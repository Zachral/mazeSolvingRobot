#include <util/delay.h>
#include <stdio.h>
#include "drive.h"
#include "servo.h"

void drive_forward(){
    printf("forward\n");
    left_servo_set_percentage(10);
    right_servo_set_percentage(-10); 
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
    left_servo_set_percentage(-10);
    right_servo_set_percentage(-10);
    //delay sets the degree of turn
    _delay_ms(2000);
    stop();
    _delay_ms(500);
    return;
}

void turn_right(){
    printf("turning right\n"); 
    left_servo_set_percentage(10);
    right_servo_set_percentage(10);
    //delay sets the degree of turn
    _delay_ms(2000);
    stop();
    _delay_ms(500);
    return;
}

void u_turn(){
    printf("U-turn\n"); 
    left_servo_set_percentage(10);
    right_servo_set_percentage(10);
    //delay sets the degree of turn
    _delay_ms(4000);
    stop();
    _delay_ms(500);
    return;
}