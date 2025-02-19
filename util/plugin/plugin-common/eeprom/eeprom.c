/***************************************************************************//**
 * @file
 * @brief Code for manipulating the EEPROM from the Application Framework
 * In particular, sleepies that use the EEPROM will require re-initialization
 * of the driver code after they wake up from sleep.  This code helps
 * manage the state of the driver.
 *******************************************************************************
 * # License
 * <b>Copyright 2018 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifdef UC_BUILD
#include "af.h"
#include "eeprom-config.h"
#else // !UC_BUILD
#ifdef EMBER_AF_API_AF_HEADER // AFV2
  #include EMBER_AF_API_AF_HEADER
#else                         // AFV6
  #include PLATFORM_HEADER
  #include CONFIGURATION_HEADER
  #include EMBER_AF_API_HAL
  #ifdef EMBER_AF_API_DEBUG_PRINT
    #include EMBER_AF_API_DEBUG_PRINT
  #endif
  #ifdef EMBER_TEST
    #define EMBER_TEST_ASSERT(x) assert((x))
  #else
    #define EMBER_TEST_ASSERT(x)
  #endif
#endif
#endif // UC_BUILD

#include "eeprom.h"

#ifdef EMBER_TEST
  #include "eeprom-test.h"
#endif

//------------------------------------------------------------------------------
// Globals

// NOTE:
// In EmberZNet 4.3 we required the code required that the
// underlying EEPROM driver MUST have support for arbitrary page writes
// (i.e. writes that cross page boundaries and or are smaller than the page size)
// Specifically the OTA Storage EEPROM Driver plugin code for storing OTA images
// requires this.

// This is no longer a requirement due to the fact that we have formal page-erase
// support built into the OTA code.  However for systems using a read-modify-write
// driver we have support here.
#if defined(EZSP_HOST) \
  || defined(EMBER_AF_PLUGIN_OTA_STORAGE_SIMPLE_EEPROM_ENABLE_SOC_APP_BOOTLOADER_COMPATIBILITY_MODE)
  #define eepromInit() halEepromInit()
  #define eepromWrite(address, data, len) \
  halEepromWrite((address), (data), (len))
  #define eepromRead(address, data, len) \
  halEepromRead((address), (data), (len))
  #define eepromErase(address, len) \
  halEepromErase((address), (len))
  #define eepromBusy() \
  halEepromBusy()
  #define eepromInfo() \
  halEepromInfo()
  #define eepromShutdown() \
  halEepromShutdown()

#else // SOC with 4.3 bootloader or later
  #define eepromInit() halAppBootloaderInit()
  #define eepromWrite(address, data, len) \
  halAppBootloaderWriteRawStorage((address), (data), (len))
  #define eepromRead(address, data, len) \
  halAppBootloaderReadRawStorage((address), (data), (len))
  #define eepromErase(address, len) \
  halAppBootloaderEraseRawStorage((address), (len))
  #define eepromBusy() \
  halAppBootloaderStorageBusy()
  #define eepromInfo() \
  halAppBootloaderInfo()
  #define eepromShutdown() \
  halAppBootloaderShutdown()
#endif

EmAfPartialWriteStruct emAfEepromSavedPartialWrites[EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT];
// the following would allow up to EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT number of out of order
// ota block deliveries, especially useful when PAGE_REQUEST is in place
EmAfPartialWriteStruct emAfEepromPostPartialWrites[EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT];
// We cache the word size because determining the size requires calling into the
// bootloader and potentially reading it from the part itself.  Several pieces
// of code reference the word size quite often and therefore this will reduce
// the performance hit of the code.
#define UNKNOWN_WORD_SIZE 0

typedef enum {
  PAGE_ERASE_NOT_NEEDED = 0,
  PAGE_ERASE_REQUIRED   = 1,
  PAGE_ERASE_UNKNOWN    = 0xFF,
} PageEraseStatus;

static HalEepromState eepromState = HAL_EEPROM_UNINITIALIZED;

static uint8_t wordSize = UNKNOWN_WORD_SIZE;

static PageEraseStatus pageEraseStatus = PAGE_ERASE_UNKNOWN;

static uint8_t postPartialentries = 0;

#define pageEraseRequired() (pageEraseStatus == PAGE_ERASE_REQUIRED)

#define INVALID_INDEX 0xFF
#define INVALID_ADDRESS 0xFFFFFFFF

#ifdef EMBER_SCRIPTED_TEST
  #define eepromReallyDebugPrintln(...)
#else
  #define eepromReallyDebugPrintln(...) emberAfCorePrintln(__VA_ARGS__)
#endif

//#define EEPROM_DEBUG true
#if defined(EEPROM_DEBUG)
  #define eepromDebugPrintln(...) eepromReallyDebugPrintln(__VA_ARGS__)
#elif defined(EMBER_SCRIPTED_TEST)
  #define eepromDebugPrintln(...) \
  printf(__VA_ARGS__);            \
  printf("\n")
#else
  #define eepromDebugPrintln(...)
#endif

//------------------------------------------------------------------------------
// App framework init callback
void emberAfPluginEepromInitCallback(void)
{
  emberAfPluginEepromInit();
}

//------------------------------------------------------------------------------

// Sleepies will need a re-initialization of the driver after sleep,
// so this code helps manage that state and automatically re-init the driver
// if it is needed.

bool emAfIsEepromInitialized(void)
{
  return eepromState >= HAL_EEPROM_INITIALIZED;
}

void emAfPluginEepromStateUpdate(HalEepromState newState)
{
  if (eepromState != newState) {
    emberAfPluginEepromStateChangeCallback(eepromState, newState);
    eepromState = newState;
  }
}

uint8_t emberAfPluginEepromGetWordSize(void)
{
  if (wordSize == UNKNOWN_WORD_SIZE) {
    const HalEepromInformationType* part = emberAfPluginEepromInfo();
    wordSize = 1;

    // The word size in the part was added much later in the driver
    // support.  Therefore we assume the word size is 1 for those devices
    // that don't support the parameter because in prior releases
    // we only released drivers that supported that word size.
    if (part != NULL
        && part->version >= EEPROM_INFO_MIN_VERSION_WITH_WORD_SIZE_SUPPORT) {
      wordSize = part->wordSizeBytes;
    }
  }
  return wordSize;
}

void emberAfPluginEepromNoteInitializedState(bool state)
{
  // Only change to initialized if not already in an initialized state
  if (state == true && eepromState < HAL_EEPROM_INITIALIZED) {
    emAfPluginEepromStateUpdate(HAL_EEPROM_INITIALIZED);
  }
  // Only change to uninitialized if not already in an uninitialized state
  else if (state == false && eepromState >= HAL_EEPROM_INITIALIZED) {
    emAfPluginEepromStateUpdate(HAL_EEPROM_UNINITIALIZED);
  }
}

static void eepromFirstTimeInit(void)
{
  if (PAGE_ERASE_UNKNOWN == pageEraseStatus) {
    const HalEepromInformationType* eepromInfo = eepromInfo();
    if (eepromInfo != NULL) {
      pageEraseStatus = ((eepromInfo->capabilitiesMask
                          & EEPROM_CAPABILITIES_PAGE_ERASE_REQD)
                         ? PAGE_ERASE_REQUIRED
                         : PAGE_ERASE_NOT_NEEDED);

      MEMSET(emAfEepromSavedPartialWrites,
             0xFF,
             sizeof(EmAfPartialWriteStruct)
             * EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT);

      MEMSET(emAfEepromPostPartialWrites,
             0xFF,
             sizeof(EmAfPartialWriteStruct)
             * EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT);

      // We can't do partial writes with a word size above 4.
      if (pageEraseRequired()) {
        assert(emberAfPluginEepromGetWordSize() <= EM_AF_EEPROM_MAX_WORD_SIZE);
      }
    } else {
      // Legacy drivers without EEPROM info structs were all read-modify write,
      // so we know definitively that page erase is not needed.
      pageEraseStatus = PAGE_ERASE_NOT_NEEDED;
    }
  }
}

void emberAfPluginEepromInit(void)
{
  if (emAfIsEepromInitialized()) {
    return;
  }

  uint8_t eepromStatus = eepromInit();
  (void)eepromStatus;
  eepromReallyDebugPrintln("EEPROM init: 0x%X", eepromStatus);
  emberAfPluginEepromNoteInitializedState(true);

  eepromFirstTimeInit();
}

const HalEepromInformationType* emberAfPluginEepromInfo(void)
{
  emberAfPluginEepromInit();
  return eepromInfo();
}

static void clearPartialWrite(uint8_t index)
{
  MEMSET(&(emAfEepromSavedPartialWrites[index]), 0xFF, sizeof(EmAfPartialWriteStruct));
}

static void clearPostPartialWrite(uint8_t index)
{
  if (postPartialentries) {
    --postPartialentries;
  }
  MEMSET(&(emAfEepromPostPartialWrites[index]), 0xFF, sizeof(EmAfPartialWriteStruct));
}

static uint8_t checkForPostcedingPartialWrite(uint32_t address)
{
  uint8_t i;
  eepromDebugPrintln("checkForPostcedingPartialWrite() address: 0x%4X", address);
  uint8_t wordsize = emberAfPluginEepromGetWordSize();
  for (i = 0; i < EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT; i++) {
    eepromDebugPrintln("Post Partial write index %d, address 0x%4X", i, emAfEepromPostPartialWrites[i].address);
    uint32_t tempAddress = emAfEepromPostPartialWrites[i].address; // this is the address in the middle of the block
    if (tempAddress != INVALID_ADDRESS
        && ((tempAddress
             - (wordsize - emAfEepromPostPartialWrites[i].count)) == address)) {
      return i;
    }
  }
  return INVALID_INDEX;
}

static uint8_t addPostPartialWrite(const EmAfPartialWriteStruct* newPartialWrite)
{
  uint8_t i;
  for (i = 0; i < EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT; i++) {
    if (emAfEepromPostPartialWrites[i].address == INVALID_ADDRESS) {
      MEMMOVE(&(emAfEepromPostPartialWrites[i]),
              newPartialWrite,
              sizeof(EmAfPartialWriteStruct));
      eepromDebugPrintln("Stored post partial write at index %d", i);
      ++postPartialentries;
      return EEPROM_SUCCESS;
    }
  }
  return EEPROM_ERR;
}

static uint8_t checkForPreceedingPartialWrite(uint32_t address)
{
  uint8_t i;
  eepromDebugPrintln("checkForPreceedingPartialWrite() address: 0x%4X", address);
  for (i = 0; i < EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT; i++) {
    eepromDebugPrintln("Partial write index %d, address 0x%4X", i, emAfEepromSavedPartialWrites[i].address);
    uint32_t tempAddress = emAfEepromSavedPartialWrites[i].address;
    if (tempAddress != INVALID_ADDRESS
        && ((tempAddress
             + emAfEepromSavedPartialWrites[i].count) == address)) {
      return i;
    }
  }
  return INVALID_INDEX;
}

static uint8_t addPartialWrite(const EmAfPartialWriteStruct* newPartialWrite)
{
  uint8_t i;
  for (i = 0; i < EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT; i++) {
    if (emAfEepromSavedPartialWrites[i].address == INVALID_ADDRESS) {
      MEMMOVE(&(emAfEepromSavedPartialWrites[i]),
              newPartialWrite,
              sizeof(EmAfPartialWriteStruct));
      eepromDebugPrintln("Stored partial write at index %d", i);
      return EEPROM_SUCCESS;
    }
  }
  return EEPROM_ERR;
}

#if defined(EMBER_TEST)
void emAfPluginEepromFakeEepromCallback(void)
{
  // The fake (simulated) EEPROM gets initialized at a funny time,
  // after emberAfPluginEepromInit().  We must reinitialize the known
  // parameters of the EEPROM by this plugin in case it has chnaged.
  emberAfPluginEepromNoteInitializedState(false);
  pageEraseStatus = PAGE_ERASE_UNKNOWN;
  emberAfPluginEepromInit();
}
#endif

#ifdef _SILICON_LABS_32B_SERIES_2
#define ALIGNMENT4 __ALIGNED(4)
#else
#define ALIGNMENT4
#endif

ALIGNMENT4 static uint8_t ota_buff[EEPROM_PAGE_SIZE];

static uint8_t postcedingPartialWrite(uint32_t address,
                                      const uint8_t *data,
                                      uint16_t totalLength)
{
  uint8_t index = INVALID_INDEX;
  uint8_t status = EEPROM_SUCCESS;
  EmAfPartialWriteStruct tempPrePartialWrite = { INVALID_ADDRESS, { 0xFF }, 0 };
  EmAfPartialWriteStruct tempPostPartialWrite = { INVALID_ADDRESS, { 0xFF }, 0 };
  uint8_t wordSize = emberAfPluginEepromGetWordSize();
  //**********************************************************************
  //using the begining bytes of new data:
  //cache the postceding part of the unaligned write with no previous data!
  //**********************************************************************
  tempPostPartialWrite.address = address; // this is the unaligned address in the middle of the block
  uint8_t postcedingRemaining = (address) % wordSize;
  tempPostPartialWrite.count = wordSize - postcedingRemaining;
  MEMCOPY(tempPostPartialWrite.data, data, wordSize - postcedingRemaining);

  index = addPostPartialWrite(&tempPostPartialWrite);
  if (index == INVALID_INDEX ) {
    // postceding tabel is not big enough for the number of out of order blocks we have received
    // increase EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT in configuration or try again
    assert(false);
  }
  if (totalLength < (wordSize - postcedingRemaining) ) {
    // this shoudl not happen, unless ota-server is funky and sending us wrong sized blocks
    assert(false);
  }
  totalLength -= wordSize - postcedingRemaining;
  data += (wordSize - postcedingRemaining);
  address = address + (wordSize - postcedingRemaining);

  //**********************************************************************
  //using the ending bytes of new data:
  //cache the new preceding part of the unaligned write with no CONTINUES previous data,
  // or in other words, with no matching entry in preceding partialcache |
  //**********************************************************************

  uint8_t precedingRemaining = (address + totalLength) % wordSize;
  if (totalLength > 0u) {
    tempPrePartialWrite.address = address + totalLength - precedingRemaining;
    tempPrePartialWrite.count = precedingRemaining;
    MEMCOPY(tempPrePartialWrite.data, data + totalLength - precedingRemaining, precedingRemaining);
    index = addPartialWrite(&tempPrePartialWrite);
    if (index == INVALID_INDEX ) {
      // postceding tabel is not big enough for the number of out of order blocks we have received
      // increase EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT in configuration or try again
      assert(false);
    }
  }
  //#########
  totalLength = totalLength - precedingRemaining;
  //#########

  //**********************************************************************
  // for everything in between the newly added postceding cache entry,
  // and preceding cache entry, we directly write to eeprom
  //**********************************************************************

  if (totalLength > 0u) {
    emAfPluginEepromStateUpdate(HAL_EEPROM_WRITING);
   #ifdef _SILICON_LABS_32B_SERIES_2
    // we need 32 bits alignment for some boards e.g. 4181
    MEMCOPY(ota_buff,
            data,
            totalLength);
    status = eepromWrite(address, ota_buff, totalLength);
   #else
    status = eepromWrite(address, data, totalLength);
   #endif

    emAfPluginEepromStateUpdate(HAL_EEPROM_INITIALIZED);
  }

  //#########

  return status;
}

uint8_t emberAfPluginEepromWrite(uint32_t address,
                                 const uint8_t *data,
                                 uint16_t totalLength)
{
  uint8_t status = EEPROM_SUCCESS;
  EmAfPartialWriteStruct tempPartialWrite = { INVALID_ADDRESS, { 0xFF }, 0 };
  emberAfPluginEepromInit();
  uint8_t wordSize = emberAfPluginEepromGetWordSize();

  if (pageEraseRequired()
      && (wordSize > 1)
      && ((address % wordSize) != 0)) {
    uint8_t index = checkForPreceedingPartialWrite(address);
    if (index == INVALID_INDEX) {
      // An unaligned write with no previous data!  We are handling this
      // but we might still hit asserts. For example, when:
      //   - we don't have any space in the table
      //     of postceding partial writes
      return postcedingPartialWrite(address, data, totalLength);
    } else {
      uint8_t copyLength;
      uint8_t partialLength = wordSize - emAfEepromSavedPartialWrites[index].count;
      if (totalLength > partialLength) {
        copyLength = partialLength;
      } else {
        copyLength = totalLength;
      }
      MEMCOPY(&(emAfEepromSavedPartialWrites[index].data[emAfEepromSavedPartialWrites[index].count]),
              data,
              copyLength);
      totalLength -= copyLength;
      emAfEepromSavedPartialWrites[index].count += copyLength;
      address += copyLength;

      if (emAfEepromSavedPartialWrites[index].count == wordSize) {
        emAfPluginEepromStateUpdate(HAL_EEPROM_WRITING);
        status = eepromWrite(emAfEepromSavedPartialWrites[index].address,
                             emAfEepromSavedPartialWrites[index].data,
                             wordSize);
        emAfPluginEepromStateUpdate(HAL_EEPROM_INITIALIZED);
        data += copyLength;
        EMBER_TEST_ASSERT(status == EEPROM_SUCCESS);
        clearPartialWrite(index);
        if (status != EEPROM_SUCCESS) {
          return status;
        }
      }

      // We have cached the partial write but have not enough data to write to flash.
      // Consider this a "successful" write as we have nothing more to do until
      // we get more data.
      if (totalLength == 0) {
        return status;
      }
    }
  }

  if (pageEraseRequired()) {
    // At this point, any data left to write should start on a word aligned boundary.
    assert(address % wordSize == 0);
  }

  if (pageEraseRequired()
      && (((address + totalLength) % wordSize) != 0)) {
    uint8_t remainder = (address + totalLength) % wordSize;
    uint32_t tempAddress = address + totalLength - remainder;
    tempPartialWrite.address = tempAddress;
    MEMCOPY(tempPartialWrite.data, data + totalLength - remainder, remainder);
    tempPartialWrite.count = remainder;
    totalLength -= remainder;
  }
  eepromDebugPrintln("eepromWrite() Address: 0x%4X, len: %d",
                     address,
                     totalLength);
  if (totalLength > 0u) {
    emAfPluginEepromStateUpdate(HAL_EEPROM_WRITING);

#ifdef _SILICON_LABS_32B_SERIES_2
    // we need 32 bits alignment for some boards e.g. 4181
    MEMCOPY(ota_buff,
            data,
            totalLength);
    status = eepromWrite(address, ota_buff, totalLength);
#else
    status = eepromWrite(address, data, totalLength);
#endif
    emAfPluginEepromStateUpdate(HAL_EEPROM_INITIALIZED);
  }

  EMBER_TEST_ASSERT(status == EEPROM_SUCCESS);

  uint8_t index = INVALID_INDEX;
  if (postPartialentries) {
    index = checkForPostcedingPartialWrite(tempPartialWrite.address);// this is the address of the begining of the block
  }
  if (status == 0 && index != INVALID_INDEX) {
    eepromDebugPrintln("Found post ceding entry for address 0x%4X",
                       tempPartialWrite.address);
    // we already have the rest of the ending unaligned write in postceding cache table
    // we can just concatenate the 2 parts and write it to the eeprom
    MEMCOPY(ota_buff,
            tempPartialWrite.data,
            tempPartialWrite.count);
    MEMCOPY(ota_buff + tempPartialWrite.count,
            emAfEepromPostPartialWrites[index].data,
            emAfEepromPostPartialWrites[index].count);

    if (wordSize != (emAfEepromPostPartialWrites[index].count + tempPartialWrite.count)) {
      // we have gotten to state where our partial write cache entry is fragmented
      // this shoudl not happen, unless ota-server is funky and sending us wrong sized blocks
      assert(false);
    }
    status = eepromWrite(tempPartialWrite.address, ota_buff, wordSize);

    emAfPluginEepromStateUpdate(HAL_EEPROM_INITIALIZED);
    clearPostPartialWrite(index);
  } else {
    // The remaining unalighed write must be added to preceding cache table,
    // waiting for the next block to bring in the rest of the data
    if (status == 0
        && tempPartialWrite.address != INVALID_ADDRESS) {
      eepromDebugPrintln("Caching partial word write at address 0x%4X",
                         tempPartialWrite.address);
      status = addPartialWrite(&tempPartialWrite);
      EMBER_TEST_ASSERT(status == EEPROM_SUCCESS);
    }
  }

  return status;
}

uint8_t emberAfPluginEepromFlushSavedPartialWrites(void)
{
  uint8_t i;
  eepromDebugPrintln("emberAfPluginEepromFlushSavedPartialWrites()");
  if (!pageEraseRequired()) {
    return EEPROM_SUCCESS;
  }
  emberAfPluginEepromInit();

  for (i = 0; i < EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT; i++) {
    if (emAfEepromSavedPartialWrites[i].address != INVALID_ADDRESS) {
      uint8_t status;
      emAfPluginEepromStateUpdate(HAL_EEPROM_WRITING);
      status = eepromWrite(emAfEepromSavedPartialWrites[i].address,
                           emAfEepromSavedPartialWrites[i].data,
                           emberAfPluginEepromGetWordSize());
      emAfPluginEepromStateUpdate(HAL_EEPROM_INITIALIZED);
      EMBER_TEST_ASSERT(status == EEPROM_SUCCESS);
      if (status != EEPROM_SUCCESS) {
        return status;
      }
    }
  }
  return EEPROM_SUCCESS;
}

uint8_t emberAfPluginEepromRead(uint32_t address,
                                uint8_t *data,
                                uint16_t totalLength)
{
  uint8_t status;

  emberAfPluginEepromInit();

  emAfPluginEepromStateUpdate(HAL_EEPROM_READING);
  status = eepromRead(address, data, totalLength);
  emAfPluginEepromStateUpdate(HAL_EEPROM_INITIALIZED);

  EMBER_TEST_ASSERT(status == EEPROM_SUCCESS);

  return status;
}

uint8_t emberAfPluginEepromErase(uint32_t address, uint32_t totalLength)
{
  uint8_t i;
  uint8_t status;
  emberAfPluginEepromInit();

  emAfPluginEepromStateUpdate(HAL_EEPROM_ERASING);
  status = eepromErase(address, totalLength);
  emAfPluginEepromStateUpdate(HAL_EEPROM_INITIALIZED);

  EMBER_TEST_ASSERT(status == EEPROM_SUCCESS);

  for (i = 0; i < EMBER_AF_PLUGIN_EEPROM_PARTIAL_WORD_STORAGE_COUNT; i++) {
    if (emAfEepromSavedPartialWrites[i].address != INVALID_ADDRESS
        && emAfEepromSavedPartialWrites[i].address >= address
        && emAfEepromSavedPartialWrites[i].address < (address + totalLength)) {
      clearPartialWrite(i);
    }
  }

  return status;
}

bool emberAfPluginEepromBusy(void)
{
  emberAfPluginEepromInit();
  return eepromBusy();
}

// Returns true if shutdown was done, returns false if shutdown was not
// necessary.
bool emberAfPluginEepromShutdown(void)
{
  if (!emAfIsEepromInitialized()) {
    return false;
  }

  eepromShutdown();
  emAfPluginEepromStateUpdate(HAL_EEPROM_SHUTDOWN);
  return true;
}
