#include <avr/io.h>
#include <util/delay.h>
#include "common_defines.h"
#include "drive.h"

void decide_path(unsigned int direction){
    drive_forward();
    _delay_ms(500); 
    if (direction == LEFT) turn_left();
    if (direction == RIGHT) turn_right();
    drive_forward();
     
    return; 
   
}
