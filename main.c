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
    _delay_ms(1000);
    init_servo();
    button_init(); 
    init_serial();
    init_Ultrasonic_sensor();
    sei();
    static volatile bool buttonWasPressed = false; 



    while(!buttonWasPressed){
         buttonClick(&buttonWasPressed);
    }
    
    while(1){
        drive_forward();
       
    }
    return 0;
}
