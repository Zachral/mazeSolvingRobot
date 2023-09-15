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

    while(!buttonWasPressed){
         buttonClick(&buttonWasPressed);
    }
    
    while(1){
        drive_forward(); 
        _delay_ms(5000);
        stop();
        _delay_ms(1000);
        turn_left(); 
        drive_forward(); 
    }
    return 0;
}
