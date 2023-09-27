#ifndef _RUN_PATH_H__
#define _RUN_PATH_H__

#include "millis.h"

typedef struct{
    char currentAction; 
    volatile millis_t timeSinceAction;
}direction_and_time_of_action_t; 

typedef struct{
    char numberOfActions;
    direction_and_time_of_action_t currentRunPath[50]; 
}actions_taken_by_robot_t;


typedef enum {
    LEFT_TURN,
    RIGHT_TURN, 
    U_TURN
}driving_action_t; 

void decide_action( int frontDistance, int leftDistance, int rightDistance, actions_taken_by_robot_t actionsTakenByRobot); 
void add_action_to_current_path(driving_action_t action, actions_taken_by_robot_t actionsTakenByRobot);
#endif