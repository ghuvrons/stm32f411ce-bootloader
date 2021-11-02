/*
 * Flash.h
 *
 *  Created on: Nov 1, 2021
 *      Author: janoko
 */

#ifndef FOTU_FLASH_H_
#define FOTU_FLASH_H_

#include "stm32f4xx_hal.h"

uint32_t Flash_Read(void);
uint32_t Flash_Write(uint32_t address, uint32_t *data, uint16_t numberofwords);
uint32_t Flash_Erase(uint32_t startSectorAddress, uint16_t numberofwords);


#endif /* FOTU_FLASH_H_ */
