/***************************************************************************//**
 * @file
 * @brief This file contains the type definitions for efr32xg2x chip specific
 *   aspects of RAIL.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef __RAIL_CHIP_SPECIFIC_H_
#if !defined(__RAIL_TYPES_H__) && !defined(DOXYGEN_SHOULD_SKIP_THIS)
#warning rail_chip_specific.h should only be included by rail_types.h
#include "rail_types.h" // Force rail_chip_specific.h only within rail_types.h
#else // __RAIL_TYPES_H__
/// Include guard
#define __RAIL_CHIP_SPECIFIC_H_

#include "rail_features.h"
#ifdef RAIL_INTERNAL_BUILD
#include "rail_chip_specific_internal.h"
#endif

#if     (defined(DOXYGEN_SHOULD_SKIP_THIS) && !defined(RAIL_ENUM))
//  Copied from rail_types.h to satisfy doxygen build.
/// The RAIL library does not use enumerations because the ARM EABI leaves their
/// size ambiguous, which causes problems if the application is built
/// with different flags than the library. Instead, uint8_t typedefs
/// are used in compiled code for all enumerations. For documentation purposes, this is
/// converted to an actual enumeration since it's much easier to read in Doxygen.
#define RAIL_ENUM(name) enum name
/// This macro is a more generic version of the \ref RAIL_ENUM() macro that
/// allows the size of the type to be overridden instead of forcing the use of
/// a uint8_t. See \ref RAIL_ENUM() for more information.
#define RAIL_ENUM_GENERIC(name, type) enum name
#endif//(defined(DOXYGEN_SHOULD_SKIP_THIS) && !defined(RAIL_ENUM))

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup General_EFR32XG2 EFR32xG2
 * @{
 * @brief EFR32xG2-specific initialization data types
 * @ingroup General
 */

/**
 * A placeholder for a chip-specific RAIL handle. Using NULL as a RAIL handle is
 * not recommended. As a result, another value that can't be de-referenced is used.
 *
 * This generic handle can and should be used for RAIL APIs that are called
 * prior to RAIL initialization.
 */
#define RAIL_EFR32_HANDLE ((RAIL_Handle_t)0xFFFFFFFFUL)

#ifndef DOXYGEN_SHOULD_SKIP_THIS

/**
 * @def RAIL_EFR32XG21_STATE_BUFFER_BYTES
 * @brief The EFR32XG21 series size needed for
 *   \ref RAIL_StateBufferEntry_t::bufferBytes.
 */
#define RAIL_EFR32XG21_STATE_BUFFER_BYTES 528

/**
 * @def RAIL_EFR32XG22_STATE_BUFFER_BYTES
 * @brief The EFR32XG22 series size needed for
 *   \ref RAIL_StateBufferEntry_t::bufferBytes.
 */
#define RAIL_EFR32XG22_STATE_BUFFER_BYTES 568

/**
 * @def RAIL_EFR32XG23_STATE_BUFFER_BYTES
 * @brief The EFR32XG23 series size needed for
 *   \ref RAIL_StateBufferEntry_t::bufferBytes.
 */
#define RAIL_EFR32XG23_STATE_BUFFER_BYTES 560

/**
 * @def RAIL_EFR32XG24_STATE_BUFFER_BYTES
 * @brief The EFR32XG24 series size needed for
 *   \ref RAIL_StateBufferEntry_t::bufferBytes.
 */
#define RAIL_EFR32XG24_STATE_BUFFER_BYTES 584

/**
 * @def RAIL_EFR32XG25_STATE_BUFFER_BYTES
 * @brief The EFR32XG25 series size needed for
 *   \ref RAIL_StateBufferEntry_t::bufferBytes.
 */
#define RAIL_EFR32XG25_STATE_BUFFER_BYTES 616

/**
 * @def RAIL_EFR32XG27_STATE_BUFFER_BYTES
 * @brief The EFR32XG27 series size needed for
 *   \ref RAIL_StateBufferEntry_t::bufferBytes.
 */
#define RAIL_EFR32XG27_STATE_BUFFER_BYTES 568

/**
 * @def RAIL_EFR32XG28_STATE_BUFFER_BYTES
 * @brief The EFR32XG28 series size needed for
 *   \ref RAIL_StateBufferEntry_t::bufferBytes.
 */
#define RAIL_EFR32XG28_STATE_BUFFER_BYTES 560

#ifndef RAIL_STATE_BUFFER_BYTES
/**
 * @def RAIL_STATE_BUFFER_BYTES
 * @brief The size needed for \ref RAIL_StateBufferEntry_t::bufferBytes
 *   on this platform for this radio. This compile-time size may be slightly
 *   larger than what \ref RAIL_GetStateBufferSize() determines at run-time.
 */
#if (_SILICON_LABS_32B_SERIES_2_CONFIG == 1)
#define RAIL_STATE_BUFFER_BYTES RAIL_EFR32XG21_STATE_BUFFER_BYTES
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 2)
#define RAIL_STATE_BUFFER_BYTES RAIL_EFR32XG22_STATE_BUFFER_BYTES
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#define RAIL_STATE_BUFFER_BYTES RAIL_EFR32XG23_STATE_BUFFER_BYTES
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 4)
#define RAIL_STATE_BUFFER_BYTES RAIL_EFR32XG24_STATE_BUFFER_BYTES
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 5)
#define RAIL_STATE_BUFFER_BYTES RAIL_EFR32XG25_STATE_BUFFER_BYTES
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 7)
#define RAIL_STATE_BUFFER_BYTES RAIL_EFR32XG27_STATE_BUFFER_BYTES
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 8)
#define RAIL_STATE_BUFFER_BYTES RAIL_EFR32XG28_STATE_BUFFER_BYTES
#else
#define RAIL_STATE_BUFFER_BYTES 0 // Sate Doxygen
#error "Unsupported platform!"
#endif
#endif //#ifndef RAIL_STATE_BUFFER_BYTES
#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @struct RAILSched_Config_t
 * @brief Provided for backwards compatibility.
 */
typedef struct RAILSched_Config {
  uint8_t buffer[1]; /**< Dummy buffer no longer used. */
} RAILSched_Config_t;

/**
 * @typedef RAIL_StateBuffer_t
 * @brief Provided for backwards compatibility.
 */
typedef uint8_t RAIL_StateBuffer_t[1];

/**
 * @struct RAIL_Config_t
 * @brief RAIL configuration structure.
 */
typedef struct RAIL_Config {
  /**
   * A pointer to a function, which is called whenever a RAIL event occurs.
   *
   * @param[in] railHandle A handle for a RAIL instance.
   * @param[in] events A bit mask of RAIL events.
   *
   * See the \ref RAIL_Events_t documentation for the list of RAIL events.
   */
  void (*eventsCallback)(RAIL_Handle_t railHandle, RAIL_Events_t events);
  /**
   * Provided for backwards compatibility. Ignored.
   */
  void *protocol;
  /**
   * Provided for backwards compatibility. Ignored.
   */
  RAILSched_Config_t *scheduler;
  /**
   * Provided for backwards compatibility. Ignored.
   */
  RAIL_StateBuffer_t buffer;
} RAIL_Config_t;

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 * @enum RAIL_RadioStateEfr32_t
 * @brief Radio state machine statuses.
 */
RAIL_ENUM(RAIL_RadioStateEfr32_t) {
  RAIL_RAC_STATE_OFF,         /**< Radio is off. */
  RAIL_RAC_STATE_RXWARM,      /**< Radio is enabling the receiver. */
  RAIL_RAC_STATE_RXSEARCH,    /**< Radio is listening for incoming frames. */
  RAIL_RAC_STATE_RXFRAME,     /**< Radio is receiving a frame. */
  RAIL_RAC_STATE_RXPD,        /**< Radio is powering down receiver and going to
                                   OFF state. */
  RAIL_RAC_STATE_RX2RX,       /**< Radio is going back to receive mode after
                                   receiving a frame. */
  RAIL_RAC_STATE_RXOVERFLOW,  /**< Received data was lost due to full receive
                                   buffer. */
  RAIL_RAC_STATE_RX2TX,       /**< Radio is disabling receiver and enabling
                                   transmitter. */
  RAIL_RAC_STATE_TXWARM,      /**< Radio is enabling transmitter. */
  RAIL_RAC_STATE_TX,          /**< Radio is transmitting data. */
  RAIL_RAC_STATE_TXPD,        /**< Radio is powering down transmitter and going
                                   to OFF state. */
  RAIL_RAC_STATE_TX2RX,       /**< Radio is disabling transmitter and enabling
                                   reception. */
  RAIL_RAC_STATE_TX2TX,       /**< Radio is preparing a transmission after the
                                   previous transmission was ended. */
  RAIL_RAC_STATE_SHUTDOWN,    /**< Radio is powering down receiver and going to
                                   OFF state. */
#if _SILICON_LABS_32B_SERIES_2_CONFIG >= 2
  RAIL_RAC_STATE_POR,         /**< Radio power-on-reset state. */
#endif
  RAIL_RAC_STATE_NONE         /**< Invalid Radio state, must be the last entry */
};

// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_RAC_STATE_OFF          ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_OFF)
#define RAIL_RAC_STATE_RXWARM       ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_RXWARM)
#define RAIL_RAC_STATE_RXSEARCH     ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_RXSEARCH)
#define RAIL_RAC_STATE_RXFRAME      ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_RXFRAME)
#define RAIL_RAC_STATE_RXPD         ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_RXPD)
#define RAIL_RAC_STATE_RX2RX        ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_RX2RX)
#define RAIL_RAC_STATE_RXOVERFLOW   ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_RXOVERFLOW)
#define RAIL_RAC_STATE_RX2TX        ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_RX2TX)
#define RAIL_RAC_STATE_TXWARM       ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_TXWARM)
#define RAIL_RAC_STATE_TX           ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_TX)
#define RAIL_RAC_STATE_TXPD         ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_TXPD)
#define RAIL_RAC_STATE_TX2RX        ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_TX2RX)
#define RAIL_RAC_STATE_TX2TX        ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_TX2TX)
#define RAIL_RAC_STATE_SHUTDOWN     ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_SHUTDOWN)
#if _SILICON_LABS_32B_SERIES_2_CONFIG >= 2
#define RAIL_RAC_STATE_POR          ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_POR)
#endif
#define RAIL_RAC_STATE_NONE         ((RAIL_RadioStateEfr32_t) RAIL_RAC_STATE_NONE)
#endif//DOXYGEN_SHOULD_SKIP_THIS

#ifndef DOXYGEN_SHOULD_SKIP_THIS
/**
 * @struct RAIL_RffpllConfig_t
 * @brief Stores information relevant to the Radio-Friendly Frequency
 *   Phase-Locked Loop (RFFPLL) for the PHY configuration currently loaded in
 *   memory.
 */
typedef struct {
  uint32_t dividers;      // Divider X (Modem Clock), Divider Y (M33 System Clock), and Divider N (Feedback)  values
  uint32_t radioFreqHz;   // Radio clock frequency in Hz
  uint32_t sysclkFreqHz;  // System clock frequency in Hz
} RAIL_RffpllConfig_t;

/**
 * @def RAIL_RFFPLL_DIVIDERX_MASK
 * @brief Bit mask for RFFPLL DIVX in \ref RAIL_RffpllConfig_t::dividers.
 */
#define RAIL_RFFPLL_DIVIDERX_MASK   0x000000FFUL

/**
 * @def RAIL_RFFPLL_DIVIDERX_SHIFT
 * @brief Shift value for RFFPLL DIVX in \ref RAIL_RffpllConfig_t::dividers.
 */
#define RAIL_RFFPLL_DIVIDERX_SHIFT  0

/**
 * @def RAIL_RFFPLL_DIVIDERY_MASK
 * @brief Bit mask for RFFPLL DIVY in \ref RAIL_RffpllConfig_t::dividers.
 */
#define RAIL_RFFPLL_DIVIDERY_MASK   0x0000FF00UL

/**
 * @def RAIL_RFFPLL_DIVIDERY_SHIFT
 * @brief Shift value for RFFPLL DIVY in \ref RAIL_RffpllConfig_t::dividers.
 */
#define RAIL_RFFPLL_DIVIDERY_SHIFT  8

/**
 * @def RAIL_RFFPLL_DIVIDERN_MASK
 * @brief Bit mask for RFFPLL DIVN in \ref RAIL_RffpllConfig_t::dividers.
 */
#define RAIL_RFFPLL_DIVIDERN_MASK   0x00FF0000UL

/**
 * @def RAIL_RFFPLL_DIVIDERN_SHIFT
 * @brief Shift value for RFFPLL DIVN in \ref RAIL_RffpllConfig_t::dividers.
 */
#define RAIL_RFFPLL_DIVIDERN_SHIFT  16
#endif//DOXYGEN_SHOULD_SKIP_THIS
/** @} */ // end of group General_EFR32XG2

// -----------------------------------------------------------------------------
// Multiprotocol
// -----------------------------------------------------------------------------
/**
 * @addtogroup Multiprotocol_EFR32 EFR32
 * @{
 * @brief EFR32-specific multiprotocol support defines
 * @ingroup Multiprotocol
 */

/**
 * @def TRANSITION_TIME_US
 * @brief Time it takes to take care of protocol switching.
 */
#if _SILICON_LABS_32B_SERIES_2_CONFIG > 1
// XG22 + devices
#define TRANSITION_TIME_US 510
#else
// XG21
#define TRANSITION_TIME_US 500
#endif

/** @} */ // end of group Multiprotocol_EFR32

// -----------------------------------------------------------------------------
// Antenna Control
// -----------------------------------------------------------------------------
/**
 * @addtogroup Antenna_Control_EFR32XG2X EFR32XG2X
 * @{
 * @brief EFR32 Antenna Control Functionality
 * @ingroup Antenna_Control
 *
 * These enumerations and structures are used with RAIL Antenna Control API. EFR32 supports
 * up to two antennas with configurable pin locations.
 */

/** Antenna path Selection enumeration. */
RAIL_ENUM(RAIL_AntennaSel_t) {
  /** Enum for antenna path 0. */
  RAIL_ANTENNA_0 = 0,
  /** Enum for antenna path 1. */
  RAIL_ANTENNA_1 = 1,
  /** Enum for antenna path auto. */
  RAIL_ANTENNA_AUTO = 255,
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_ANTENNA_0    ((RAIL_AntennaSel_t) RAIL_ANTENNA_0)
#define RAIL_ANTENNA_1    ((RAIL_AntennaSel_t) RAIL_ANTENNA_1)
#define RAIL_ANTENNA_AUTO ((RAIL_AntennaSel_t) RAIL_ANTENNA_AUTO)
#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @struct RAIL_AntennaConfig_t
 * @brief A configuration for antenna selection.
 */
typedef struct RAIL_AntennaConfig {
  /** Antenna 0 Pin Enable */
  bool ant0PinEn;
  /** Antenna 1 Pin Enable */
  bool ant1PinEn;
  /** Internal default RF path (EFR32 series 2);
   *  defaultPath is ignored on EFR32 series 2 parts that have only
   *  one RF path bonded out and on EFR32xG27 dual-band OPNs where
   *  the appropriate RF path is automatically set by RAIL to
   *  0 for 2.4GHZ band and 1 for SubGHz band PHYs. */
  RAIL_AntennaSel_t defaultPath;
  /** Antenna 0 output GPIO port */
  uint8_t ant0Port;
  /** Antenna 0 output GPIO pin */
  uint8_t ant0Pin;
  /** Reserved */
  uint8_t reserved;
  /** Antenna 1 output GPIO port */
  uint8_t ant1Port;
  /** Antenna 1 output GPIO pin */
  uint8_t ant1Pin;
} RAIL_AntennaConfig_t;

/** @} */ // end of group Antenna_Control_EFR32

// -----------------------------------------------------------------------------
// Calibration
// -----------------------------------------------------------------------------
/**
 * @addtogroup Calibration_EFR32XG2X EFR32XG2X
 * @{
 * @brief EFR32XG2X-specific Calibrations
 * @ingroup Calibration
 *
 * The EFR32 supports the Image Rejection (IR)
 * calibration and a temperature-dependent calibration. The IR calibration
 * can be computed once and stored off or computed each time at
 * startup. Because it is PHY-specific and provides sensitivity improvements,
 * it is highly recommended. The IR calibration should only be run when the
 * radio is IDLE.
 *
 * The temperature-dependent calibrations are used to recalibrate the synth if
 * the temperature crosses 0C or the temperature delta since the last
 * calibration exceeds 70C while in receive. RAIL will run the VCO calibration
 * automatically upon entering receive or transmit states, so the application
 * can omit this calibration if the stack re-enters receive or transmit with
 * enough frequency to avoid reaching the temperature delta. If the application
 * does not calibrate for temperature, it's possible to miss receive packets due
 * to a drift in the carrier frequency.
 */

/** EFR32-specific temperature calibration bit */
#define RAIL_CAL_TEMP_VCO         (0x00000001U)

#if RAIL_SUPPORTS_HFXO_COMPENSATION
/** EFR32-specific HFXO temperature check bit */
#define RAIL_CAL_TEMP_HFXO        (0x00000002U)
/** EFR32-specific HFXO compensation bit */
#define RAIL_CAL_COMPENSATE_HFXO  (0x00000004U)
#else
/** EFR32-specific HFXO temperature check bit */
#define RAIL_CAL_TEMP_HFXO        (0U)
/** EFR32-specific HFXO compensation bit */
#define RAIL_CAL_COMPENSATE_HFXO  (0U)
#endif

/** EFR32-specific IR calibration bit */
#define RAIL_CAL_RX_IRCAL         (0x00010000U)

#if RAIL_SUPPORTS_OFDM_PA
/** EFR32-specific Tx IR calibration bit */
#define RAIL_CAL_OFDM_TX_IRCAL    (0x00100000U)
#else
/** EFR32-specific Tx IR calibration bit */
#define RAIL_CAL_OFDM_TX_IRCAL    (0U)
#endif

/** EFR32-specific IR calibration bit */
#define RAIL_CAL_ONETIME_IRCAL    (RAIL_CAL_RX_IRCAL | RAIL_CAL_OFDM_TX_IRCAL)

/** A mask to run temperature-dependent calibrations */
#define RAIL_CAL_TEMP             (RAIL_CAL_TEMP_VCO | RAIL_CAL_TEMP_HFXO | RAIL_CAL_COMPENSATE_HFXO)
/** A mask to run one-time calibrations */
#define RAIL_CAL_ONETIME          (RAIL_CAL_ONETIME_IRCAL)
/** A mask to run optional performance calibrations */
#define RAIL_CAL_PERF             (0)
/** A mask for calibrations that require the radio to be off */
#define RAIL_CAL_OFFLINE          (RAIL_CAL_ONETIME_IRCAL)
/** A mask to run all possible calibrations for this chip */
#define RAIL_CAL_ALL              (RAIL_CAL_TEMP | RAIL_CAL_ONETIME)
/** A mask to run all pending calibrations */
#define RAIL_CAL_ALL_PENDING      (0x00000000U)
/** An invalid calibration value */
#define RAIL_CAL_INVALID_VALUE    (0xFFFFFFFFU)

/**
 * @def RAIL_RF_PATHS_2P4GIG
 * @brief Indicates the number of 2.4 GHz RF Paths suppported
 */
#ifndef RAIL_RF_PATHS_2P4GIG
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 1 || _SILICON_LABS_32B_SERIES_2_CONFIG == 4
#define RAIL_RF_PATHS_2P4GIG 2
#elif ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7)   \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 8))
#define RAIL_RF_PATHS_2P4GIG 1
#else
#define RAIL_RF_PATHS_2P4GIG 0
#endif

/**
 * @def RAIL_RF_PATHS_SUBGIG
 * @brief Indicates the number of sub-GHz RF Paths supported
 */
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 3
#define RAIL_RF_PATHS_SUBGIG 2
#elif  _SILICON_LABS_32B_SERIES_2_CONFIG == 5
#define RAIL_RF_PATHS_SUBGIG 2
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 8
#define RAIL_RF_PATHS_SUBGIG 1
#else
#define RAIL_RF_PATHS_SUBGIG 0
#endif
#endif //#ifndef RAIL_RF_PATHS_2P4GIG

/**
 * @def RAIL_RF_PATHS
 * @brief Indicates the number of RF Paths supported
 */
#define RAIL_RF_PATHS (RAIL_RF_PATHS_SUBGIG + RAIL_RF_PATHS_2P4GIG)

/**
 * @def RADIO_CONFIG_ENABLE_IRCAL_MULTIPLE_RF_PATHS
 * @brief Indicates this version of RAIL supports IR calibration on multiple RF paths
 * Needed for backwards compatibility.
 */
#if RAIL_RF_PATHS > 1
#define RADIO_CONFIG_ENABLE_IRCAL_MULTIPLE_RF_PATHS 1
#else
#ifdef  DOXYGEN_SHOULD_SKIP_THIS // Leave undefined except for doxygen
#define RADIO_CONFIG_ENABLE_IRCAL_MULTIPLE_RF_PATHS 0
#endif//DOXYGEN_SHOULD_SKIP_THIS
#endif

#if RAIL_SUPPORTS_OFDM_PA
/**
 * @typedef RAIL_TxIrCalValues_t
 * @brief A Tx IR calibration value structure.
 *
 * This definition contains the set of persistent calibration values for
 * OFDM on EFR32. You can set these beforehand and apply them at startup to save the
 * time required to compute them. Any of these values may be set to
 * RAIL_IRCAL_INVALID_VALUE to force the code to compute that calibration value.
 */
typedef struct RAIL_TxIrCalValues {
  uint32_t dcOffsetIQ;    // TXIRCAL result
  uint32_t phiEpsilon;    // TXIRCAL result
} RAIL_TxIrCalValues_t;

/**
 * A define to set all RAIL_TxIrCalValues_t values to uninitialized.
 *
 * This define can be used when you have no data to pass to the calibration
 * routines but wish to compute and save all possible calibrations.
 */
#define RAIL_IRCALVALUES_TX_UNINIT  { \
    RAIL_CAL_INVALID_VALUE,           \
    RAIL_CAL_INVALID_VALUE,           \
}

/**
 * @typedef RAIL_IrCalValues_t
 * @brief An IR calibration value structure.
 *
 * This definition contains the set of persistent calibration values for
 * EFR32. You can set these beforehand and apply them at startup to save the
 * time required to compute them. Any of these values may be set to
 * RAIL_IRCAL_INVALID_VALUE to force the code to compute that calibration value.
 */
typedef struct RAIL_IrCalValues {
  uint32_t rxIrCalValues[RAIL_RF_PATHS]; /**< An Image Rejection (IR) calibration value */
  RAIL_TxIrCalValues_t txIrCalValues; /**< An Image Rejection (IR) calibration value for OFDM Tx*/
} RAIL_IrCalValues_t;

/**
 * A define allowing Rx calibration value access compatibility
 * between series 1 and series 2.
 */
#define RAIL_IRCALVAL(irCalStruct, rfPath) \
  ((irCalStruct).rxIrCalValues[(rfPath)])

/**
 * A define to set all RAIL_IrCalValues_t values to uninitialized.
 *
 * This define can be used when you have no data to pass to the calibration
 * routines but wish to compute and save all possible calibrations.
 */
#if (RAIL_RF_PATHS == 2)
#define RAIL_IRCALVALUES_UNINIT {                       \
    { RAIL_CAL_INVALID_VALUE, RAIL_CAL_INVALID_VALUE }, \
    RAIL_IRCALVALUES_TX_UNINIT,                         \
}
#elif (RAIL_RF_PATHS == 1)
#define RAIL_IRCALVALUES_UNINIT { \
    { RAIL_CAL_INVALID_VALUE },   \
    RAIL_IRCALVALUES_TX_UNINIT,   \
}
#else
#error "This config is not valid, RAIL_RF_PATHS has to be either 1 or 2"
#endif

#else // RAIL_SUPPORTS_OFDM_PA
/**
 * @typedef RAIL_IrCalValues_t
 * @brief An IR calibration value structure.
 *
 * This definition contains the set of persistent calibration values for
 * EFR32. You can set these beforehand and apply them at startup to save the
 * time required to compute them. Any of these values may be set to
 * RAIL_IRCAL_INVALID_VALUE to force the code to compute that calibration value.
 */
typedef uint32_t RAIL_IrCalValues_t[RAIL_RF_PATHS];

/**
 * A define allowing Rx calibration value access compatibility
 * between series 1 and series 2.
 */
#define RAIL_IRCALVAL(irCalStruct, rfPath) \
  ((irCalStruct)[(rfPath)])

/**
 * A define to set all RAIL_IrCalValues_t values to uninitialized.
 *
 * This define can be used when you have no data to pass to the calibration
 * routines but wish to compute and save all possible calibrations.
 */
#if (RAIL_RF_PATHS == 2)
#define RAIL_IRCALVALUES_UNINIT { \
    RAIL_CAL_INVALID_VALUE,       \
    RAIL_CAL_INVALID_VALUE,       \
}
#elif (RAIL_RF_PATHS == 1)
#define RAIL_IRCALVALUES_UNINIT { \
    RAIL_CAL_INVALID_VALUE,       \
}
#else
#error "This config is not valid, RAIL_RF_PATHS has to be either 1 or 2"
#endif

#endif // RAIL_SUPPORTS_OFDM_PA

/**
 * @struct RAIL_ChannelConfigEntryAttr
 * @brief A channel configuration entry attribute structure. Items listed
 *  are designed to be altered and updated during run-time.
 */
struct RAIL_ChannelConfigEntryAttr {
  RAIL_IrCalValues_t calValues; /**< IR calibration attributes specific to
                                       each channel configuration entry. */
};

/**
 * Applies a given image rejection calibration value.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] imageRejection The image rejection value to apply.
 * @return A status code indicating success of the function call.
 *
 * Take an image rejection calibration value and apply it. This value should be
 * determined from a previous run of \ref RAIL_CalibrateIr on the same
 * physical device with the same radio configuration. The imageRejection value
 * will also be stored to the \ref RAIL_ChannelConfigEntry_t::attr, if possible.
 *
 * If multiple protocols are used, this function will return
 * \ref RAIL_STATUS_INVALID_STATE if it is called and the given railHandle is
 * not active. In that case, the caller must attempt to re-call this function later.
 *
 * @deprecated Please use \ref RAIL_ApplyIrCalibrationAlt instead.
 */
RAIL_Status_t RAIL_ApplyIrCalibration(RAIL_Handle_t railHandle,
                                      uint32_t imageRejection);

/**
 * Applies a given image rejection calibration value.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[in] imageRejection Pointer to the image rejection value to apply.
 * @param[in] rfPath RF path to calibrate.
 * @return A status code indicating success of the function call.
 *
 * Take an image rejection calibration value and apply it. This value should be
 * determined from a previous run of \ref RAIL_CalibrateIrAlt on the same
 * physical device with the same radio configuration. The imageRejection value
 * will also be stored to the \ref RAIL_ChannelConfigEntry_t::attr, if possible.
 * @note: To make sure the imageRejection value is stored/configured correctly,
 * \ref RAIL_ConfigAntenna should be called before calling this API.
 *
 * If multiple protocols are used, this function will return
 * \ref RAIL_STATUS_INVALID_STATE if it is called and the given railHandle is
 * not active. In that case, the caller must attempt to re-call this function later.
 */
RAIL_Status_t RAIL_ApplyIrCalibrationAlt(RAIL_Handle_t railHandle,
                                         RAIL_IrCalValues_t *imageRejection,
                                         RAIL_AntennaSel_t rfPath);

/**
 * Runs the image rejection calibration.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[out] imageRejection The result of the image rejection calibration.
 * @return A status code indicating success of the function call.
 *
 * Run the image rejection calibration and apply the resulting value. If the
 * imageRejection parameter is not NULL, store the value at that
 * location. The imageRejection value will also be stored to the
 * \ref RAIL_ChannelConfigEntry_t::attr, if possible. This is a long-running
 * calibration that adds significant code space when run and can be run with a
 * separate firmware image on each device to save code space in the
 * final image.
 *
 * If multiple protocols are used, this function will return
 * \ref RAIL_STATUS_INVALID_STATE if it is called and the given railHandle is
 * not active. In that case, the caller must attempt to re-call this function later.
 *
 * @deprecated Please use \ref RAIL_CalibrateIrAlt instead.
 */
RAIL_Status_t RAIL_CalibrateIr(RAIL_Handle_t railHandle,
                               uint32_t *imageRejection);

/**
 * Runs the image rejection calibration.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[out] imageRejection Pointer to the image rejection result.
 * @param[in] rfPath RF path to calibrate.
 * @return A status code indicating success of the function call.
 *
 * Run the image rejection calibration and apply the resulting value. If the
 * imageRejection parameter is not NULL, store the value at that
 * location. The imageRejection value will also be stored to the
 * \ref RAIL_ChannelConfigEntry_t::attr, if possible. This is a long-running
 * calibration that adds significant code space when run and can be run with a
 * separate firmware image on each device to save code space in the
 * final image.
 * @note: To make sure the imageRejection value is stored/configured correctly,
 * \ref RAIL_ConfigAntenna should be called before calling this API.
 *
 * If multiple protocols are used, this function will return
 * \ref RAIL_STATUS_INVALID_STATE if it is called and the given railHandle is
 * not active. In that case, the caller must attempt to re-call this function later.
 */
RAIL_Status_t RAIL_CalibrateIrAlt(RAIL_Handle_t railHandle,
                                  RAIL_IrCalValues_t *imageRejection,
                                  RAIL_AntennaSel_t rfPath);

/**
 * Calibrates image rejection for IEEE 802.15.4 2.4 GHz
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[out] imageRejection The result of the image rejection calibration.
 * @return A status code indicating success of the function call.
 *
 * Some chips have protocol-specific image rejection calibrations programmed
 * into their flash. This function will either get the value from flash and
 * apply it, or run the image rejection algorithm to find the value.
 */
RAIL_Status_t RAIL_IEEE802154_CalibrateIr2p4Ghz(RAIL_Handle_t railHandle,
                                                uint32_t *imageRejection);

/**
 * Calibrates image rejection for IEEE 802.15.4 915 MHz and 868 MHz
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[out] imageRejection The result of the image rejection calibration.
 * @return A status code indicating success of the function call.
 *
 * Some chips have protocol-specific image rejection calibrations programmed
 * into their flash. This function will either get the value from flash and
 * apply it, or run the image rejection algorithm to find the value.
 *
 * @deprecated Please use \ref RAIL_CalibrateIrAlt instead.
 */
RAIL_Status_t RAIL_IEEE802154_CalibrateIrSubGhz(RAIL_Handle_t railHandle,
                                                uint32_t *imageRejection);

/**
 * Calibrates image rejection for Bluetooth Low Energy
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[out] imageRejection The result of the image rejection calibration.
 * @return A status code indicating success of the function call.
 *
 * Some chips have protocol-specific image rejection calibrations programmed
 * into their flash. This function will either get the value from flash and
 * apply it, or run the image rejection algorithm to find the value.
 */
RAIL_Status_t RAIL_BLE_CalibrateIr(RAIL_Handle_t railHandle,
                                   uint32_t *imageRejection);

/**
 * Runs the temperature calibration.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @return A status code indicating success of the function call.
 *
 * Run the temperature calibration, which needs to recalibrate the synth if
 * the temperature crosses 0C or the temperature delta since the last
 * calibration exceeds 70C while in receive. RAIL will run the VCO calibration
 * automatically upon entering receive or transmit states, so the application
 * can omit this calibration if the stack re-enters receive or transmit with
 * enough frequency to avoid reaching the temperature delta. If the application
 * does not calibrate for temperature, it's possible to miss receive packets due
 * to a drift in the carrier frequency.
 *
 * If multiple protocols are used, this function will return
 * \ref RAIL_STATUS_INVALID_STATE if it is called and the given railHandle is
 * not active. In that case, the calibration will be automatically performed
 * next time the radio enters receive.
 */
RAIL_Status_t RAIL_CalibrateTemp(RAIL_Handle_t railHandle);

/**
 * Performs HFXO compensation.
 *
 * @param[in] railHandle A RAIL instance handle.
 * @param[out] crystalPPMError Current deviation that has been corrected,
 *   measured in PPM. May be NULL.
 * @return A status code indicating the result of the function call.
 *
 * Compute the PPM correction using the thermistor value available when
 * \ref RAIL_EVENT_THERMISTOR_DONE occurs, after
 * \ref RAIL_StartThermistorMeasurement() call.
 * Then correct the RF frequency as well as Tx and Rx sampling.
 *
 * This function calls the following RAIL functions in sequence saving having
 * to call them individually:
 *   - \ref RAIL_ConvertThermistorImpedance()
 *   - \ref RAIL_ComputeHFXOPPMError()
 *   - \ref RAIL_CompensateHFXO()
 *
 * @note This function makes the radio idle.
 */
RAIL_Status_t RAIL_CalibrateHFXO(RAIL_Handle_t railHandle, int8_t *crystalPPMError);

/**
 * @typedef RAIL_CalValues_t
 * @brief A calibration value structure.
 *
 * This structure contains the set of persistent calibration values for
 * EFR32. You can set these beforehand and apply them at startup to save the
 * time required to compute them. Any of these values may be set to
 * RAIL_CAL_INVALID_VALUE to force the code to compute that calibration value.
 */
typedef RAIL_IrCalValues_t RAIL_CalValues_t;

/**
 * A define to set all RAIL_CalValues_t values to uninitialized.
 *
 * This define can be used when you have no data to pass to the calibration
 * routines but wish to compute and save all possible calibrations.
 */
#define RAIL_CALVALUES_UNINIT RAIL_IRCALVALUES_UNINIT

/** @} */ // end of group Calibration_EFR32

// -----------------------------------------------------------------------------
// Diagnostic
// -----------------------------------------------------------------------------
/**
 * @addtogroup Diagnostic_EFR32 EFR32
 * @{
 * @brief Types specific to the EFR32 for the diagnostic routines.
 * @ingroup Diagnostic
 */

/**
 * @typedef RAIL_FrequencyOffset_t
 * @brief Chip-specific type that represents the number of Frequency Offset
 *   units. It is used with \ref RAIL_GetRxFreqOffset() and
 *   \ref RAIL_SetFreqOffset().
 *
 * The units on this chip are radio synthesizer resolution steps (synthTicks).
 * On EFR32 (at least for now), the frequency offset is limited to 15 bits
 * (size of SYNTH_CALOFFSET). A value of \ref RAIL_FREQUENCY_OFFSET_INVALID
 * means that this value is invalid.
 */
typedef int16_t RAIL_FrequencyOffset_t;

/**
 * The maximum frequency offset value supported by this radio.
 */
#define RAIL_FREQUENCY_OFFSET_MAX ((RAIL_FrequencyOffset_t) 0x3FFF)

/**
 * The minimum frequency offset value supported by this radio.
 */
#define RAIL_FREQUENCY_OFFSET_MIN ((RAIL_FrequencyOffset_t) -RAIL_FREQUENCY_OFFSET_MAX)

/**
 * Specify an invalid frequency offset value. This will be returned if you
 * call \ref RAIL_GetRxFreqOffset() at an invalid time.
 */
#define RAIL_FREQUENCY_OFFSET_INVALID ((RAIL_FrequencyOffset_t) 0x8000)

/**
 * @struct RAIL_DirectModeConfig_t
 * @brief Chip-specific type that allows the user to specify direct mode
 *   parameters using \ref RAIL_ConfigDirectMode().
 */
typedef struct RAIL_DirectModeConfig {
  /** Enable synchronous RX DOUT using DCLK vs. asynchronous RX DOUT. */
  bool syncRx;
  /** Enable synchronous TX DIN using DCLK vs. asynchronous TX DIN. */
  bool syncTx;

  /** Only used with directRx */
  /** Data output (DOUT) GPIO port */
  uint8_t doutPort;
  /** Data output (DOUT) GPIO pin */
  uint8_t doutPin;

  /** Only used in synchronous mode */
  /** Data clock (DCLK) GPIO port. Only used in synchronous mode */
  uint8_t dclkPort;
  /** Data clock (DCLK) GPIO pin. Only used in synchronous mode */
  uint8_t dclkPin;

  /** Only used with directTx */
  /** Data frame (DIN) GPIO port */
  uint8_t dinPort;
  /** Data frame (DIN) GPIO pin */
  uint8_t dinPin;

  /** Reserved for future use */
  uint8_t reserved[3];
} RAIL_DirectModeConfig_t;

/** @} */ // end of group Diagnostic_EFR32

// -----------------------------------------------------------------------------
// Radio Configuration
// -----------------------------------------------------------------------------
/**
 * @addtogroup Radio_Configuration_EFR32 EFR32
 * @{
 * @ingroup Radio_Configuration
 * @brief Types specific to the EFR32 for radio configuration.
 */

/**
 * @brief The radio configuration structure.
 *
 * The radio configuration properly configures the
 * radio for operation on a protocol. These configurations should not be
 * created or edited by hand.
 */
typedef const uint32_t *RAIL_RadioConfig_t;

/** @} */ // end of group Radio_Configuration_EFR32

// -----------------------------------------------------------------------------
// Transmit
// -----------------------------------------------------------------------------
/**
 * @addtogroup PA_EFR32XG2X EFR32XG2X
 * @{
 * @ingroup PA
 * @brief Types specific to the EFR32 for dealing with the on-chip PAs.
 */

/**
 * Raw power levels used directly by the RAIL_Get/SetTxPower API where a higher
 * numerical value corresponds to a higher output power. These are referred to
 * as 'raw (values/units)'. On EFR32, they can range from one of \ref
 * RAIL_TX_POWER_LEVEL_2P4_LP_MIN, \ref RAIL_TX_POWER_LEVEL_2P4_HP_MIN, or
 * \ref RAIL_TX_POWER_LEVEL_SUBGIG_HP_MIN to one of \ref
 * RAIL_TX_POWER_LEVEL_2P4_LP_MAX, \ref RAIL_TX_POWER_LEVEL_2P4_HP_MAX, and \ref
 * RAIL_TX_POWER_LEVEL_SUBGIG_HP_MAX, respectively, depending on the selected \ref
 * RAIL_TxPowerMode_t.
 */
typedef uint8_t RAIL_TxPowerLevel_t;

/**
 * PA power setting used directly by the \ref RAIL_GetPaPowerSetting() and
 * \ref RAIL_SetPaPowerSetting() APIs which is decoded to the actual
 * hardware register value(s).
 */
typedef uint32_t RAIL_PaPowerSetting_t;

/**
 * Returned by \ref RAIL_SetPaPowerSetting when the current PA does
 * not support the dBm to power setting mapping table.
 */
#define RAIL_TX_PA_POWER_SETTING_UNSUPPORTED     (0U)

#if _SILICON_LABS_32B_SERIES_2_CONFIG == 1
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_HP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_HP_MAX     (180U)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_HP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_HP_MIN     (1U)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_MP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_MP_MAX     (90U)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_MP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_MP_MIN     (1U)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LP_MAX     (64U)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LP_MIN     (0U)
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 4
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_HP mode.
 *  EFR32XG24: capable of 20dBm max output power has max powerlevel:180
 *  EFR32XG24: capable of 10dBm max output power has max powerlevel:90
 */
#if defined (_SILICON_LABS_EFR32_2G4HZ_HP_PA_PRESENT) \
  && (_SILICON_LABS_EFR32_2G4HZ_HP_PA_MAX_OUTPUT_DBM > 10)
#define RAIL_TX_POWER_LEVEL_2P4_HP_MAX     (180U)
#else
#define RAIL_TX_POWER_LEVEL_2P4_HP_MAX     (90U)
#endif
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_HP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_HP_MIN     (0U)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LP_MAX     (15U)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LP_MIN     (0U)
#elif ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_HP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_HP_MAX     (127U)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_HP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_HP_MIN     (0U)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LP_MAX     (15U)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LP_MIN     (0U)
#else //efr32xg23
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_HP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_HP_MAX     (240)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_HP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_HP_MIN     (1U)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_MP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_MP_MAX     (RAIL_TX_POWER_LEVEL_2P4_HP_MAX)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_MP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_MP_MIN     (RAIL_TX_POWER_LEVEL_2P4_HP_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LP_MAX     (RAIL_TX_POWER_LEVEL_2P4_HP_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LP_MIN     (RAIL_TX_POWER_LEVEL_2P4_HP_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LLP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LLP_MAX     (RAIL_TX_POWER_LEVEL_2P4_HP_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_2P4_LLP mode.
 */
#define RAIL_TX_POWER_LEVEL_2P4_LLP_MIN     (RAIL_TX_POWER_LEVEL_2P4_HP_MIN)
#endif //_SILICON_LABS_32B_SERIES_2_CONFIG

#if RAIL_FEAT_SUBGIG_RADIO
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 3 || _SILICON_LABS_32B_SERIES_2_CONFIG == 8
#ifndef RAIL_SUBGIG_MAX
#define RAIL_SUBGIG_MAX 240U
#endif
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 5
#define RAIL_SUBGIG_MAX 79U
#endif
#define RAIL_SUBGIG_MIN 1U

/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_HP_MAX (RAIL_SUBGIG_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_HP_MIN (RAIL_SUBGIG_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_MP mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_MP_MAX (RAIL_SUBGIG_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_MP mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_MP_MIN (RAIL_SUBGIG_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_LP_MAX (RAIL_SUBGIG_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_LP mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_LP_MIN (RAIL_SUBGIG_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_LLP mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_LLP_MAX (RAIL_SUBGIG_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_LLP mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_LLP_MIN (RAIL_SUBGIG_MIN)
#if RAIL_SUPPORTS_EFF
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_EFF_30DBM_MAX (RAIL_SUBGIG_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_EFF_30DBM_MIN (RAIL_SUBGIG_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_EFF_25DBM_MAX (RAIL_SUBGIG_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_EFF_25DBM_MIN (RAIL_SUBGIG_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_EFF_20DBM_MAX (RAIL_SUBGIG_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_SUBGIG_EFF_20DBM_MIN (RAIL_SUBGIG_MIN)
#endif
#endif //RAIL_FEAT_SUBGIG_RADIO

#if RAIL_SUPPORTS_OFDM_PA
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 5
#define RAIL_OFDM_PA_MAX      204U
#define RAIL_OFDM_PA_EFF_MAX  204U
#define RAIL_OFDM_PA_MULT     5U
#define RAIL_OFDM_PA_MIN      0U
#define RAIL_OFDM_PA_EFF_MIN  0U
#endif
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_MAX (RAIL_OFDM_PA_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_MIN (RAIL_OFDM_PA_MIN)
#if RAIL_SUPPORTS_EFF
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_30DBM_MAX (RAIL_OFDM_PA_EFF_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_30DBM_MIN (RAIL_OFDM_PA_EFF_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_25DBM_MAX (RAIL_OFDM_PA_EFF_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA_EFF_250DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_25DBM_MIN (RAIL_OFDM_PA_EFF_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_20DBM_MAX (RAIL_OFDM_PA_EFF_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_20DBM_MIN (RAIL_OFDM_PA_EFF_MIN)
/**
 * The maximum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_MAXDBM_MAX (RAIL_OFDM_PA_EFF_MAX)
/**
 * The minimum valid value for the \ref RAIL_TxPowerLevel_t when in \ref
 * RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM mode.
 */
#define RAIL_TX_POWER_LEVEL_OFDM_PA_EFF_MAXDBM_MIN (RAIL_OFDM_PA_EFF_MIN)
#endif
#endif //RAIL_SUPPORTS_OFDM_PA

/** Backwards compatability define */
#define RAIL_TX_POWER_LEVEL_HP_MAX      RAIL_TX_POWER_LEVEL_2P4_HP_MAX
/** Backwards compatability define */
#define RAIL_TX_POWER_LEVEL_HP_MIN      RAIL_TX_POWER_LEVEL_2P4_HP_MIN
/** Backwards compatability define */
#define RAIL_TX_POWER_LEVEL_MP_MAX      RAIL_TX_POWER_LEVEL_2P4_MP_MAX
/** Backwards compatability define */
#define RAIL_TX_POWER_LEVEL_MP_MIN      RAIL_TX_POWER_LEVEL_2P4_MP_MIN
/** Backwards compatability define */
#define RAIL_TX_POWER_LEVEL_LP_MAX      RAIL_TX_POWER_LEVEL_2P4_LP_MAX
/** Backwards compatability define */
#define RAIL_TX_POWER_LEVEL_LP_MIN      RAIL_TX_POWER_LEVEL_2P4_LP_MIN
/** Backwards compatability define */
#define RAIL_TX_POWER_LEVEL_SUBGIG_MAX  RAIL_TX_POWER_LEVEL_SUBGIG_HP_MAX
/** Backwards compatability define */
#define RAIL_TX_POWER_LEVEL_SUBGIG_MIN  RAIL_TX_POWER_LEVEL_SUBGIG_HP_MIN

/**
 * Invalid RAIL_TxPowerLevel_t value returned when an error occurs
 * with RAIL_GetTxPower.
 */
#define RAIL_TX_POWER_LEVEL_INVALID (255U)
/**
 * Sentinel value that can be passed to RAIL_SetTxPower to set
 * the highest power level available on the current PA, regardless
 * of which one is selected.
 */
#define RAIL_TX_POWER_LEVEL_MAX (254U)

/**
 * @enum RAIL_TxPowerMode_t
 * @brief An enumeration of the EFR32 power modes.
 *
 * The power modes on the EFR32 correspond to the different on-chip PAs that
 * are available. For more information about the power and performance
 * characteristics of a given amplifier, see the data sheet.
 */
#ifndef RAIL_INTERNAL_TXPOWERMODE
RAIL_ENUM(RAIL_TxPowerMode_t) {
#if RAIL_FEAT_2G4_RADIO
  /**
   *  High-power 2.4 GHz amplifier
   *  EFR32XG21: up to 20 dBm, raw values: 1-180
   *  EFR32XG22: up to 6 dBm, raw values: 1-128
   *  EFR32XG24: capable of 20dBm max output power supports powerlevel: 0-180
   *  EFR32XG24: capable of 10dBm max output power supports powerlevel: 0-90
   *  EFR32XG28: capable of 10dBm max output power supports powerlevel: 0-240
   */
  RAIL_TX_POWER_MODE_2P4GIG_HP,
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 1) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 8))
  /**
   *  Mid-power 2.4 GHz amplifier
   *  EFR32XG21: up to 10 dBm, raw values: 1-90
   *  EFR32XG22: N/A
   */
  RAIL_TX_POWER_MODE_2P4GIG_MP,
#endif
#if _SILICON_LABS_32B_SERIES_2_CONFIG != 3
  /**
   *  Low-power 2.4 GHz amplifier
   *  EFR32XG21: up to 0 dBm, raw values: 1-64
   *  EFR32XG22: up to 0 dBm, raw values: 1-16
   *  EFR32XG24: up to 0 dBm, raw values: 1-16
   */
  RAIL_TX_POWER_MODE_2P4GIG_LP,
#endif
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 8
  /** Low-Low-power 2.4GHz amplifier */
  RAIL_TX_POWER_MODE_2P4GIG_LLP,
#endif
  /** Select the highest power PA available on the current chip. */
  RAIL_TX_POWER_MODE_2P4GIG_HIGHEST,
#endif
#if RAIL_FEAT_SUBGIG_RADIO
#if RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
  /** PA for all dBm values in range, using RAIL_PaPowerSetting_t table */
  RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE,
#else
  /** High-power amplifier (Class D mode) */
  RAIL_TX_POWER_MODE_SUBGIG_HP,
  /** @deprecated Please use \ref RAIL_TX_POWER_MODE_SUBGIG_HP instead. */
  RAIL_TX_POWER_MODE_SUBGIG = RAIL_TX_POWER_MODE_SUBGIG_HP,
  /** Mid-power amplifier */
  RAIL_TX_POWER_MODE_SUBGIG_MP,
  /** Low-power amplifier */
  RAIL_TX_POWER_MODE_SUBGIG_LP,
  /** Low-Low-power amplifier */
  RAIL_TX_POWER_MODE_SUBGIG_LLP,
#endif //RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
  /** Select the highest power PA available on the current chip. */
  RAIL_TX_POWER_MODE_SUBGIG_HIGHEST,
#endif//RAIL_FEAT_SUBGIG_RADIO
#if RAIL_SUPPORTS_OFDM_PA
#if RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
  /** PA for all dBm values in range, using RAIL_PaPowerSetting_t table */
  RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE,
  /** @deprecated Please use \ref RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE instead. */
  RAIL_TX_POWER_MODE_OFDM_PA,
#else
#error "RAIL_SUPPORTS_OFDM_PA is true, but there is no OFDM PA defined for this chip."
#endif //RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#endif//RAIL_SUPPORTS_OFDM_PA
#if RAIL_SUPPORTS_EFF
//Added after the normal PAs so old code doesn't accidentally use the wrong PA
#if RAIL_FEAT_SUBGIG_RADIO
  // EFF requires custom PAs. Normal PAs all use passthrough mode.
  /** Danger, may overtemp EFF. Use power protection! */
  RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM,
  /** Danger, may overtemp EFF. Use power protection! */
  RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM,
  /** Below 15 dBm use passthrough PAs */
  RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM,
#if RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
  /** PA for all dBm values in range, for Front-End-Module, using RAIL_PaPowerSetting_t table */
  RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE,
#endif //RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#endif//RAIL_FEAT_SUBGIG_RADIO
#if RAIL_SUPPORTS_OFDM_PA
  // EFF requires custom PAs. Normal PAs all use passthrough mode.
  /** Danger, may overtemp EFF. Use power protection! */
  RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM,
  /** Danger, may overtemp EFF. Use power protection! */
  RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM,
  /** Below 15 dBm use passthrough PAs */
  RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM,
  /** Special PA sending full Sol output. Use carefully */
  RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM,
#if RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
  /** PA for all dBm values in range, for Front-End-Module, using RAIL_PaPowerSetting_t table */
  RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE,
#endif //RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#endif//RAIL_SUPPORTS_OFDM_PA
#endif//RAIL_SUPPORTS_EFF
  /** Invalid amplifier Selection */
  RAIL_TX_POWER_MODE_NONE,
};
#endif //#ifndef RAIL_INTERNAL_TXPOWERMODE

#if RAIL_FEAT_2G4_RADIO
/** @deprecated Please use \ref RAIL_TX_POWER_MODE_2P4GIG_HP instead. */
#define RAIL_TX_POWER_MODE_2P4_HP       RAIL_TX_POWER_MODE_2P4GIG_HP
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 1) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 8))
/** @deprecated Please use \ref RAIL_TX_POWER_MODE_2P4GIG_MP instead. */
#define RAIL_TX_POWER_MODE_2P4_MP       RAIL_TX_POWER_MODE_2P4GIG_MP
#endif
#if _SILICON_LABS_32B_SERIES_2_CONFIG != 3
/** @deprecated Please use \ref RAIL_TX_POWER_MODE_2P4GIG_LP instead. */
#define RAIL_TX_POWER_MODE_2P4_LP       RAIL_TX_POWER_MODE_2P4GIG_LP
#endif
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 8
/** @deprecated Please use \ref RAIL_TX_POWER_MODE_2P4GIG_LLP instead. */
#define RAIL_TX_POWER_MODE_2P4_LLP       RAIL_TX_POWER_MODE_2P4GIG_LLP
#endif
/** @deprecated Please use \ref RAIL_TX_POWER_MODE_2P4GIG_HIGHEST instead. */
#define RAIL_TX_POWER_MODE_2P4_HIGHEST  RAIL_TX_POWER_MODE_2P4GIG_HIGHEST
#endif

/**
 * The number of PA's on this chip. (Including Virtual PAs)
 */
#ifndef RAIL_NUM_PA
#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 4) \
  || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
#define RAIL_NUM_PA (2U)
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 3)
#define RAIL_NUM_PA (4U)
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 8)
// There is a "dummy" PA for RAIL_TX_POWER_MODE_2P4GIG_HIGHEST which maps back to
// RAIL_TX_POWER_MODE_2P4GIG_HP power curves. This explains why this value is 9 instead of 8.
#define RAIL_NUM_PA (9U)
#elif (_SILICON_LABS_32B_SERIES_2_CONFIG == 5)
#if RAIL_SUPPORTS_EFF
#define RAIL_NUM_PA (13U)
#else
#define RAIL_NUM_PA (2U)
#endif
#else
#define RAIL_NUM_PA (3U)
#endif
#endif //#ifndef RAIL_NUM_PA

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#if RAIL_FEAT_2G4_RADIO
#ifndef RAIL_TX_POWER_MODE_2P4GIG_HP
#define RAIL_TX_POWER_MODE_2P4GIG_HP ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_2P4GIG_HP)
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 1 || _SILICON_LABS_32B_SERIES_2_CONFIG == 8
#define RAIL_TX_POWER_MODE_2P4GIG_MP ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_2P4GIG_MP)
#endif //_SILICON_LABS_32B_SERIES_2_CONFIG == 1 || _SILICON_LABS_32B_SERIES_2_CONFIG == 8
#if _SILICON_LABS_32B_SERIES_2_CONFIG != 3
#define RAIL_TX_POWER_MODE_2P4GIG_LP ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_2P4GIG_LP)
#endif //_SILICON_LABS_32B_SERIES_2_CONFIG != 3
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 8
#define RAIL_TX_POWER_MODE_2P4GIG_LLP ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_2P4GIG_LLP)
#endif // _SILICON_LABS_32B_SERIES_2_CONFIG == 8
#define RAIL_TX_POWER_MODE_2P4GIG_HIGHEST ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_2P4GIG_HIGHEST)
#endif //#ifndef RAIL_TX_POWER_MODE_2P4GIG_HP
#endif //RAIL_FEAT_2G4_RADIO

#if RAIL_FEAT_SUBGIG_RADIO
#if RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#define RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE      ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE)
#else
#define RAIL_TX_POWER_MODE_SUBGIG_HP                      ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_HP)
#define RAIL_TX_POWER_MODE_SUBGIG_MP                      ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_MP)
#define RAIL_TX_POWER_MODE_SUBGIG_LP                      ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_LP)
#define RAIL_TX_POWER_MODE_SUBGIG_LLP                     ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_LLP)
#define RAIL_TX_POWER_MODE_SUBGIG                         ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG)
#endif //RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#define RAIL_TX_POWER_MODE_SUBGIG_HIGHEST                 ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_HIGHEST)
#if RAIL_SUPPORTS_EFF
#define RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM               ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM)
#define RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM               ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM)
#define RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM               ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM)
#define RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE  ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE)
#endif//RAIL_SUPPORTS_EFF
#endif //RAIL_FEAT_SUBGIG_RADIO
#if RAIL_SUPPORTS_OFDM_PA
#if RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#define RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE      ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE)
#define RAIL_TX_POWER_MODE_OFDM_PA                         ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_OFDM_PA)
#endif //RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#if RAIL_SUPPORTS_EFF
#define RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM               ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM)
#define RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM               ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM)
#define RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM               ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM)
#define RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM              ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM)
#define RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE  ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE)
#endif//RAIL_SUPPORTS_EFF
#endif //RAIL_SUPPORTS_OFDM_PA
#define RAIL_TX_POWER_MODE_NONE   ((RAIL_TxPowerMode_t) RAIL_TX_POWER_MODE_NONE)
#endif//DOXYGEN_SHOULD_SKIP_THIS

#if _SILICON_LABS_32B_SERIES_2_CONFIG == 5
#if RAIL_SUPPORTS_EFF
#define RAIL_POWER_MODE_IS_ANY_EFF(x) ( ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE)   \
                                        || ((x) == RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE) \
                                        || ((x) == RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM)              \
                                        || ((x) == RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM)              \
                                        || ((x) == RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM)              \
                                        || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM)             \
                                        || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM)             \
                                        || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM)             \
                                        || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM)            \
                                        )
#define RAIL_POWER_MODE_IS_DBM_POWERSETTING_MAPPING_TABLE_OFDM(x)   ( ((x) == RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE) \
                                                                      || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE) )
#define RAIL_POWER_MODE_IS_DBM_POWERSETTING_MAPPING_TABLE_SUBGIG(x) ( ((x) == RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE) \
                                                                      || ((x) == RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE) )
#define RAIL_POWER_MODE_IS_ANY_DBM_POWERSETTING_MAPPING_TABLE(x)    ( (((x) == RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE)        \
                                                                       || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE) \
                                                                       || ((x) == RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE)      \
                                                                       || ((x) == RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE)) )
#if RAIL_IEEE802154_SUPPORTS_DUAL_PA_CONFIG
// This macro is a boolean that checks for any OFDM modes
#define RAIL_POWER_MODE_IS_ANY_OFDM(x) (   ((x) == RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE)        \
                                           || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE) \
                                           || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM)              \
                                           || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM)              \
                                           || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM)              \
                                           || ((x) == RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM)             \
                                           )
#endif
#else
#define RAIL_POWER_MODE_IS_ANY_EFF(x) (false)
#if RAIL_IEEE802154_SUPPORTS_DUAL_PA_CONFIG
// This macro is a boolean that checks for any OFDM modes
#define RAIL_POWER_MODE_IS_ANY_OFDM(x) ( ((x) == RAIL_TX_POWER_MODE_OFDM_PA) \
                                         )
#endif
#endif
#endif

#ifndef RAIL_TX_POWER_MODE_NAMES_2P4GIG
/**
 * @def RAIL_TX_POWER_MODE_NAMES_2P4GIG
 * @brief The names of the TX power modes for 2.4 GHz band.
 *
 * A list of the names for the TX power modes on the EFR32 series 2 parts
 * supporting 2.4 GHz operation.
 * This macro is useful for test applications and debugging output.
 */
#if RAIL_FEAT_2G4_RADIO
#if _SILICON_LABS_32B_SERIES_2_CONFIG == 1
#define RAIL_TX_POWER_MODE_NAMES_2P4GIG \
  "RAIL_TX_POWER_MODE_2P4GIG_HP",       \
  "RAIL_TX_POWER_MODE_2P4GIG_MP",       \
  "RAIL_TX_POWER_MODE_2P4GIG_LP",       \
  "RAIL_TX_POWER_MODE_2P4GIG_HIGHEST",
#elif _SILICON_LABS_32B_SERIES_2_CONFIG == 8
#define RAIL_TX_POWER_MODE_NAMES_2P4GIG \
  "RAIL_TX_POWER_MODE_2P4GIG_HP",       \
  "RAIL_TX_POWER_MODE_2P4GIG_MP",       \
  "RAIL_TX_POWER_MODE_2P4GIG_LP",       \
  "RAIL_TX_POWER_MODE_2P4GIG_LLP",      \
  "RAIL_TX_POWER_MODE_2P4GIG_HIGHEST",
#else // (_SILICON_LABS_32B_SERIES_2_CONFIG == 2|4|7)
#define RAIL_TX_POWER_MODE_NAMES_2P4GIG \
  "RAIL_TX_POWER_MODE_2P4GIG_HP",       \
  "RAIL_TX_POWER_MODE_2P4GIG_LP",       \
  "RAIL_TX_POWER_MODE_2P4GIG_HIGHEST",
#endif
#else
#define RAIL_TX_POWER_MODE_NAMES_2P4GIG
#endif //RAIL_FEAT_2G4_RADIO
#endif

/**
 * @def RAIL_TX_POWER_MODE_NAMES_SUBGIG
 * @brief The names of the TX power modes for Sub-GHz band.
 *
 * A list of the names for the TX power modes on the EFR32 series 2 parts
 * supporting Sub-GHz operation.
 * This macro is useful for test applications and debugging output.
 */
#if RAIL_FEAT_SUBGIG_RADIO
#if RAIL_SUPPORTS_EFF
#define RAIL_TX_POWER_MODE_NAMES_SUBGIG           \
  "RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE", \
  "RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM",          \
  "RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM",          \
  "RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM",          \
  "RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE",
#else
#if RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#define RAIL_TX_POWER_MODE_NAMES_SUBGIG \
  "RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE",
#else
#define RAIL_TX_POWER_MODE_NAMES_SUBGIG \
  "RAIL_TX_POWER_MODE_SUBGIG_HP",       \
  "RAIL_TX_POWER_MODE_SUBGIG_MP",       \
  "RAIL_TX_POWER_MODE_SUBGIG_LP",       \
  "RAIL_TX_POWER_MODE_SUBGIG_LLP",      \
  "RAIL_TX_POWER_MODE_SUBGIG_HIGHEST",
#endif //RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#endif //
#else
#define RAIL_TX_POWER_MODE_NAMES_SUBGIG
#endif

/**
 * @def RAIL_TX_POWER_MODE_NAMES_OFDM_PA
 * @brief The names of the TX power modes for the OFDM PA.
 *
 * A list of the names for the TX power modes on EFR32 series 2 parts
 * with an OFDM PA.
 * This macro is useful for test applications and debugging output.
 */
#if RAIL_SUPPORTS_OFDM_PA
#define RAIL_TX_POWER_MODE_NAMES_OFDM_PA \
  "RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE",
#else
#define RAIL_TX_POWER_MODE_NAMES_OFDM_PA
#endif

/**
 * @def RAIL_TX_POWER_MODE_NAMES_SUBGIG_EFF
 * @brief The names of the TX power modes for Sub-GHz band with an EFF.
 *
 * A list of the names for the Sub-GHz TX power modes on EFR32 series 2 parts
 * with an EFF.
 * This macro is useful for test applications and debugging output.
 */
#if RAIL_SUPPORTS_EFF
#if RAIL_FEAT_SUBGIG_RADIO
#define RAIL_TX_POWER_MODE_NAMES_SUBGIG_EFF       \
  "RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM",          \
  "RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM",          \
  "RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM",          \
  "RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE", \
  "RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE",
#else
#define RAIL_TX_POWER_MODE_NAMES_SUBGIG_EFF
#endif
#else
#define RAIL_TX_POWER_MODE_NAMES_SUBGIG_EFF
#endif//RAIL_SUPPORTS_EFF

/**
 * @def RAIL_TX_POWER_MODE_NAMES_OFDM_PA_EFF
 * @brief The names of the TX power modes for the OFDM PA with an EFF.
 *
 * A list of the names for the TX power modes on EFR32 series 2 parts
 * with an OFDM PA and EFF.
 * This macro is useful for test applications and debugging output.
 */
#if RAIL_SUPPORTS_EFF
#if RAIL_SUPPORTS_OFDM_PA
#define RAIL_TX_POWER_MODE_NAMES_OFDM_PA_EFF       \
  "RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM",          \
  "RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM",          \
  "RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM",          \
  "RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM",         \
  "RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE", \
  "RAIL_TX_POWER_MODE_OFDM_PA",                    \
  "RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE",
#else
#define RAIL_TX_POWER_MODE_NAMES_OFDM_PA_EFF
#endif
#else
#define RAIL_TX_POWER_MODE_NAMES_OFDM_PA_EFF
#endif//RAIL_SUPPORTS_EFF

#if RAIL_SUPPORTS_DBM_POWERSETTING_MAPPING_TABLE
#define RAIL_TX_POWER_MODE_NAMES {                       \
    "RAIL_TX_POWER_MODE_SUBGIG_POWERSETTING_TABLE",      \
    "RAIL_TX_POWER_MODE_SUBGIG_HIGHEST",                 \
    "RAIL_TX_POWER_MODE_OFDM_PA_POWERSETTING_TABLE",     \
    "RAIL_TX_POWER_MODE_OFDM_PA",                        \
    "RAIL_TX_POWER_MODE_SUBGIG_EFF_30DBM",               \
    "RAIL_TX_POWER_MODE_SUBGIG_EFF_25DBM",               \
    "RAIL_TX_POWER_MODE_SUBGIG_EFF_20DBM",               \
    "RAIL_TX_POWER_MODE_SUBGIG_EFF_POWERSETTING_TABLE",  \
    "RAIL_TX_POWER_MODE_OFDM_PA_EFF_30DBM",              \
    "RAIL_TX_POWER_MODE_OFDM_PA_EFF_25DBM",              \
    "RAIL_TX_POWER_MODE_OFDM_PA_EFF_20DBM",              \
    "RAIL_TX_POWER_MODE_OFDM_PA_EFF_MAXDBM",             \
    "RAIL_TX_POWER_MODE_OFDM_PA_EFF_POWERSETTING_TABLE", \
    "RAIL_TX_POWER_MODE_NONE",                           \
}
#else
/**
 * @def RAIL_TX_POWER_MODE_NAMES
 * @brief The names of the TX power modes
 *
 * A list of the names for the TX power modes on the EFR32 series 2 parts. This
 * macro is useful for test applications and debugging output.
 */
#define RAIL_TX_POWER_MODE_NAMES {         \
    RAIL_TX_POWER_MODE_NAMES_2P4GIG        \
    RAIL_TX_POWER_MODE_NAMES_SUBGIG        \
    RAIL_TX_POWER_MODE_NAMES_OFDM_PA       \
    RAIL_TX_POWER_MODE_NAMES_SUBGIG_EFF    \
      RAIL_TX_POWER_MODE_NAMES_OFDM_PA_EFF \
    "RAIL_TX_POWER_MODE_NONE"              \
}
#endif

/**
 * @struct RAIL_TxPowerConfig_t
 *
 * @brief A structure containing values used to initialize the power amplifiers.
 */
typedef struct RAIL_TxPowerConfig {
  /** TX power mode */
  RAIL_TxPowerMode_t mode;
  /** Power amplifier supply voltage in mV, generally:
   *  DCDC supply ~ 1800 mV (1.8 V)
   *  Battery supply ~ 3300 mV (3.3 V)
   */
  uint16_t voltage;
  /** The amount of time to spend ramping for TX in uS. */
  uint16_t rampTime;
} RAIL_TxPowerConfig_t;

/** @} */ // end of group PA_EFR32

// -----------------------------------------------------------------------------
// PTI
// -----------------------------------------------------------------------------
/**
 * @addtogroup PTI_EFR32 EFR32
 * @{
 * @brief EFR32 PTI functionality
 * @ingroup PTI
 *
 * These enumerations and structures are used with RAIL PTI API. EFR32 supports
 * SPI and UART PTI and is configurable in terms of baud rates and pin PTI
 * pin locations.
 */

/** A channel type enumeration. */
RAIL_ENUM(RAIL_PtiMode_t) {
  /** Turn PTI off entirely. */
  RAIL_PTI_MODE_DISABLED,
  /** SPI mode. */
  RAIL_PTI_MODE_SPI,
  /** UART mode. */
  RAIL_PTI_MODE_UART,
  /** 9-bit UART mode. */
  RAIL_PTI_MODE_UART_ONEWIRE,
};

#ifndef DOXYGEN_SHOULD_SKIP_THIS
// Self-referencing defines minimize compiler complaints when using RAIL_ENUM
#define RAIL_PTI_MODE_DISABLED     ((RAIL_PtiMode_t) RAIL_PTI_MODE_DISABLED)
#define RAIL_PTI_MODE_SPI          ((RAIL_PtiMode_t) RAIL_PTI_MODE_SPI)
#define RAIL_PTI_MODE_UART         ((RAIL_PtiMode_t) RAIL_PTI_MODE_UART)
#define RAIL_PTI_MODE_UART_ONEWIRE ((RAIL_PtiMode_t) RAIL_PTI_MODE_UART_ONEWIRE)
#endif//DOXYGEN_SHOULD_SKIP_THIS

/**
 * @struct RAIL_PtiConfig_t
 * @brief A configuration for PTI.
 */
typedef struct RAIL_PtiConfig {
  /** Packet Trace mode (UART or SPI) */
  RAIL_PtiMode_t mode;
  /** Output baudrate for PTI in Hz */
  uint32_t baud;
  /** Data output (DOUT) location for pin/port */
  uint8_t doutLoc;
  /** Data output (DOUT) GPIO port */
  uint8_t doutPort;
  /** Data output (DOUT) GPIO pin */
  uint8_t doutPin;
  /** Data clock (DCLK) location for pin/port. Only used in SPI mode */
  uint8_t dclkLoc;
  /** Data clock (DCLK) GPIO port. Only used in SPI mode */
  uint8_t dclkPort;
  /** Data clock (DCLK) GPIO pin. Only used in SPI mode */
  uint8_t dclkPin;
  /** Data frame (DFRAME) location for pin/port */
  uint8_t dframeLoc;
  /** Data frame (DFRAME) GPIO port */
  uint8_t dframePort;
  /** Data frame (DFRAME) GPIO pin */
  uint8_t dframePin;
} RAIL_PtiConfig_t;

/** @} */ // end of group PTI_EFR32

/******************************************************************************
 * Calibration Structures
 *****************************************************************************/
/**
 * @addtogroup Calibration
 * @{
 */

/// Use this value with either TX or RX values in RAIL_SetPaCTune
/// to use whatever value is already set and do no update. This
/// value is provided to provide consistency across EFR32 chips,
/// but technically speaking, all PA capacitance tuning values are
/// invalid on EFR32XG21 parts, as RAIL_SetPaCTune is not supported
/// on those parts.
#define RAIL_PACTUNE_IGNORE (255U)

/** @} */ // end of group Calibration

// -----------------------------------------------------------------------------
// Retiming
// -----------------------------------------------------------------------------
/**
 * @addtogroup Retiming_EFR32 Retiming
 * @{
 * @brief EFR32-specific retiming capability.
 * @ingroup RAIL_API
 *
 * The EFR product families have many digital and analog modules that can run
 * in parallel with a radio. Such combinations can result in interference and
 * degradation on the radio RX sensitivity. Retiming have the capability to
 * modify the clocking of the digital modules to reduce such interference.
 */

/**
 * @enum RAIL_RetimeOptions_t
 * @brief Retiming options bit shifts.
 */
RAIL_ENUM(RAIL_RetimeOptions_t) {
  /** Shift position of \ref RAIL_RETIME_OPTION_HFXO bit */
  RAIL_RETIME_OPTION_HFXO_SHIFT = 0,
  /** Shift position of \ref RAIL_RETIME_OPTION_HFRCO bit */
  RAIL_RETIME_OPTION_HFRCO_SHIFT,
  /** Shift position of \ref RAIL_RETIME_OPTION_DCDC bit */
  RAIL_RETIME_OPTION_DCDC_SHIFT,
  /** Shift position of \ref RAIL_RETIME_OPTION_LCD bit */
  RAIL_RETIME_OPTION_LCD_SHIFT,
};

// RAIL_RetimeOptions_t bitmasks
/**
 * An option to configure HFXO retiming
 */
#define RAIL_RETIME_OPTION_HFXO \
  (1U << RAIL_RETIME_OPTION_HFXO_SHIFT)

/**
 * An option to configure HFRCO retiming
 */
#define RAIL_RETIME_OPTION_HFRCO \
  (1U << RAIL_RETIME_OPTION_HFRCO_SHIFT)

/**
 * An option to configure DCDC retiming
 */
#define RAIL_RETIME_OPTION_DCDC \
  (1U << RAIL_RETIME_OPTION_DCDC_SHIFT)

/**
 * An option to configure LCD retiming
 */
#define RAIL_RETIME_OPTION_LCD \
  (1U << RAIL_RETIME_OPTION_LCD_SHIFT)

/** A value representing no retiming options */
#define RAIL_RETIME_OPTIONS_NONE 0x0U

/** A value representing all retiming options */
#define RAIL_RETIME_OPTIONS_ALL 0xFFU

/**
 * Configure retiming options.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[in] mask A bitmask containing which options should be modified.
 * @param[in] options A bitmask containing desired configuration settings.
 *   Bit positions for each option are found in the \ref RAIL_RetimeOptions_t.
 * @return Status code indicating success of the function call.
 */
RAIL_Status_t RAIL_ConfigRetimeOptions(RAIL_Handle_t railHandle,
                                       RAIL_RetimeOptions_t mask,
                                       RAIL_RetimeOptions_t options);

/**
 * Gets currently configured retiming option.
 *
 * @param[in] railHandle A handle of RAIL instance.
 * @param[out] pOptions A pointer to configured retiming options
                        bitmask indicating which are enabled.
 * @return Status code indicating success of the function call.
 */
RAIL_Status_t RAIL_GetRetimeOptions(RAIL_Handle_t railHandle,
                                    RAIL_RetimeOptions_t *pOptions);

/**
 * Indicate that the DCDC peripheral bus clock enable has changed allowing
 * RAIL to react accordingly.
 *
 * @note This should be called after DCDC has been enabled or disabled.
 *
 * @return Status code indicating success of the function call.
 */
RAIL_Status_t RAIL_ChangedDcdc(void);

/** @} */ // end of group Retiming_EFR32

/******************************************************************************
 * RX Channel Hopping
 *****************************************************************************/
/**
 * @addtogroup Rx_Channel_Hopping RX Channel Hopping
 * @{
 */

#if _SILICON_LABS_32B_SERIES_2_CONFIG == 8
/// The static amount of memory needed per channel for channel hopping, measured
/// in 32 bit words, regardless of the size of radio configuration structures.
#define RAIL_CHANNEL_HOPPING_BUFFER_SIZE_PER_CHANNEL (61U)
#else
/// The static amount of memory needed per channel for channel hopping, measured
/// in 32 bit words, regardless of the size of radio configuration structures.
#define RAIL_CHANNEL_HOPPING_BUFFER_SIZE_PER_CHANNEL (54U)

#endif

/** @} */  // end of group Rx_Channel_Hopping

/**
 * @addtogroup Sleep
 * @{
 */

/// Default PRS channel to use when configuring sleep
#define RAIL_TIMER_SYNC_PRS_CHANNEL_DEFAULT  (7U)

#if ((_SILICON_LABS_32B_SERIES_2_CONFIG == 2) || (_SILICON_LABS_32B_SERIES_2_CONFIG == 7))
/// Default RTCC channel to use when configuring sleep
#define RAIL_TIMER_SYNC_RTCC_CHANNEL_DEFAULT (1U)
#else
/// Default RTCC channel to use when configuring sleep
#define RAIL_TIMER_SYNC_RTCC_CHANNEL_DEFAULT (0U)
#endif

/// Default timer synchronization configuration
#define RAIL_TIMER_SYNC_DEFAULT {         \
    RAIL_TIMER_SYNC_PRS_CHANNEL_DEFAULT,  \
    RAIL_TIMER_SYNC_RTCC_CHANNEL_DEFAULT, \
    RAIL_SLEEP_CONFIG_TIMERSYNC_ENABLED,  \
}

/** @} */ // end of group Sleep

/**
 * @addtogroup Data_Management_EFR32XG2X EFR32XG2X
 * @{
 * @ingroup Data_Management
 */

/// Fixed-width type indicating the needed alignment for RX and TX FIFOs. Note
/// that docs.silabs.com will incorrectly indicate that this is always a
/// uint8_t, but it does vary across RAIL platforms.
#if _SILICON_LABS_32B_SERIES_2_CONFIG >= 2
#define RAIL_FIFO_ALIGNMENT_TYPE uint32_t
#else
#define RAIL_FIFO_ALIGNMENT_TYPE uint8_t
#endif

/// Alignment that is needed for the RX and TX FIFOs.
#define RAIL_FIFO_ALIGNMENT (sizeof(RAIL_FIFO_ALIGNMENT_TYPE))

/** @} */ // end of group Data_Management_EFR32

/**
 * @addtogroup State_Transitions_EFR32XG2X
 * @{
 * @ingroup State_Transitions
 */

/**
 * @def RAIL_MINIMUM_TRANSITION_US
 * @brief The minimum value for a consistent RAIL transition
 * @note Transitions may need to be slower than this when using longer
 *   \ref RAIL_TxPowerConfig_t::rampTime values
 */
#define RAIL_MINIMUM_TRANSITION_US (100U)

/**
 * @def RAIL_MAXIMUM_TRANSITION_US
 * @brief The maximum value for a consistent RAIL transition
 */
#define RAIL_MAXIMUM_TRANSITION_US (1000000U)

/**
 * @typedef RAIL_TransitionTime_t
 * @brief Suitable type for the supported transition time range.
 */
typedef uint32_t RAIL_TransitionTime_t;

/** @} */ // end of group State_Transitions_EFR32

#ifdef __cplusplus
}
#endif

#endif //__RAIL_TYPES_H__

#endif //__RAIL_CHIP_SPECIFIC_H_
