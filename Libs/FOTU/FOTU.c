/*
 * FOTU.c
 *
 *  Created on: Nov 1, 2021
 *      Author: janoko
 */

#include "FOTU.h"
#include "Flash.h"


void FOTU_PrepareWrite(FOTU_Handler_t *fh, uint32_t length, uint32_t crc)
{
  fh->expectLength = length;
  fh->expectCRC = crc;
  fh->state = FOTU_STATE_WRITING;
  fh->writeIdx = fh->app1.appAddress;

  // Erase APP
  Flash_Erase(fh->app1.appAddress, (uint16_t) fh->app1.appLength/4);

  if(fh->onReadyToWrite != NULL)
    fh->onReadyToWrite();
}

void FOTU_Write(FOTU_Handler_t *fh, uint8_t *data, uint32_t length)
{
  // update CRC
  for(uint32_t i = 0; i < length; i++){
    FOTU_Crc(&(fh->crc), data[i]);
  }

  // Write to address
  Flash_Write(fh->writeIdx, (uint32_t *)data, length/4);
  fh->writeIdx += length;
  fh->expectLength -= length;

  // on finished
  if(fh->expectLength == 0){
    fh->state = FOTU_STATE_AVAILABLE;

    if(fh->onWritingDone != NULL)
      fh->onWritingDone();
  }
}

void FOTU_Crc(uint32_t *lastCRC, uint8_t newbyte)
{
  uint8_t tmp;

  tmp = (*lastCRC) >> 24;
  *lastCRC = (*lastCRC) << 8;
  *lastCRC = (*lastCRC) | tmp;
  *lastCRC = (*lastCRC) ^ newbyte;
}
