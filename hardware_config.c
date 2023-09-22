#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"
#include "servo.h"
#include "button.h"
#include "ultrasonic_sensor.h"
#include "millis.h"

void hardware_setup(){
    _delay_ms(1000);
    init_servo();
    button_init(); 
    init_serial();
    init_Ultrasonic_sensor();
    color_sensor_init();
    millis_init();
    sei();
    return; 
}