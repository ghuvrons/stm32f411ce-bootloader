/*
 * FOTU.h
 *
 *  Created on: Nov 1, 2021
 *      Author: janoko
 */

#ifndef FOTU_FOTU_H_
#define FOTU_FOTU_H_

#define FOTU_STATE_AVAILABLE 0
#define FOTU_STATE_WRITING 1

#include "stm32f4xx_hal.h"

typedef struct {
  uint32_t appAddress;
  uint32_t appLength;
} FOTU_App_t;

typedef struct {
  uint8_t state;

  uint32_t length;
  uint32_t crc;
  uint32_t expectLength;
  uint32_t expectCRC;
  uint32_t writeIdx;

  FOTU_App_t app1;

  // Events
  void (*onReadyToWrite)(void);
  void (*onWritingDone)(void);
} FOTU_Handler_t;

void FOTU_PrepareWrite(FOTU_Handler_t*, uint32_t length, uint32_t crc);
void FOTU_Write(FOTU_Handler_t*, uint8_t *data, uint32_t length);
void FOTU_Crc(uint32_t *lastCRC, uint8_t newbyte);

#endif /* FOTU_FOTU_H_ */
