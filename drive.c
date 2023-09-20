#include <util/delay.h>
#include <stdio.h>
#include "drive.h"
#include "servo.h"

void drive_forward(){
    printf("forward\n");
    left_servo_set_percentage(45);
    right_servo_set_percentage(-40); 
    return; 
}

void stop(){
    printf("Stop\n");
    left_servo_set_percentage(0);
    right_servo_set_percentage(0);
    return;
}

void turn_left(){
    printf("turning left\n"); 
    stop();
    left_servo_set_percentage(-40);
    right_servo_set_percentage(-40);
    //delay sets the degree of turn
    _delay_ms(550);
    stop();
    return;
}

void turn_right(){
    printf("turning right\n"); 
    left_servo_set_percentage(40);
    right_servo_set_percentage(40);
    //delay sets the degree of turn
    _delay_ms(560);
    stop();
    return;
}

void u_turn(int leftDistance, int rightDistance){
    printf("U-turn\n"); 
    if(leftDistance > rightDistance){
        left_servo_set_percentage(-40);
        right_servo_set_percentage(-40);
    }else{ 
        left_servo_set_percentage(40);
        right_servo_set_percentage(40);  
    }
    //delay sets the degree of turn
    _delay_ms(1400);
    stop();
    return;
}