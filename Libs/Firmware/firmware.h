/*
 * firmware.h
 *
 *  Created on: Oct 28, 2021
 *      Author: janoko
 */

#ifndef FIRMWARE_FIRMWARE_H_
#define FIRMWARE_FIRMWARE_H_

#include "stm32f4xx_hal.h"

#define FIRMWARE_DETAIL_ADDR 0x2001fff0

typedef uint32_t Firmware_Version_t;

typedef struct {
  Firmware_Version_t version;
  uint8_t isUpdate;
} Firmware_Detail_t;

void Firmware_LoadDetail(Firmware_Detail_t *);
void Firmware_SaveDetail(Firmware_Detail_t *);
void Firmware_SetVersion(Firmware_Detail_t *, uint8_t major, uint8_t minor, uint8_t patch);

#endif /* FIRMWARE_FIRMWARE_H_ */
