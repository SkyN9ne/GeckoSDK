/**
 * @file
 * @copyright 2023 Silicon Laboratories Inc.
 */

#ifndef _ZW_CONFIG_RF_H_
#define _ZW_CONFIG_RF_H_

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Max Tx Power Configuration

// <o> The maximum allowed Tx power in deci dBm for Z-Wave Long Range network <140..200:1> <f.d>
// <i> The maximum allowed Tx power in deci dBm for Z-Wave Long Range network
// <i> Default: 200
#define APP_MAX_TX_POWER_LR  200

// <o> The maximum allowed Tx power in deci dBm for Z-Wave network <-100..140:1> <f.d>
// <i> The maximum allowed Tx power in deci dBm for Z-Wave network
// <i> Default: 0
#define APP_MAX_TX_POWER  0

// <o> The deci dBmoutput measured at a PA setting of 0dBm <-50..50:1> <f.d>
// <i> The deci dBm output measured at a PA setting of 0dBm
// <i> Default: 0
#define APP_MEASURED_0DBM_TX_POWER  0

// <q> Enable Radio Debug
// <i> Enable Radio Debug
// <i> Default: 0
#define ENABLE_RADIO_DEBUG  0

// </h>

// <<< end of configuration section >>>

#endif /* _ZW_CONFIG_RF_H_ */
