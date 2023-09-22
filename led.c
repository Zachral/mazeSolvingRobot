#include <avr/io.h>
#include <math.h>
#include "common_defines.h"
#include "led.h"
#include "millis.h"

void led_init(){
    BIT_SET(LED_PORT_DIRECTION, LED_PIN);
    BIT_CLEAR(LED_PORT, LED_PIN);
    return; 
}

void light_led(){
    BIT_SET(LED_PORT, LED_PIN);
    return;
}

void turn_of_led(){
    BIT_CLEAR(LED_PORT, LED_PIN);
    return;
}

void flash_led(volatile millis_t *timeSinceFlash, unsigned int flashSpeedInMilliSeconds){
    if (millis_get() - *timeSinceFlash > flashSpeedInMilliSeconds){
        BIT_FLIP(LED_PORT,LED_PIN);
        *timeSinceFlash = millis_get(); 
    }
    return; 
}


