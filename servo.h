#ifndef _SERVO_H_
#define _SERVO_H_

#include <avr/io.h>  
#include "common_defines.h"

#define SERVO_PORT_INDEX        D
#define SERVO_PORT              PORT_(SERVO_PORT_INDEX)
#define SERVO_PORT_DIRECTION    DDR_(SERVO_PORT_INDEX)
#define LEFT_SERVO_PIN          PD5
#define RIGHT_SERVO_PIN         PD6
 
void init_servo(void);
void left_servo_set_percentage(signed char percentage);
void right_servo_set_percentage(signed char percentage);
 
#endif