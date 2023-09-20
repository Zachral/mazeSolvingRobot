#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "servo.h"
#include "button.h"
#include "drive.h"
#include "ultrasonic_sensor.h"
#include "run_path.h"
#include "millis.h"

int main(void){
    _delay_ms(1000);
    init_servo();
    button_init(); 
    init_serial();
    init_Ultrasonic_sensor();
    millis_init();
    sei();
    static volatile bool buttonWasPressed = false; 
    //Setting starting distance value to not trigger turning at start, convert_ultrasonic_input_to_centimeters devides this number by 10
    int frontDistance = 90, leftDistance = 50, rightDistance = 50;
    volatile millis_t milliSecondSinceLastReading = 0;



    while(!buttonWasPressed){
         buttonClick(&buttonWasPressed);
    }
    
    while(1){
        drive_forward();
        if(millis_get() - milliSecondSinceLastReading > 500){
            printf("reading");
            frontDistance = get_distance_Ultrasonic_sensor(Front_Ultrasonic_Echo_pin); 
            leftDistance = get_distance_Ultrasonic_sensor(Left_Ultrasonic_Echo_pin);
            rightDistance = get_distance_Ultrasonic_sensor(Right_Ultrasonic_Echo_pin);
            milliSecondSinceLastReading = millis_get(); 
        }
        if(convert_ultrasonic_input_to_centimeters(frontDistance) < 9){
           //color_check(); 
            u_turn(leftDistance, rightDistance); 
            reset_sensors(&frontDistance, &leftDistance,&rightDistance);
            milliSecondSinceLastReading = millis_get(); 
        }else if((convert_ultrasonic_input_to_centimeters(leftDistance) > 20) 
                || (convert_ultrasonic_input_to_centimeters(rightDistance) > 20)){
            decide_path(frontDistance, leftDistance,rightDistance);
            reset_sensors(&frontDistance, &leftDistance,&rightDistance);
            milliSecondSinceLastReading = millis_get(); 
        }
        // }else if(convert_ultrasonic_input_to_centimeters(rightDistance) > 20){
        //     decide_path(RIGHT); 
        //     reset_sensors(&frontDistance, &leftDistance,&rightDistance);
        //     milliSecondSinceLastReading = millis_get(); 
        // }
        if(convert_ultrasonic_input_to_centimeters(leftDistance) < 4){
        //    stabilize(LEFT);
        }
        if(convert_ultrasonic_input_to_centimeters(rightDistance) < 4){
           // stabilize(RIGHT);
        }
    }
    return 0;
}
