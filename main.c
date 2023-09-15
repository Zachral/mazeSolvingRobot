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

void setup(){
    _delay_ms(1000);
    init_servo();
    button_init(); 
    init_serial();
    init_Ultrasonic_sensor();
    sei();
    return; 
}

int main(void){
    setup();
    static volatile bool buttonWasPressed = false; 
    int frontDistance = 0, leftDistance = 0, rightDistance = 0; 

    while(!buttonWasPressed){
         buttonClick(&buttonWasPressed);
    }
    
    while(1){
        drive_forward();
        frontDistance = get_distance_Ultrasonic_sensor(Left_Ultrasonic_Echo_pin);
        if(convert_ultrasonic_input_to_centimeters(frontDistance) < 9){
            stop();
            _delay_ms(1000); 
        }

    }
    return 0;
}
