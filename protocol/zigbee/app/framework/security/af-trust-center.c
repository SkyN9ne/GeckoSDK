/***************************************************************************//**
 * @file
 * @brief Security code for a Trust Center node.
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

#include "app/framework/include/af.h"
#define USE_REAL_SECURITY_PROTOTYPES
#include "app/framework/security/af-security.h"
#include "app/framework/util/af-main.h"
#include "app/framework/util/attribute-storage.h"

#ifdef UC_BUILD
#include "sl_component_catalog.h"
#ifdef SL_CATALOG_ZIGBEE_DELAYED_JOIN_PRESENT
#define DELAYED_JOIN_PRESENT
#endif
#ifdef SL_CATALOG_ZIGBEE_NETWORK_CREATOR_SECURITY_PRESENT
#include "network-creator-security-config.h"
#if (EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_BDB_JOIN_USES_INSTALL_CODE_KEY == 1)
#define NETWORK_CREATOR_SECURITY_BDB_JOIN_USES_INSTALL_CODE_KEY
#endif
#endif
#else // UC_BUILD
#ifdef EMBER_AF_PLUGIN_DELAYED_JOIN
#define DELAYED_JOIN_PRESENT
#endif
#ifdef EMBER_AF_PLUGIN_NETWORK_CREATOR_SECURITY_BDB_JOIN_USES_INSTALL_CODE_KEY
#define NETWORK_CREATOR_SECURITY_BDB_JOIN_USES_INSTALL_CODE_KEY
#endif
#endif // UC_BUILD

//------------------------------------------------------------------------------
// Globals

#if defined(EMBER_AF_PRINT_SECURITY)  || defined(SL_CATALOG_ZIGBEE_DEBUG_PRINT_PRESENT)
// Corresponds to the EmberJoinDecision status codes
static const char * joinDecisionText[] = {
  EMBER_JOIN_DECISION_STRINGS
};

// Corresponds to the EmberDeviceUpdate status codes
static const char * deviceUpdateText[] = {
  EMBER_DEVICE_UPDATE_STRINGS
};

#endif // EMBER_AF_PRINT_APP

static EmberStatus permitRequestingTrustCenterLinkKey(void);
static EmberStatus permitRequestingApplicationLinkKey(void);
static EmberStatus setJoinPolicy(EmberJoinDecision decision);

//----------------------------------------------------------------
// Helper Functions

// Reverse the bits in a byte
static uint8_t reverse(uint8_t b)
{
#if defined(EZSP_HOST) || defined(BOARD_SIMULATION)
  return ((b * 0x0802UL & 0x22110UL) | (b * 0x8020UL & 0x88440UL)) * 0x10101UL >> 16;
#else
  return (__RBIT((uint32_t)b) >> 24); // Cortex function __RBIT uses uint32_t
#endif // EZSP_HOST
}

//------------------------------------------------------------------------------

EmberStatus zaTrustCenterSetJoinPolicy(EmberJoinDecision decision)
{
  // Call the platform specific method to do this.
  return setJoinPolicy(decision);
}

EmberStatus zaTrustCenterSecurityPolicyInit(void)
{
  EmberStatus status = permitRequestingTrustCenterLinkKey();
  if (status == EMBER_SUCCESS) {
    status = permitRequestingApplicationLinkKey();
  }
  if (status != EMBER_SUCCESS) {
    return status;
  }

  // We always set the join policy to EMBER_USE_PRECONFIGURED_KEY
  // even in the case where the joining device doesn't have one.  This
  // is the safest thing to do.
  // In cases where devices don't have a preconfigured key, the TC must be
  // explicitly told to allow joining by calling the function below with
  // EMBER_SEND_KEY_IN_THE_CLEAR.  Once the device finishes joining the TC
  // should set the policy back to EMBER_USE_PRECONFIGURED_KEY.
  return setJoinPolicy(EMBER_USE_PRECONFIGURED_KEY);
}

EmberStatus zaTrustCenterSecurityInit(bool centralizedNetwork)
{
  EmberInitialSecurityState state;
  EmberExtendedSecurityBitmask extended;
  EmberStatus status;
  const EmberAfSecurityProfileData *data = emAfGetCurrentSecurityProfileData();

  if (data == NULL) {
    return EMBER_ERR_FATAL;
  }

  MEMSET(&state, 0, sizeof(EmberInitialSecurityState));
  state.bitmask = data->tcBitmask;
  extended = data->tcExtendedBitmask;
  MEMMOVE(emberKeyContents(&state.preconfiguredKey),
          emberKeyContents(&data->preconfiguredKey),
          EMBER_ENCRYPTION_KEY_SIZE);

  // Random network key (highly recommended)
  status = emberAfGenerateRandomKey(&(state.networkKey));
  if (status != EMBER_SUCCESS) {
    return status;
  }

  // Check for distributed network.
  if (!centralizedNetwork) {
    state.bitmask |= EMBER_DISTRIBUTED_TRUST_CENTER_MODE;
  }

#if defined(ZA_CLI_FULL) || defined(SL_CATALOG_CLI_PRESENT)
  // These functions will only be called if the full CLI is enabled and key
  // values have been previously set on the CLI via the "changekey" command.
  getLinkKeyFromCli(&(state.preconfiguredKey));
  getNetworkKeyFromCli(&(state.networkKey));
#endif

  emberAfSecurityInitCallback(&state, &extended, true); // trust center?

  emberAfSecurityPrintln("set state to: 0x%2x", state.bitmask);
  status = emberSetInitialSecurityState(&state);
  if (status != EMBER_SUCCESS) {
    emberAfSecurityPrintln("security init TC: 0x%x", status);
    return status;
  }

  // Don't need to check on the status here, emberSetExtendedSecurityBitmask
  // always returns EMBER_SUCCESS.
  emberAfSecurityPrintln("set extended security to: 0x%2x", extended);
  emberSetExtendedSecurityBitmask(extended);

  status = zaTrustCenterSecurityPolicyInit();
  if (status != EMBER_SUCCESS) {
    return status;
  }

  emAfClearLinkKeyTable();

  return EMBER_SUCCESS;
}

static void securityJoinNotify(EmberNodeId newNodeId,
                               EmberEUI64 newNodeEui64,
                               EmberNodeId parentOfNewNode,
                               EmberDeviceUpdate status,
                               EmberJoinDecision decision)
{
  // Allow users of the framework an opportunity to see this notification.
  emberAfTrustCenterJoinCallback(newNodeId,
                                 newNodeEui64,
                                 parentOfNewNode,
                                 status,
                                 decision);

#if defined(EMBER_AF_PRINT_SECURITY) || defined(UC_BUILD)

  emberAfSecurityPrintln("Trust Center Join Handler: status = %p, decision = %p (%x), shortid 0x%2x",
                         deviceUpdateText[status],
                         joinDecisionText[decision],
                         decision,
                         newNodeId);
  emberAfSecurityFlush();
#endif
}

EmberStatus emAfInstallCodeToKey(uint8_t* installCode, uint8_t length,
                                 EmberKeyData *key)
{
  EmberStatus status;
  uint8_t index;
  bool validInstallCodeSize = false;
  uint16_t crc = 0xFFFF;
  uint8_t installCodeSizes[EMBER_NUM_INSTALL_CODE_SIZES] =
    EMBER_INSTALL_CODE_SIZES;

  if (!installCode || !key) {
    return EMBER_BAD_ARGUMENT;
  }

  for (index = 0; index < EMBER_NUM_INSTALL_CODE_SIZES; index++) {
    if (length == installCodeSizes[index]) {
      validInstallCodeSize = true;
      break;
    }
  }

  if (!validInstallCodeSize) {
    return EMBER_BAD_ARGUMENT;
  }

  // Compute the CRC and verify that it matches.  The bit reversals, byte swap,
  // and ones' complement are due to differences between halCommonCrc16 and the
  // Smart Energy version.
  for (index = 0; index < length - EMBER_INSTALL_CODE_CRC_SIZE; index++) {
    crc = halCommonCrc16(reverse(installCode[index]), crc);
  }
  crc = ~HIGH_LOW_TO_INT(reverse(LOW_BYTE(crc)), reverse(HIGH_BYTE(crc)));
  if (installCode[length - EMBER_INSTALL_CODE_CRC_SIZE] != LOW_BYTE(crc)
      || installCode[length - EMBER_INSTALL_CODE_CRC_SIZE + 1] != HIGH_BYTE(crc)) {
    return EMBER_SECURITY_DATA_INVALID;
  }

  // Compute the key from the install code and CRC.
  status = emberAesHashSimple(length, installCode, emberKeyContents(key));

  return status;
}

//==============================================================================
// Platform Dependent Implementations

#if defined (EZSP_HOST)

static const char * ezspJoinPolicyText[] = {
  "Disallow all joins and rejoins",
  "Allow preconfigured key joins",
  "Allow Joins, rejoins have link key",
  "Allow rejoins only",
};

#ifdef UC_BUILD
void emAfTrustCenterJoinCallback(EmberNodeId newNodeId,
                                 EmberEUI64 newNodeEui64,
                                 EmberDeviceUpdate status,
                                 EmberJoinDecision policyDecision,
                                 EmberNodeId parentOfNewNode)
#else
void ezspTrustCenterJoinHandler(EmberNodeId newNodeId,
                                EmberEUI64 newNodeEui64,
                                EmberDeviceUpdate status,
                                EmberJoinDecision policyDecision,
                                EmberNodeId parentOfNewNode)
#endif
{
  (void) emberAfPushCallbackNetworkIndex();
#if defined(DELAYED_JOIN_PRESENT)
  policyDecision = (status == EMBER_STANDARD_SECURITY_SECURED_REJOIN
                    || status == EMBER_STANDARD_SECURITY_UNSECURED_REJOIN)
                   ? EMBER_USE_PRECONFIGURED_KEY
                   : EMBER_NO_ACTION;
#endif
  //this would be the callback
  securityJoinNotify(newNodeId,
                     newNodeEui64,
                     parentOfNewNode,
                     status,
                     policyDecision);
  (void) emberAfPopNetworkIndex();
}

static EmberStatus setJoinPolicy(EmberJoinDecision decision)
{
  EzspDecisionBitmask policy = EZSP_DECISION_BITMASK_DEFAULT_CONFIGURATION;
  uint8_t textId = 0;

  if (decision == EMBER_USE_PRECONFIGURED_KEY) {
    policy = (EZSP_DECISION_ALLOW_JOINS | EZSP_DECISION_ALLOW_UNSECURED_REJOINS);
    textId = 1;
  } else if (decision == EMBER_SEND_KEY_IN_THE_CLEAR) {
    policy = (EZSP_DECISION_ALLOW_JOINS | EZSP_DECISION_ALLOW_UNSECURED_REJOINS | EZSP_DECISION_SEND_KEY_IN_CLEAR);
    textId = 2;
  } else if (decision == EMBER_ALLOW_REJOINS_ONLY) {
    policy = EZSP_DECISION_ALLOW_UNSECURED_REJOINS;
    textId = 3;
  }
  return emberAfSetEzspPolicy(EZSP_TRUST_CENTER_POLICY,
                              policy,
                              "Trust Center Policy",
                              ezspJoinPolicyText[textId]);
}

static EmberStatus permitRequestingTrustCenterLinkKey(void)
{
  const EmberAfSecurityProfileData *data = emAfGetCurrentSecurityProfileData();
  if (data == NULL) {
    return EMBER_ERR_FATAL;
  }

  return emberAfSetEzspPolicy(EZSP_TC_KEY_REQUEST_POLICY,
                              data->tcLinkKeyRequestPolicy,
                              "TC Key Request",
                              (data->tcLinkKeyRequestPolicy
                               !=  EMBER_AF_DENY_TC_KEY_REQUESTS
                               ? "Allow"
                               : "Deny"));
}

static EmberStatus permitRequestingApplicationLinkKey(void)
{
  const EmberAfSecurityProfileData *data = emAfGetCurrentSecurityProfileData();
  if (data == NULL) {
    return EMBER_ERR_FATAL;
  }
  return emberAfSetEzspPolicy(EZSP_APP_KEY_REQUEST_POLICY,
                              data->appLinkKeyRequestPolicy,
                              "App. Key Request",
                              (data->appLinkKeyRequestPolicy
                               != EMBER_AF_DENY_APP_KEY_REQUESTS
                               ? "Allow"
                               : "Deny"));
}

//------------------------------------------------------------------------------
// System-on-a-chip

#else

static EmberJoinDecision defaultDecision = EMBER_USE_PRECONFIGURED_KEY;
#ifdef UC_BUILD
EmberJoinDecision emAfTrustCenterJoinCallback(EmberNodeId newNodeId,
                                              EmberEUI64 newNodeEui64,
                                              EmberDeviceUpdate status,
                                              EmberNodeId parentOfNewNode)
#else
EmberJoinDecision emberTrustCenterJoinHandler(EmberNodeId newNodeId,
                                              EmberEUI64 newNodeEui64,
                                              EmberDeviceUpdate status,
                                              EmberNodeId parentOfNewNode)
#endif
{
  (void) emberAfPushCallbackNetworkIndex();
  EmberJoinDecision joinDecision = defaultDecision;
  EmberCurrentSecurityState securityState;
  EmberStatus securityStatus = emberGetCurrentSecurityState(&securityState);

  if (status == EMBER_STANDARD_SECURITY_SECURED_REJOIN
      || status == EMBER_DEVICE_LEFT
      // 4.6.3.3.2 - TC rejoins rejected in distributed TC mode
      || ((EMBER_SUCCESS == securityStatus)
          && (securityState.bitmask & EMBER_DISTRIBUTED_TRUST_CENTER_MODE)
          && (status == EMBER_STANDARD_SECURITY_UNSECURED_REJOIN))) {
    joinDecision = EMBER_NO_ACTION;
  }
#ifdef NETWORK_CREATOR_SECURITY_BDB_JOIN_USES_INSTALL_CODE_KEY
  else {
    EmberTransientKeyData transientKeyData;
    // Check in transient key table
    if ((EMBER_STANDARD_SECURITY_UNSECURED_JOIN == status)
        && (EMBER_SUCCESS != emberGetTransientLinkKey(newNodeEui64,
                                                      &transientKeyData))) {
      joinDecision = EMBER_NO_ACTION;
    }
  }
#endif

#if defined(DELAYED_JOIN_PRESENT)
  joinDecision = (status == EMBER_STANDARD_SECURITY_SECURED_REJOIN
                  || status == EMBER_STANDARD_SECURITY_UNSECURED_REJOIN)
                 ? EMBER_USE_PRECONFIGURED_KEY
                 : EMBER_NO_ACTION;
#endif

  // EMZIGBEE-9283 Allow unsecured rejoin if default decision is EMBER_ALLOW_REJOINS_ONLY
  if (status == EMBER_STANDARD_SECURITY_UNSECURED_REJOIN
      && joinDecision == EMBER_ALLOW_REJOINS_ONLY ) {
    joinDecision = EMBER_USE_PRECONFIGURED_KEY;
  }

  //this would be the callback
  securityJoinNotify(newNodeId,
                     newNodeEui64,
                     parentOfNewNode,
                     status,
                     joinDecision);

  (void) emberAfPopNetworkIndex();
  return joinDecision;
}

static EmberStatus setJoinPolicy(EmberJoinDecision decision)
{
  defaultDecision = decision;
  return EMBER_SUCCESS;
}

static EmberStatus permitRequestingTrustCenterLinkKey(void)
{
  const EmberAfSecurityProfileData *data = emAfGetCurrentSecurityProfileData();
  if (data == NULL) {
    return EMBER_ERR_FATAL;
  }
  emberTrustCenterLinkKeyRequestPolicy = data->tcLinkKeyRequestPolicy;

  return EMBER_SUCCESS;
}

static EmberStatus permitRequestingApplicationLinkKey(void)
{
  const EmberAfSecurityProfileData *data = emAfGetCurrentSecurityProfileData();
  if (data == NULL) {
    return EMBER_ERR_FATAL;
  }
  emberAppLinkKeyRequestPolicy = data->appLinkKeyRequestPolicy;
  return EMBER_SUCCESS;
}

#endif // EZSP_HOST
