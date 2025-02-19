/***************************************************************************//**
 * @file
 * @brief CPC SPI SECONDARY driver configuration file.
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

// <<< Use Configuration Wizard in Context Menu >>>

#ifndef SL_CPC_DRV_SPI_EUSART_MIKROE_SECONDARY_CONFIG_H
#define SL_CPC_DRV_SPI_EUSART_MIKROE_SECONDARY_CONFIG_H
#include "spidrv.h"

// <h> CPC-Secondary SPI Driver Configuration

// <o SL_CPC_DRV_SPI_MIKROE_RX_QUEUE_SIZE> Number of frame that can be queued in the driver receive queue
// <i> Default: 10
#define SL_CPC_DRV_SPI_MIKROE_RX_QUEUE_SIZE            10

// <o SL_CPC_DRV_SPI_MIKROE_TX_QUEUE_SIZE> Number of frame that can be queued in the driver transmit queue
// <i> Default: 10
#define SL_CPC_DRV_SPI_MIKROE_TX_QUEUE_SIZE            10

// <o SL_CPC_DRV_SPI_MIKROE_BITRATE> SPI bit rate
// <i> Default: 1000000
#define SL_CPC_DRV_SPI_MIKROE_BITRATE               1000000

// <o SL_CPC_DRV_SPI_MIKROE_CS_FALLING_EDGE_INT_NO> Chip Select Interrupt Number on Falling Edge
// <i> Default: 10
#define SL_CPC_DRV_SPI_MIKROE_CS_FALLING_EDGE_INT_NO  0

// <o SL_CPC_DRV_SPI_MIKROE_CS_RISING_EDGE_INT_NO> Chip Select Interrupt Number on Rising Edge
// <i> Default: 11
#define SL_CPC_DRV_SPI_MIKROE_CS_RISING_EDGE_INT_NO   1
// </h>

// <<< end of configuration section >>>

// <<< sl:start pin_tool >>>
// <gpio> SL_CPC_DRV_SPI_MIKROE_RX_IRQ
// $[GPIO_SL_CPC_DRV_SPI_MIKROE_RX_IRQ]
#define SL_CPC_DRV_SPI_MIKROE_RX_IRQ_PORT        gpioPortB
#define SL_CPC_DRV_SPI_MIKROE_RX_IRQ_PIN         1

// [GPIO_SL_CPC_DRV_SPI_MIKROE_RX_IRQ]$

// <eusart signal=TX,RX,SCLK,(CS)> SL_CPC_DRV_SPI_MIKROE
// $[EUSART_SL_CPC_DRV_SPI_MIKROE]
#define SL_CPC_DRV_SPI_MIKROE_PERIPHERAL         EUSART1
#define SL_CPC_DRV_SPI_MIKROE_PERIPHERAL_NO      1

// EUSART1 TX on PC03
#define SL_CPC_DRV_SPI_MIKROE_TX_PORT            gpioPortC
#define SL_CPC_DRV_SPI_MIKROE_TX_PIN             3

// EUSART1 RX on PC02
#define SL_CPC_DRV_SPI_MIKROE_RX_PORT            gpioPortC
#define SL_CPC_DRV_SPI_MIKROE_RX_PIN             2

// EUSART1 SCLK on PC01
#define SL_CPC_DRV_SPI_MIKROE_SCLK_PORT          gpioPortC
#define SL_CPC_DRV_SPI_MIKROE_SCLK_PIN           1

// EUSART1 CS on PC00
#define SL_CPC_DRV_SPI_MIKROE_CS_PORT            gpioPortC
#define SL_CPC_DRV_SPI_MIKROE_CS_PIN             0

// [EUSART_SL_CPC_DRV_SPI_MIKROE]$
// <<< sl:end pin_tool >>>

#endif /* SL_CPC_DRV_SPI_MIKROE_SECONDARY_CONFIG_H */
