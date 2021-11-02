/*
 * debugger.c
 *
 *  Created on: Sep 1, 2021
 *      Author: janoko
 */

#include "debugger.h"
#include <stdio.h>

static DBG_Config myConfig;

void DBG_Init(DBG_Config config)
{
  myConfig = config;
}

int DBG_Print(const char *str, ...)
{
  printf(str);
  printf("\r\n");
  return 1;
}

void DBG_PrintB(const uint8_t *bytes, uint16_t size)
{
  for(uint16_t i = 0; i < size; i++){
    printf("%.2X ", (*bytes));
    bytes++;
  }
  printf("\r\n");
}

void DBG_PrintS(const char *str, uint16_t size)
{
  uint16_t i = 0;
  char tmp[256];
  if(size > 255) size = 255;
  for(i = 0; i < size; i++){
    tmp[i] = (*str);
    str++;
  }
  tmp[i] = 0;
  printf("%s\r\n", tmp);
}


void DBG_Log(const uint8_t *bytes, uint16_t length)
{
  char spltter[] = " || ";
  uint16_t i = 0;

  for(i = 0; i < length; i++){
    DBG_LogBuffer[DBG_LogBufferIdx] = (*bytes);
    bytes++;
    DBG_LogBufferIdx++;
    if(DBG_LogBufferIdx >= DBG_LOG_SZ) DBG_LogBufferIdx = 0;
  }

  for(i = 0; i < 4; i++){
    DBG_LogBuffer[DBG_LogBufferIdx] = spltter[i];
    DBG_LogBufferIdx++;
    if(DBG_LogBufferIdx >= DBG_LOG_SZ) DBG_LogBufferIdx = 0;
  }
}

void DBG_LogStr(const char *str)
{
  char spltter[] = " || ";
  uint16_t i = 0;

  while(*str != 0){
    DBG_LogBuffer[DBG_LogBufferIdx] = (*str);
    str++;
    DBG_LogBufferIdx++;
    if(DBG_LogBufferIdx >= DBG_LOG_SZ) DBG_LogBufferIdx = 0;
  }

  for(i = 0; i < 4; i++){
    DBG_LogBuffer[DBG_LogBufferIdx] = spltter[i];
    DBG_LogBufferIdx++;
    if(DBG_LogBufferIdx >= DBG_LOG_SZ) DBG_LogBufferIdx = 0;
  }
}
