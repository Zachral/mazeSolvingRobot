#include <avr/io.h>
#include <util/delay.h>
#include "common_defines.h"
#include "drive.h"
#include "ultrasonic_sensor.h"

void decide_path( int frontDistance, int leftDistance, int rightDistance){
    drive_forward();
    _delay_ms(500); 
    if (convert_ultrasonic_input_to_centimeters(leftDistance) > 20){ 
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
        turn_right();
        return; 
    }
    return;
}

