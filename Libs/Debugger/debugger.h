/*
 * debugger.h
 *
 *  Created on: Sep 1, 2021
 *      Author: janoko
 */

#ifndef INC_DEBUGGER_H_
#define INC_DEBUGGER_H_

#include "stm32f4xx_hal.h"

#define DBG_TYPE_DISABLE 0x00
#define DBG_TYPE_BY_USB 0x01
#define DBG_LOG_SZ      512

uint8_t DBG_LogBuffer[DBG_LOG_SZ];
uint16_t DBG_LogBufferIdx;
uint8_t DBG_flag;

typedef uint8_t DBG_Type;

typedef struct DBG_Config {
  void *conn;
  DBG_Type type;
} DBG_Config;

DBG_Config DBG_GetConfig(void);
void DBG_Init(DBG_Config config);
int DBG_Print(const char *str, ...);
void DBG_PrintLn(void);
void DBG_PrintB(const uint8_t *bytes, uint16_t length);
void DBG_PrintS(const char *bytes, uint16_t length);
void DBG_Log(const uint8_t *bytes, uint16_t length);
void DBG_LogStr(const char*);

#endif /* INC_DEBUGGER_H_ */
