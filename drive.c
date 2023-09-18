#include <util/delay.h>
#include <stdio.h>
#include "drive.h"
#include "servo.h"

void drive_forward(){
    printf("forward\n");
    left_servo_set_percentage(25);
    right_servo_set_percentage(-22); 
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
    left_servo_set_percentage(-20);
    right_servo_set_percentage(-20);
    //delay sets the degree of turn
    _delay_ms(1000);
    stop();
    return;
}

void turn_right(){
    printf("turning right\n"); 
    left_servo_set_percentage(20);
    right_servo_set_percentage(20);
    //delay sets the degree of turn
    _delay_ms(1000);
    stop();
    return;
}

void u_turn(){
    printf("U-turn\n"); 
    left_servo_set_percentage(20);
    right_servo_set_percentage(20);
    //delay sets the degree of turn
    _delay_ms(2000);
    stop();
    return;
}