#ifndef _RUN_PATH_H__
#define _RUN_PATH_H__

#include "millis.h"

typedef struct{
    char currentDirection; 
    volatile millis_t timeSinceDirectionChange;
}direction_and_time_of_turn_t; 

typedef struct{
    direction_and_time_of_turn_t currentRunPath[50]; 
}current_run_path;


typedef enum {
    LEFT_TURN,
    RIGHT_TURN,
    STRAIGHT, 
    U_TURN
}driving_direction_t; 

void decide_path( int frontDistance, int leftDistance, int rightDistance); 
#endif