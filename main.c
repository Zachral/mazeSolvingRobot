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
#include "run_path.h"
#include "millis.h"
#include "color_sensor.h"
#include "hardware_config.h"
#include "led.h"

int main(void){
    hardware_setup(); 
    actions_taken_by_robot_t actionsTakenByRobot; 
    static volatile bool isButtonPressed = false; 
    //Setting starting distance value to not trigger turning at start, convert_ultrasonic_input_to_centimeters devides this number by 10
    int frontDistance = 90, leftDistance = 50, rightDistance = 50;
    volatile millis_t milliSecondSinceLastReading = 0;
    volatile millis_t timeSinceFlash = 0; 

    while(!isButtonPressed){
        flash_led(&timeSinceFlash, 500);
        buttonClick(&isButtonPressed);
    }
    turn_of_led();
    while(1){
        drive_forward();
        read_ultrasonic_sensor(&frontDistance, &leftDistance, &rightDistance);
        //milliSecondSinceLastReading = millis_get(); 
        
        if(convert_ultrasonic_input_to_centimeters(leftDistance) < 4){
            stabilize(LEFT);
        }
        if(convert_ultrasonic_input_to_centimeters(rightDistance) < 4){
            stabilize(RIGHT);
        }
        if(convert_ultrasonic_input_to_centimeters(frontDistance) < 9){
            drive_slowly_forward();
            if(detect_red_color()){
                light_led();
                break; 
            }else{
                add_action_to_current_path(U_TURN, actionsTakenByRobot);
                actionsTakenByRobot.numberOfActions++;
                back_up(); 
                u_turn(leftDistance, rightDistance); 
                
                reset_sensors(&frontDistance, &leftDistance,&rightDistance);
                //milliSecondSinceLastReading = millis_get(); 
            }
        }
        if(millis_get() - milliSecondSinceLastReading > 550){
            if((convert_ultrasonic_input_to_centimeters(leftDistance) > 20) 
                    || (convert_ultrasonic_input_to_centimeters(rightDistance) > 20)){
                decide_action(frontDistance, leftDistance,rightDistance, actionsTakenByRobot);
                reset_sensors(&frontDistance, &leftDistance,&rightDistance);
                milliSecondSinceLastReading = millis_get(); 
            }
        }
       
    }
    return 0;
}
