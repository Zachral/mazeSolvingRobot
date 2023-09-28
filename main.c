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
    actionsTakenByRobot.numberOfActions = 0; 
    static volatile bool isButtonPressed = false; 
    //Setting starting distance value to not trigger turning at start, convert_ultrasonic_input_to_centimeters devides this number by 10
    int frontDistance = 90, leftDistance = 60, rightDistance = 60;
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
        
        if(convert_ultrasonic_input_to_centimeters(leftDistance) < 6){
            stabilize(LEFT);
        }
        if(convert_ultrasonic_input_to_centimeters(rightDistance) < 6){
            stabilize(RIGHT);
        }
        if(convert_ultrasonic_input_to_centimeters(frontDistance) < 8){
            drive_slowly_forward();
            if(detect_red_color()){
                light_led();
                break; 
            }else{
                back_up(); 
                u_turn(leftDistance, rightDistance); 
                add_action_to_current_path(U_TURN, &actionsTakenByRobot);
                for(int i = 0; i <= actionsTakenByRobot.numberOfActions; i++){
                    printf("Action %d = %d. Num of actions = %d\n", i, actionsTakenByRobot.currentRunPath[i].currentAction, actionsTakenByRobot.numberOfActions); 
                }
                actionsTakenByRobot.numberOfActions++;
                //reset_sensors(&frontDistance, &leftDistance,&rightDistance);
            }
        }
        if(millis_get() - milliSecondSinceLastReading > 350){
            if((convert_ultrasonic_input_to_centimeters(leftDistance) > 20) && is_making_an_action(actionsTakenByRobot, LEFT_TURN)){
                do_action(LEFT, &actionsTakenByRobot);
            }
            if(((convert_ultrasonic_input_to_centimeters(rightDistance) > 20) 
            && (convert_ultrasonic_input_to_centimeters(frontDistance) < 20)) && is_making_an_action(actionsTakenByRobot, RIGHT_TURN)){
                do_action(RIGHT, &actionsTakenByRobot);
            }    
            //reset_sensors(&frontDistance, &leftDistance,&rightDistance);
            milliSecondSinceLastReading = millis_get(); 
                for(int i = 0; i < actionsTakenByRobot.numberOfActions; i++){
                    printf("Action %d = %d. Num of actions = %d\n", i, actionsTakenByRobot.currentRunPath[i].currentAction, actionsTakenByRobot.numberOfActions); 
                }
            }
        }
    return 0;
}
