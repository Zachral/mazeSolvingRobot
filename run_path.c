#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "run_path.h"
#include "common_defines.h"
#include "drive.h"
#include "ultrasonic_sensor.h"

//to be able to determine path and timing, drive_forward does not have to be stored in array. 
void decide_action( int frontDistance, int leftDistance, int rightDistance, actions_taken_by_robot_t *actionsTakenByRobot){
    drive_forward();
    _delay_ms(500); 
    if (convert_ultrasonic_input_to_centimeters(leftDistance) > 20){ 
        add_action_to_current_path(LEFT_TURN, &*actionsTakenByRobot);
        actionsTakenByRobot->numberOfActions++;  
        turn_left();
        return; 
    }
    if((convert_ultrasonic_input_to_centimeters(rightDistance) > 20) 
        && (convert_ultrasonic_input_to_centimeters(frontDistance) > 20)){ 
        drive_forward();
        return; 
    }
    if((convert_ultrasonic_input_to_centimeters(rightDistance) > 20) 
        && (convert_ultrasonic_input_to_centimeters(frontDistance) < 20)){
        add_action_to_current_path(RIGHT_TURN, &*actionsTakenByRobot);
        actionsTakenByRobot->numberOfActions++; 
        turn_right();
        return; 
    }
    return;
}

void add_action_to_current_path(driving_action_t action, actions_taken_by_robot_t *actionsTakenByRobot){
        actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions].currentAction = action; 
        actionsTakenByRobot->currentRunPath[actionsTakenByRobot->numberOfActions].timeSinceAction = millis_get();
    return; 
}