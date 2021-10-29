/*
 * firmware.c
 *
 *  Created on: Oct 28, 2021
 *      Author: janoko
 */

#include "firmware.h"

Firmware_Detail_t Firmware_GetDetail()
{
  Firmware_Detail_t detail = {0};
  detail = *((Firmware_Detail_t*) FIRMWARE_DETAIL_ADDR);
  return detail;
}

void Firmware_SaveDetail(Firmware_Detail_t* detail)
{
  Firmware_Detail_t *detailPtr = (Firmware_Detail_t*) FIRMWARE_DETAIL_ADDR;
  *detailPtr = *detail;
}

void Firmware_SetVersion(Firmware_Detail_t *detail, uint8_t major, uint8_t minor, uint8_t patch)
{
  uint8_t tmpVersion[4] = {0, patch, minor, major};
  detail->version = *((uint32_t*) tmpVersion);
}
