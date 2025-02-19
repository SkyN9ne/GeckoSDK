/***************************************************************************//**
 * @file
 * @brief Device initialization for HFXO.
 *******************************************************************************
 * # License
 * <b>Copyright 2019 Silicon Laboratories Inc. www.silabs.com</b>
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
#include "sl_device_init_hfxo.h"
#include "sl_device_init_hfxo_config.h"

#include "em_cmu.h"

// Fetch CTUNE value from USERDATA page as a manufacturing token
#define MFG_CTUNE_ADDR 0x0FE00100UL
#define MFG_CTUNE_VAL  (*((uint16_t *) (MFG_CTUNE_ADDR)))

sl_status_t sl_device_init_hfxo(void)
{
  CMU_HFXOInit_TypeDef hfxoInit = CMU_HFXOINIT_DEFAULT;
  hfxoInit.mode = SL_DEVICE_INIT_HFXO_MODE;

  if (SL_DEVICE_INIT_HFXO_MODE == cmuOscMode_External) {
    hfxoInit = (CMU_HFXOInit_TypeDef)CMU_HFXOINIT_EXTERNAL_CLOCK;
  }

  int ctune = -1;

#if defined(_DEVINFO_MODXOCAL_HFXOCTUNE_MASK)
  // Use HFXO tuning value from DEVINFO if available (PCB modules)
  if ((DEVINFO->MODULEINFO & _DEVINFO_MODULEINFO_HFXOCALVAL_MASK) == 0) {
    ctune = DEVINFO->MODXOCAL & _DEVINFO_MODXOCAL_HFXOCTUNE_MASK;
  }
#endif

  // Use HFXO tuning value from MFG token in UD page if not already set
  if ((ctune == -1) && (MFG_CTUNE_VAL != 0xFFFF)) {
    ctune = MFG_CTUNE_VAL;
  }

  // Use HFXO tuning value from configuration header as fallback
  if (ctune == -1) {
    ctune = SL_DEVICE_INIT_HFXO_CTUNE;
  }

  if (ctune != -1) {
    hfxoInit.ctuneSteadyState = ctune;
  }

  SystemHFXOClockSet(SL_DEVICE_INIT_HFXO_FREQ);
  CMU_HFXOInit(&hfxoInit);

#if defined(_CMU_HFXOCTRL_AUTOSTARTEM0EM1_MASK)
  if (SL_DEVICE_INIT_HFXO_AUTOSTART) {
    CMU_HFXOAutostartEnable(0, true, SL_DEVICE_INIT_HFXO_AUTOSELECT);
  }
#endif

  return SL_STATUS_OK;
}
