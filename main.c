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
    int frontDistance = 0; 


    // while(!buttonWasPressed){
    //      buttonClick(&buttonWasPressed);
    // }
    
    while(1){
        frontDistance = get_distance_Ultrasonic_sensor(Front_Ultrasonic_Echo_pin); 
        convert_ultrasonic_input_to_centimeters(frontDistance);
        printf("new mesure\n");
        _delay_ms(100); 
        
    }
    return 0;
}
