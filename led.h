#ifndef _LED_H__
#define _LED_H__

#include "common_defines.h"

#define LED_PORT_INDEX      B
#define LED_PORT_DIRECTION  DDR_(LED_PORT_INDEX)
#define LED_PORT            PORT_(LED_PORT_INDEX)
#define LED_PIN             0

void led_init();
void light_led();

#endif