#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "color_sensor.h"
#include "common_defines.h"

void color_sensor_init(){
    //set as output
    COLOR_SENSOR_PORT_DIRECTION_S0_S1_OUT   |= (1<<S0_PIN);
    COLOR_SENSOR_PORT_DIRECTION_S0_S1_OUT   |= (1<<S1_PIN);
    COLOR_SENSOR_PORT_DIRECTION_S2_S3       |= (1<<S2_PIN);
    COLOR_SENSOR_PORT_DIRECTION_S2_S3       |= (1<<S3_PIN);

    //set as input
    COLOR_SENSOR_PORT_DIRECTION_S0_S1_OUT   &= ~(1<<OUT_PIN);

    //Set scaling to 20% - recomended for arduino
    COLOR_SENSOR_PORT_S0_S1_OUT             |= (1<<S0_PIN);
    COLOR_SENSOR_PORT_S0_S1_OUT             &= ~(1<<S1_PIN);
    printf("I am set up!\n");
   
}

void set_color_to_detect(uint8_t color){
  switch (color){
  case RED:
      //Sets the sensor to detect red
      COLOR_SENSOR_PORT_S2_S3                   &= ~(1<<S2_PIN);
      COLOR_SENSOR_PORT_S2_S3                   &= ~(1<<S3_PIN);
      break;
  case GREEN:
      //Sets the sensor to detect green
      COLOR_SENSOR_PORT_S2_S3                   |= (1<<S2_PIN);
      COLOR_SENSOR_PORT_S2_S3                   |= (1<<S3_PIN);
      break;
  case BLUE:
      //Sets the sensor to detect blue
      COLOR_SENSOR_PORT_S2_S3                   &= ~(1<<S2_PIN);
      COLOR_SENSOR_PORT_S2_S3                   |= (1<<S3_PIN);
      break;
  default:
    break;
  }
}

unsigned int read_color_sensor(unsigned int out_pin, unsigned int timeout){
    unsigned int pulseWidth = 0, iterations = 0, maxIterations = microsecondsToClockCycles(timeout)/16;
    //wait for the pulse before to end
   
    while (!(BIT_CHECK(COLOR_SENSOR_OUTPUT,out_pin))) {
      //returns if there is no signal
      if(iterations++ == maxIterations) return 0;
    }

    //wait for signal to go low
    while(BIT_CHECK(COLOR_SENSOR_OUTPUT,out_pin)){
      if(iterations++ ==  maxIterations) return 0;
    }

    //start reading the low signal until it goes high
    while (!(BIT_CHECK(COLOR_SENSOR_OUTPUT,out_pin))){
      if(iterations++ == maxIterations) return 0;
      pulseWidth++;
    }

    //converts frequency to micro seconds, the loop is approximatley 20 clockcycles long and about 16 clocks from start to end. 
    return clockCyclesToMicroseconds(pulseWidth *21 + 16);  
}

long Convert_input_frequency(long frequency, long in_min, long in_max, long out_min, long out_max) {
  return (frequency - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

unsigned int red_is_detected(){
        unsigned int redFrequency = 0, greenFrequency = 0, blueFrequency = 0, redColor = 0,  greenColor = 0, blueColor = 0; 

        set_color_to_detect(RED);
        redFrequency = read_color_sensor(OUT_PIN,255); 
        redColor = Convert_input_frequency(redFrequency,6, 28 , 255, 0); 
        _delay_ms(100);

        set_color_to_detect(GREEN);
        greenFrequency = read_color_sensor(OUT_PIN,255);
        greenColor = Convert_input_frequency(greenFrequency, 18, 56, 255, 0);
        _delay_ms(100);

        set_color_to_detect(BLUE);
        blueFrequency = read_color_sensor(OUT_PIN,255);
        blueColor = Convert_input_frequency(blueFrequency, 14, 46, 255, 0); 
        _delay_ms(100); 

        if(redColor > greenColor && redColor > blueColor){ 
          printf("RED DETECTED");
          return 1;
        }
        if(greenColor > redColor && greenColor > blueColor){ 
          printf("GREEN DETECTED\n");
          return 0;
        }
        if(blueColor > redColor && blueColor > greenColor){
          printf("BLUE DETECTED\n");
          return 0;
        }
    return 0; 
}
