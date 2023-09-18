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
    int frontDistance = 0, leftDistance = 0, rightDistance = 0; 


    while(!buttonWasPressed){
         buttonClick(&buttonWasPressed);
    }
    
    while(1){
        drive_forward();
        frontDistance = get_distance_Ultrasonic_sensor(Front_Ultrasonic_Echo_pin); 
        leftDistance = get_distance_Ultrasonic_sensor(Left_Ultrasonic_Echo_pin);
        rightDistance = get_distance_Ultrasonic_sensor(Right_Ultrasonic_Echo_pin);
        if(convert_ultrasonic_input_to_centimeters(frontDistance) < 9) {
           printf("color check!\n");      
        }
        if(convert_ultrasonic_input_to_centimeters(leftDistance) > 15 || convert_ultrasonic_input_to_centimeters(rightDistance) > 15){
            printf("space to the sides!\n"); 
        }
        if(convert_ultrasonic_input_to_centimeters(leftDistance) < 4 || convert_ultrasonic_input_to_centimeters(rightDistance) < 4){
            printf("TO CLOSE!\n");
        }
    }
    return 0;
}
