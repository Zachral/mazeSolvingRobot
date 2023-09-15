#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "servo.h"
#include "button.h"
#include "drive.h"
#include "ultrasonic_sensor.h"

int main(void){
    sei();
    init_servo();
    button_init(); 
    init_serial();
    init_Ultrasonic_sensor();
    static volatile bool buttonWasPressed = false; 
    volatile uint8_t frontDistance = 0; 

    while(!buttonWasPressed){
         buttonClick(&buttonWasPressed);
    }
    
    while(1){
        drive_forward(); 
        frontDistance = get_distance_Ultrasonic_sensor(Front_Ultrasonic_Echo_pin); 
        if(convert_ultrasonic_input_to_centimeters(frontDistance) < 10){
            stop();
            _delay_ms(200);
            turn_left();
        }
    }
    return 0;
}
