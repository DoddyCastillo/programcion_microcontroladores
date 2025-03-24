/*
 * API_delay.h
 *
 *  Created on: Mar 20, 2025
 *      Author: doddy
 */


#include "stm32f4xx_hal.h"
#include<stdlib.h>
#include <stdbool.h>

#define PATTERN_STEPS 4
#define REPETITIONS_PER_STEP 5
#define LED_TOGGLE_DELAY_MS 100

typedef uint32_t tick_t;

typedef bool bool_t;

typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );
bool_t delayIsRunning(delay_t * delay);




