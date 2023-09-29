#include <util/delay.h>
#include <stdio.h>
#include "drive.h"
#include "servo.h"

void drive_forward(){
    printf("forward\n");
    left_servo_set_percentage(40);
    right_servo_set_percentage(-30); 
    return; 
}

void drive_slowly_forward(){
    printf("slow forward"); 
    stop();
    left_servo_set_percentage(27);
    right_servo_set_percentage(-20); 
    _delay_ms(250); 
    return; 
}

void back_up(){
    printf("backwards");
    stop(); 
    left_servo_set_percentage(-27);
    right_servo_set_percentage(20); 
    _delay_ms(600); 
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
    _delay_ms(750);
    return;
}

void turn_right(){
    printf("turning right\n"); 
    stop();
    left_servo_set_percentage(40);
    right_servo_set_percentage(40);
    //delay sets the degree of turn
    _delay_ms(750);
    return;
}

void u_turn(int leftDistance, int rightDistance){
    printf("U-turn\n"); 
    stop();
    if(leftDistance > rightDistance){
        left_servo_set_percentage(-45);
        right_servo_set_percentage(-45);
    }else{ 
        left_servo_set_percentage(35);
        right_servo_set_percentage(35);  
    }
    //delay sets the degree of turn
    _delay_ms(1400);
    return;
}

void stabilize(uint8_t side){
    printf("stabilize\n");
    switch (side){
    case LEFT:
        left_servo_set_percentage(50);
        right_servo_set_percentage(-25);
        _delay_ms(250);
        break;
    case RIGHT:
        left_servo_set_percentage(25);
        right_servo_set_percentage(-45);
        _delay_ms(250);
    default:
        drive_forward();
        break;
    }
}