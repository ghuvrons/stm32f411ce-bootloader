/*
 * utils.c
 *
 *  Created on: Oct 26, 2021
 *      Author: janoko
 */

#include "utils.h"
#include "stm32f4xx_hal.h"

#ifdef USE_FREERTOS
#include "cmsis_os.h"
#endif

void sleep(uint32_t timeout)
{
#ifdef USE_FREERTOS
  osDelay(timeout);
#endif
#ifndef USE_FREERTOS
  HAL_Delay(timeout);
#endif
}
