/*
 * led_user.c
 *
 *  Created on: Oct 26, 2021
 *      Author: janoko
 */

#include "led_user.h"
#include "stm32f4xx_hal.h"
#include "utils.h"

void bepBlink(uint8_t n, uint16_t t_on , uint16_t t_off)
{
  uint8_t i;

  for(i = 0; i < n; i++){
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    sleep(t_on);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);
    sleep(t_off);
  }
}
