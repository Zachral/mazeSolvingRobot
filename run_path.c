#include <avr/io.h>
#include <util/delay.h>
#include "common_defines.h"
#include "drive.h"

void decide_path( int frontDistance, int leftDistance, int rightDistance){
    drive_forward();
    _delay_ms(500); 
    if (leftDistance > 20){ 
        turn_left();
        return; 
    }
    if((rightDistance > 20) && (frontDistance > 20)){ 
        drive_forward();
        return; 
    }
    if((rightDistance > 20) && (frontDistance < 20)){
        turn_right();
        return; 
    }
    return;
}

