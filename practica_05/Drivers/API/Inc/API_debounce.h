/*
 * API_delay.h
 *
 *  Created on: Mar 20, 2025
 *      Author: doddy
 */


#ifndef API_DEBOUNCE_H
#define API_DEBOUNCE_H

#include "stm32f4xx_hal.h"
#include "API_delay.h"
#include <API_uart.h>

void debounceFSM_init(void);
void debounceFSM_update(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void toggle_led(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
bool_t readKey(void);

#endif
