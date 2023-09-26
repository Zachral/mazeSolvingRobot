#ifndef _DRIVE_H__
#define _DRIVE_H__

void drive_forward();
void drive_slowly_forward(); 
void back_up();
void stop();
void turn_left();
void turn_right();
void u_turn(int leftDistance, int rightDistance);
#endif