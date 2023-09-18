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
static volatile int frontDistance = 0, leftDistance =0, rightDistance = 0;
static volatile uint8_t overflowCount = 0;

ISR(TIMER2_OVF_vect){
    overflowCount++;
    if (overflowCount > 100) overflowCount = 0;  
}

ISR(TIMER2_COMPB_vect){
    if (overflowCount > 31){
        printf("INTERUPPT!\n");
        leftDistance = get_distance_Ultrasonic_sensor(Left_Ultrasonic_Echo_pin); 
        rightDistance = get_distance_Ultrasonic_sensor(Right_Ultrasonic_Echo_pin);
        frontDistance = get_distance_Ultrasonic_sensor(Front_Ultrasonic_Echo_pin); 

        //checks if there is an opening in the maze wall
        if((leftDistance > 15) || (rightDistance > 15)){
            printf("space to the sides!\n");
        }
        //checks if there is a wall in front of the robot
        if(frontDistance < 9){
            printf("Wall infront\n");
        }
        //Checks if the robot gets to close to the side walls
        if((leftDistance < 4) || (rightDistance < 4)){
            printf("TO CLOSE!\n");
        }
    }
}

int main(void){
    _delay_ms(1000);
    init_Ultrasonic_sensor();
    init_servo();
    button_init(); 
    init_serial();
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
