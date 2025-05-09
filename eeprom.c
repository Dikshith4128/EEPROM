/*

  eeprom.c
  modify for multiple volumes

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

#include "eeprom.h"

#ifdef F_CPU
#include <avr/eeprom.h>
#define EEPROM_Read(address) eeprom_read_byte((uint8_t *)(uint16_t)(address))
#define EEPROM_Write(address, data) eeprom_update_byte((uint8_t *)(uint16_t)(address), (data))
#else // F_CPU
// Only used for simulation when compiled on a computer
uint8_t eeprom[EEPROM_SIMULATED_SIZE] = { [0 ... EEPROM_SIMULATED_SIZE - 1] = 0xFF };
#define EEPROM_Read(address) eeprom[(address)]
#define EEPROM_Write(address, data) eeprom[(address)] = (data)
#include <stdio.h>

void EEPROM_Print(eeprom_wl_volume_t volume, const uint16_t begin, const uint16_t end) {
	switch(volume){
		case eeprom_wl_volume0:
			printf("-----------------------------------------------\n");
			for (uint16_t i = begin; i < end; ++i)
				printf("%02X %s", eeprom[i], (i + 1) % (EEPROM_WL_VOLUME0_WL_FACTOR * 1) ? "" : "\n");
			printf("-----------------------------------------------\n");
			break;
		case eeprom_wl_volume1:
			printf("-----------------------------------------------\n");
			for (uint16_t i = begin; i < end; ++i)
				printf("%02X %s", eeprom[i], (i + 1) % (EEPROM_WL_VOLUME1_WL_FACTOR * 2) ? "" : "\n");
			printf("-----------------------------------------------\n");
			break;
		case eeprom_wl_volume2:
			printf("-----------------------------------------------\n");
			for (uint16_t i = begin; i < end; ++i)
				printf("%02X %s", eeprom[i], (i + 1) % (EEPROM_WL_VOLUME2_WL_FACTOR * 2) ? "" : "\n");
			printf("-----------------------------------------------\n");
			break;
		case eeprom_wl_volume3:
			printf("-----------------------------------------------\n");
			for (uint16_t i = begin; i < end; ++i)
				printf("%02X %s", eeprom[i], (i + 1) % (EEPROM_WL_VOLUME3_WL_FACTOR * 2) ? "" : "\n");
			printf("-----------------------------------------------\n");
			break;
		default:
			printf("Unsupoorted Volume\n");
			break;
	}
}


#endif // F_CPU
static volatile uint16_t  param_buffer_size;
static volatile uint16_t  status_buffer_size;

static inline int16_t eeprom_wl_get_p_s(eeprom_wl_volume_t volume)
{
	switch(volume){
		case eeprom_wl_volume0:
			param_buffer_size  = EE_WL_VOLUME0_PARAM_BUFFER_SIZE;
			status_buffer_size = EE_WL_VOLUME0_STATUS_BUFFER_SIZE;
			break;
		case eeprom_wl_volume1:
			param_buffer_size  = EE_WL_VOLUME1_PARAM_BUFFER_SIZE;
			status_buffer_size = EE_WL_VOLUME1_STATUS_BUFFER_SIZE;
			break;
		case eeprom_wl_volume2:
			param_buffer_size  = EE_WL_VOLUME2_PARAM_BUFFER_SIZE;
			status_buffer_size = EE_WL_VOLUME2_STATUS_BUFFER_SIZE;
			break;
		case eeprom_wl_volume3:
			param_buffer_size  = EE_WL_VOLUME3_PARAM_BUFFER_SIZE;
			status_buffer_size = EE_WL_VOLUME3_STATUS_BUFFER_SIZE;
			break;
		default:
			return 1;
	}

	if(status_buffer_size == 1)
		status_buffer_size = 0;

	return 0;
}




static uint16_t EEPROM_FindCurrentAddress(const uint16_t param) {
	uint16_t EeBufPtr = param + param_buffer_size; // point to the status buffer
	uint16_t EeBufEnd = EeBufPtr + status_buffer_size; // the first address outside the buffer

	// Identify the last written element of the status buffer
	uint8_t tmp;
	do {
		tmp = EEPROM_Read(EeBufPtr);
		if (++EeBufPtr == EeBufEnd) // avoid comparing out-of-bounds
		 break;
	} while (EEPROM_Read(EeBufPtr) == (uint8_t)(tmp + 1));

	// Return the last used element of the param buffer
	return EeBufPtr - (param_buffer_size + 1);
}

uint8_t EEPROM_InitWearLeveledByte(eeprom_wl_volume_t volume, const uint16_t param, const uint8_t data) {
	eeprom_wl_get_p_s(volume);
	if(status_buffer_size == 0) {
		EEPROM_Write(param + param_buffer_size, status_buffer_size - 1);
		for (uint8_t i = 1; i < status_buffer_size; ++i)
			EEPROM_Write(i + param + param_buffer_size, i - 1);

		EEPROM_Write(param, data);
	}else{
		EEPROM_Write(param, data);
	}

	return data;
}




uint8_t EEPROM_ReadWearLeveledByte(eeprom_wl_volume_t volume, const uint16_t param) {
	eeprom_wl_get_p_s(volume);
	return EEPROM_Read(EEPROM_FindCurrentAddress(param));
}

void EEPROM_WriteWearLeveledByte(eeprom_wl_volume_t volume, const uint16_t param, const uint8_t data) {
	eeprom_wl_get_p_s(volume);
	uint16_t address = EEPROM_FindCurrentAddress(param);

  // Only perform the write if the new value is different from what's currently stored
  if (EEPROM_Read(address) == data)
    return;

	if(status_buffer_size != 0) {
		// Update the param buffer in the EEPROM
		EEPROM_Write(address, data);
	}else{

		// Store the old status value
		uint8_t oldStatusValue = EEPROM_Read(address + param_buffer_size);

		// Move pointer to the next element in the buffer, wrapping around if necessary
		if (++address == param + param_buffer_size)
			address = param;

		// If self-programming is used in the application, insert code here
		// to wait for any self-programming operations to finish before
		// writing to the EEPROM.

		// Update the param buffer in the EEPROM
		EEPROM_Write(address, data);

		// Update the status buffer in the EEPROM
		EEPROM_Write(address + param_buffer_size, oldStatusValue + 1);
	}
}

static uint8_t __EEPROM_InitWearLeveledByte(const uint16_t param, const uint8_t data) {
	if(status_buffer_size != 0) {
		EEPROM_Write(param + param_buffer_size, status_buffer_size - 1);
		for (uint8_t i = 1; i < status_buffer_size; ++i)
			EEPROM_Write(i + param + param_buffer_size, i - 1);

		EEPROM_Write(param, data);
	}else{
		EEPROM_Write(param, data);
	}

	return data;
}

static uint8_t __EEPROM_ReadWearLeveledByte(const uint16_t param) {
	return EEPROM_Read(EEPROM_FindCurrentAddress(param));
}

static void __EEPROM_WriteWearLeveledByte(const uint16_t param, const uint8_t data) {
	uint16_t address = EEPROM_FindCurrentAddress(param);

	// Only perform the write if the new value is different from what's currently stored
	if (EEPROM_Read(address) == data)
		return;

	if(status_buffer_size == 0) {
		// Update the param buffer in the EEPROM
		EEPROM_Write(address, data);
	}else{

		// Store the old status value
		uint8_t oldStatusValue = EEPROM_Read(address + param_buffer_size);

		// Move pointer to the next element in the buffer, wrapping around if necessary
		if (++address == param + param_buffer_size)
			address = param;

		// If self-programming is used in the application, insert code here
		// to wait for any self-programming operations to finish before
		// writing to the EEPROM.

		// Update the param buffer in the EEPROM
		EEPROM_Write(address, data);

		// Update the status buffer in the EEPROM
		EEPROM_Write(address + param_buffer_size, oldStatusValue + 1);
  }
}

void EEPROM_InitWearLeveledBlock(eeprom_wl_volume_t volume, const uint16_t param, const void *data, const uint16_t len) {
	eeprom_wl_get_p_s(volume);
	for (uint16_t i = 0; i < len; ++i)
		__EEPROM_InitWearLeveledByte(param + i * (param_buffer_size + status_buffer_size),
                               *(((uint8_t *)data) + i));
}
/*
EEPROM_ReadWearLeveledBlock() is typically only called once per
parameter, usually when the device is first powered on, to retrieve
the latest stored value. */
void EEPROM_ReadWearLeveledBlock(eeprom_wl_volume_t volume, const uint16_t param, void *data, const uint16_t len) {
	eeprom_wl_get_p_s(volume);
	for (uint16_t i = 0; i < len; ++i)
		*(((uint8_t *)data) + i) = __EEPROM_ReadWearLeveledByte(param + i * (param_buffer_size
								       + status_buffer_size));
}
/*
EEPROM_WriteWearLeveledBlock() is called to store the value of a
parameter in EEPROM. Internally, it checks to see if each byte being
stored is different than the one currently present in EEPROM, and
writes only occur for bytes that have changed. */
void EEPROM_WriteWearLeveledBlock(eeprom_wl_volume_t volume, const uint16_t param, const void *data, const uint16_t len) {
	eeprom_wl_get_p_s(volume);
	for (uint16_t i = 0; i < len; ++i)
		__EEPROM_WriteWearLeveledByte(param + i * (param_buffer_size + status_buffer_size),
                                *(((uint8_t *)data) + i));
}
