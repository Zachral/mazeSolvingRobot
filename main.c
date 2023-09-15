#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "servo.h"
#include "button.h"



int main(void){
    sei();
    init_servo();
    button_init(); 
    init_serial();
    static volatile bool buttonWasPressed = false; 
    
    while(!buttonWasPressed){
         buttonClick(&buttonWasPressed);
    }
    
    while(1){
        // while(buttonWasPressed) {
            left_servo_set_percentage(8);
            right_servo_set_percentage(-10); 
        // }
    }
    return 0;
}
