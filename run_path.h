#ifndef _RUN_PATH_H__
#define _RUN_PATH_H__

#include "millis.h"

typedef enum {
    LEFT_TURN,
    RIGHT_TURN, 
    U_TURN
}driving_action_t; 

typedef struct{
    driving_action_t currentAction; 
    volatile millis_t timeSinceAction;
}direction_and_time_of_action_t; 

typedef struct{
    int numberOfActions;
    direction_and_time_of_action_t currentRunPath[50]; 
}actions_taken_by_robot_t;


void decide_action( int frontDistance, int leftDistance, int rightDistance, actions_taken_by_robot_t *actionsTakenByRobot); 
unsigned int is_making_an_action(actions_taken_by_robot_t actionsTakenByRobot, driving_action_t currentTurn);
void do_action(int direction, actions_taken_by_robot_t *actionsTakenByRobot);
void add_action_to_current_path(driving_action_t action, actions_taken_by_robot_t *actionsTakenByRobot);
#endif