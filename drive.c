#include <util/delay.h>
#include <stdio.h>
#include "drive.h"
#include "servo.h"

void drive_forward(){
    printf("forward\n");
    left_servo_set_percentage(53);
    right_servo_set_percentage(-50); 
    return; 
}

void drive_slowly_forward(){
    printf("slow forward"); 
    stop();
    left_servo_set_percentage(28);
    right_servo_set_percentage(-25); 
    _delay_ms(500); 
    return; 
}

void back_up(){
    printf("backwards");
    stop(); 
    left_servo_set_percentage(-28);
    right_servo_set_percentage(25); 
    _delay_ms(500); 
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
    left_servo_set_percentage(-50);
    right_servo_set_percentage(-50);
    //delay sets the degree of turn
    _delay_ms(650);
    return;
}

void turn_right(){
    printf("turning right\n"); 
    stop();
    left_servo_set_percentage(50);
    right_servo_set_percentage(50);
    //delay sets the degree of turn
    _delay_ms(650);
    return;
}

void u_turn(int leftDistance, int rightDistance){
    printf("U-turn\n"); 
    stop();
    if(leftDistance > rightDistance){
        left_servo_set_percentage(-50);
        right_servo_set_percentage(-50);
    }else{ 
        left_servo_set_percentage(50);
        right_servo_set_percentage(50);  
    }
    //delay sets the degree of turn
    _delay_ms(1350);
    return;
}

void stabilize(uint8_t side){
    switch (side){
    case LEFT:
        left_servo_set_percentage(53);
        right_servo_set_percentage(-70);
        _delay_ms(500);
        break;
    case RIGHT:
        left_servo_set_percentage(73);
        right_servo_set_percentage(-50);
        _delay_ms(500);
    default:
        drive_forward();
        break;
    }
}