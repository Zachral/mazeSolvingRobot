#ifndef _LED_H__
#define _LED_H__

#include "common_defines.h"
#include "millis.h"
#include <avr/io.h>

#define LED_PORT_INDEX      B
#define LED_PORT_DIRECTION  DDR_(LED_PORT_INDEX)
#define LED_PORT            PORT_(LED_PORT_INDEX)
#define LED_PIN             PINB0

void led_init();
void light_led();
void turn_of_led(void);
void flash_led(volatile millis_t *timeSinceFlash, unsigned int flashSpeedInMilliSeconds);

#endif