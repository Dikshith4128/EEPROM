/*

  eeprom.h

  Based on AVR101 "High endurance EEPROM storage" by jllassen

  Copyright 2015 Matthew T. Pandina. All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions
  are met:

  1. Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY MATTHEW T. PANDINA "AS IS" AND ANY
  EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL MATTHEW T. PANDINA OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
  USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
  OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
  SUCH DAMAGE.

*/

#ifndef __EEPROM_WL_VOL_H__
#define __EEPROM_WL_VOL_H__


#include <stdint.h>
#include "eeprom_wl_vol_cfg.h"

#ifndef EEPROM_SIMULATD_SIZE
#define EEPROM_SIMULATED_SIZE  (HAL_LIB_CFG_EEPROM_SIMULATED_SIZE)
#else
#define EEPROM_SIMULATED_SIZE  (1024)
#endif


typedef enum eeprom_wl_volume_e {eeprom_wl_volume0, eeprom_wl_volume1, eeprom_wl_volume2, eeprom_wl_volume3} eeprom_wl_volume_t;

//Volume 0 config
#ifdef HAL_LIB_CFG_EEPROM_WL_VOLUME0
	#define EEPROM_WL_VOLUME0			(HAL_LIB_CFG_EEPROM_WL_VOLUME0)
	#define EEPROM_WL_VOLUME0_SIZE		(HAL_LIB_CFG_EEPROM_WL_VOLUME0_SIZE)
	#define EEPROM_WL_VOLUME0_WL_FACTOR (HAL_LIB_CFG_EEPROM_WL_VOLUME0_WL_FACTOR)
#else
	#define EEPROM_WL_VOLUME0			(0U)
	#define EEPROM_WL_VOLUME0_SIZE		(256U)
	#define EEPROM_WL_VOLUME0_WL_FACTOR (1U)
#endif
#define EEPROM_WL_VOLUME0_END			  (EEPROM_WL_VOLUME0+(EEPROM_WL_VOLUME0_SIZE - 1))
#define EE_WL_VOLUME0_PARAM_BUFFER_SIZE   (EEPROM_WL_VOLUME0_WL_FACTOR)
#define EE_WL_VOLUME0_STATUS_BUFFER_SIZE  (EE_WL_VOLUME0_PARAM_BUFFER_SIZE)

//Volume 1 config
#ifdef HAL_LIB_CFG_EEPROM_WL_VOLUME1
	#define EEPROM_WL_VOLUME1			(HAL_LIB_CFG_EEPROM_WL_VOLUME1)
	#define EEPROM_WL_VOLUME1_SIZE		(HAL_LIB_CFG_EEPROM_WL_VOLUME1_SIZE)
	#define EEPROM_WL_VOLUME1_WL_FACTOR (HAL_LIB_CFG_EEPROM_WL_VOLUME1_WL_FACTOR)
#else
	#define EEPROM_WL_VOLUME1			(256U)
	#define EEPROM_WL_VOLUME1_SIZE		(256U)
	#define EEPROM_WL_VOLUME1_WL_FACTOR (2U)
#endif
#define EEPROM_WL_VOLUM1_END			 (EEPROM_WL_VOLUME1+(EEPROM_WL_VOLUME1_SIZE - 1))
#define EE_WL_VOLUME1_PARAM_BUFFER_SIZE  (EEPROM_WL_VOLUME1_WL_FACTOR)
#define EE_WL_VOLUME1_STATUS_BUFFER_SIZE (EE_WL_VOLUME1_PARAM_BUFFER_SIZE)

//Volume 2 config
#ifdef HAL_LIB_CFG_EEPROM_WL_VOLUME2
	#define EEPROM_WL_VOLUME2			(HAL_LIB_CFG_EEPROM_WL_VOLUME2)
	#define EEPROM_WL_VOLUME2_SIZE		(HAL_LIB_CFG_EEPROM_WL_VOLUME2_SIZE)
	#define EEPROM_WL_VOLUME2_WL_FACTOR (HAL_LIB_CFG_EEPROM_WL_VOLUME2_WL_FACTOR)
#else
	#define EEPROM_WL_VOLUME2			(512U)
	#define EEPROM_WL_VOLUME2_SIZE		(256U)
	#define EEPROM_WL_VOLUME2_WL_FACTOR (4U)
#endif
#define EEPROM_WL_VOLUM2_END			 (EEPROM_WL_VOLUME2+(EEPROM_WL_VOLUME2_SIZE - 1))
#define EE_WL_VOLUME2_PARAM_BUFFER_SIZE  (EEPROM_WL_VOLUME2_WL_FACTOR)
#define EE_WL_VOLUME2_STATUS_BUFFER_SIZE (EE_WL_VOLUME2_PARAM_BUFFER_SIZE)

//Volume 3 config
#ifdef HAL_LIB_CFG_EEPROM_WL_VOLUME3
	#define EEPROM_WL_VOLUME3			(HAL_LIB_CFG_EEPROM_WL_VOLUME3)
	#define EEPROM_WL_VOLUME3_SIZE		(HAL_LIB_CFG_EEPROM_WL_VOLUME3_SIZE)
	#define EEPROM_WL_VOLUME3_WL_FACTOR (HAL_LIB_CFG_EEPROM_WL_VOLUME3_WL_FACTOR)
#else
	#define EEPROM_WL_VOLUME3			(768U)
	#define EEPROM_WL_VOLUME3_SIZE		(256U)
	#define EEPROM_WL_VOLUME3_WL_FACTOR (8U)
#endif
#define EEPROM_WL_VOLUM3_END			 (EEPROM_WL_VOLUME2+(EEPROM_WL_VOLUME3_SIZE - 1))
#define EE_WL_VOLUME3_PARAM_BUFFER_SIZE  (EEPROM_WL_VOLUME3_WL_FACTOR)
#define EE_WL_VOLUME3_STATUS_BUFFER_SIZE (EE_WL_VOLUME3_PARAM_BUFFER_SIZE)



/*
 * This library is intended to be compiled for an AVR microcontroller,
 * but for debugging purposes, it may also be compiled on a computer,
 * in which case the EEPROM will be simulated using an array, and a
 * function called EEPROM_Print will become available, which prints
 * the contents of the simulated EEPROM to stdout.
 *
 * In order to differentiate between the two platforms, it is assumed
 * that F_CPU is only defined when being compiled on an AVR.
 *
 * You probably want to program the FUSES on your AVR to preserve the
 * contents of the EEPROM (so the EEPROM doesn't get wiped clean each
 * time you flash a new program), and enable BOD (Brown Out Detection)
 * to avoid EEPROM corruption if the supply voltage falls too low.
 */
#ifdef F_CPU
#include <avr/io.h>
/*
 * If EE_EEPROM_END is defined before including this header file, then
 * a compile-time assert will be used to ensure that all wear-leveled
 * parameters and associated metadata fit into the available EEPROM.
 *
 * EE_EEPROM_END should be defined to point to the first address after
 * the last used parameter.
 */
#ifdef EE_EEPROM_END
_Static_assert((EE_EEPROM_END <= E2END + 1), "Available EEPROM memory exceeded. Consider setting EEPROM_WEAR_LEVEL_FACTOR to a lower value.");
#endif // EE_EEPROM_END
#else // F_CPU
// Only used for simulation when compiled on a computer
extern uint8_t eeprom[EEPROM_SIMULATED_SIZE];
#ifdef EE_EEPROM_END
_Static_assert((EE_EEPROM_END <= sizeof(eeprom)), "Available EEPROM memory exceeded. Consider setting EEPROM_WEAR_LEVEL_FACTOR to a lower value.");
#endif // EE_EEPROM_END
/*
 * EEPROM_Print
 *
 * Prints the contents of the simulated EEPROM, between two locations,
 * to stdout.
 *
 * begin [in]
 *   The first location of the simulated EEPROM to be printed.
 *
 * end [in]
 *   The location one after the last location of the simulated EEPROM
 *   to be printed.
 */
void EEPROM_Print(eeprom_wl_volume_t volume, const uint16_t begin, const uint16_t end);
#endif // F_CPU

/*
 * EEPROM_InitWearLeveledByte
 *
 * Initializes a segment of EEPROM to use for wear-leveled storage of
 * a byte of memory, and writes the initial value to EEPROM. The total
 * length of this segment, including metadata, occupies
 * (EEPROM_WEAR_LEVEL_FACTOR * 2) bytes of EEPROM.
 * 
 * param [in]
 *   The offset into EEPROM where the wear-leveled segment begins.
 *
 * data [in]
 *   A byte containing the initial data to store in EEPROM.
 *
 * Returns:
 *   A copy of data, for convenience.
 * 
 * This function only needs to be invoked once per offset in order to
 * initialize the metadata necessary for wear-leveling, after which
 * the function EEPROM_ReadWearLeveledByte may be used to read the
 * byte from EEPROM into memory, and EEPROM_WriteWearLeveledByte to
 * write a new byte from memory into EEPROM.
 */
uint8_t EEPROM_InitWearLeveledByte(eeprom_wl_volume_t volume, const uint16_t param, const uint8_t data);

/*
 * EEPROM_ReadWearLeveledByte
 *
 * Reads, and returns the byte of data currently stored in a
 * wear-leveled segment of EEPROM.
 * 
 * param [in]
 *   The offset into EEPROM where the wear-leveled segment begins.
 *
 * Returns:
 *   The byte of data stored in that segment of EEPROM.
 * 
 * This function may only be invoked if EEPROM_InitWearLeveledByte has
 * previously been invoked on the same segment of EEPROM.
 */
uint8_t EEPROM_ReadWearLeveledByte(eeprom_wl_volume_t volume, const uint16_t param);

/*
 * EEPROM_WriteWearLeveledByte
 *
 * Writes a byte of data into a wear-leveled segment of EEPROM.
 * 
 * param [in]
 *   The offset into EEPROM where the wear-leveled segment begins.
 *
 * data [in]
 *   The byte of data to store in EEPROM.
 *
 * This function may only be invoked if EEPROM_InitWearLeveledByte
 * has previously been invoked on the same segment of EEPROM.
 */
void EEPROM_WriteWearLeveledByte(eeprom_wl_volume_t volume, const uint16_t param, const uint8_t data);

/*
 * EEPROM_InitWearLeveledBlock
 *
 * Initializes a segment of EEPROM to use for wear-leveled storage of
 * a block of memory, and writes the contents of the buffer to
 * EEPROM. The total length of this segment, including metadata,
 * occupies (len * EEPROM_WEAR_LEVEL_FACTOR * 2) bytes of EEPROM.
 * 
 * param [in]
 *   The offset into EEPROM where the wear-leveled segment begins.
 *
 * data [in]
 *   A pointer to the buffer containing the initial data to store in
 *   EEPROM.
 *
 * len [in]
 *   The size of the buffer, in bytes.
 *
 * This function only needs to be invoked once per offset in order to
 * initialize the metadata necessary for wear-leveling, after which
 * the function EEPROM_ReadWearLeveledBlock may be used to read the
 * block from EEPROM into memory, and EEPROM_WriteWearLeveledBlock to
 * write a new block from memory into EEPROM.
 */
void EEPROM_InitWearLeveledBlock(eeprom_wl_volume_t volume, const uint16_t param, const void *data, const uint16_t len);

/*
 * EEPROM_ReadWearLeveledBlock
 *
 * Reads, and copies the block of data currently stored in a
 * wear-leveled segment of EEPROM into the supplied buffer.
 * 
 * param [in]
 *   The offset into EEPROM where the wear-leveled segment begins.
 *
 * data [out]
 *   A pointer to a buffer large enough to contain the block of data
 *   stored in EEPROM.
 *
 * len [in]
 *   The size of the buffer, in bytes.
 *
 * This function may only be invoked if EEPROM_InitWearLeveledBlock
 * has previously been invoked on the same segment of EEPROM.
 */
void EEPROM_ReadWearLeveledBlock(eeprom_wl_volume_t volume, const uint16_t param, void *data, const uint16_t len);

/*
 * EEPROM_WriteWearLeveledBlock
 *
 * Writes the contents of the supplied buffer into a wear-leveled
 * segment of EEPROM.
 * 
 * param [in]
 *   The offset into EEPROM where the wear-leveled segment begins.
 *
 * data [in]
 *   A pointer to the buffer containing the data to store in EEPROM.
 *
 * len [in]
 *   The size of the buffer, in bytes.
 *
 * This function may only be invoked if EEPROM_InitWearLeveledBlock
 * has previously been invoked on the same segment of EEPROM.
 */
void EEPROM_WriteWearLeveledBlock(eeprom_wl_volume_t volume, const uint16_t param, const void *data, const uint16_t len);
#endif // __EEPROM_WL_VOL_H__
