#include <avr/io.h>
#include "common_defines.h"
#include "led.h"

void led_init(){
    BIT_SET(LED_PORT_DIRECTION, LED_PIN);
    return; 
}

void light_led(){
    BIT_SET(LED_PORT, LED_PIN);
    return;
}
