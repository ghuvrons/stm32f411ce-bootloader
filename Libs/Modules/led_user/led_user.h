/*
 * led_user.h
 *
 *  Created on: Oct 26, 2021
 *      Author: janoko
 */

#ifndef MODULES_LED_USER_LED_USER_H_
#define MODULES_LED_USER_LED_USER_H_

#include "stm32f4xx_hal.h"

void bepBlink(uint8_t n, uint16_t t_on, uint16_t t_off);

#endif /* MODULES_LED_USER_LED_USER_H_ */
