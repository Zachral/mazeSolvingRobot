#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "run_path.h"
#include "common_defines.h"
#include "drive.h"
#include "ultrasonic_sensor.h"

void decide_action( int frontDistance, int leftDistance, int rightDistance, actions_taken_by_robot_t *actionsTakenByRobot){
    drive_forward();
    _delay_ms(500); 
    if (convert_ultrasonic_input_to_centimeters(leftDistance) > 20){ 
        //this condition checks if the last turn made is left and if that was less then 2 seconds ago.
        //if thats the case, skip this turn action. This is for timing issues when comming back from a dead end. 
        //the same check will be done for a right turn. 
        if((actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions-1].currentAction == LEFT_TURN) && 
        (millis_get() - actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions-1].timeSinceAction < 2000)){
            return; 
        }else{
            add_action_to_current_path(LEFT_TURN, &*actionsTakenByRobot);
            actionsTakenByRobot->numberOfActions++;  
            turn_left();
            return; 
        }
    }
    //to be able to determine path and timing, drive_forward does not have to be stored in array. 
    if((convert_ultrasonic_input_to_centimeters(rightDistance) > 20) 
        && (convert_ultrasonic_input_to_centimeters(frontDistance) > 20)){ 
        drive_forward();
        return; 
    }
    if((convert_ultrasonic_input_to_centimeters(rightDistance) > 20) 
    && (convert_ultrasonic_input_to_centimeters(frontDistance) < 20)){
        if((actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions-1].currentAction == RIGHT_TURN) && 
        (millis_get() - actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions-1].timeSinceAction < 2000)){
            return;
        }else{
            add_action_to_current_path(RIGHT_TURN, &*actionsTakenByRobot);
            actionsTakenByRobot->numberOfActions++; 
            turn_right();
            return; 
        }
    }
    return;
}

void add_action_to_current_path(driving_action_t action, actions_taken_by_robot_t *actionsTakenByRobot){
    actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions].currentAction = action; 
    actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions].timeSinceAction = millis_get();
    return; 
}