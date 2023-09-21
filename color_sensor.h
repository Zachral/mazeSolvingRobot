#ifndef _COLOR_SENSOR_H__
#define _COLOR_SENSOR_H__
#include <avr/io.h> 
#include "common_defines.h"

//Needs to be configured according to configuration
#define COLOR_SENSOR_PORT_INDEX_S2_S3           B
#define COLOR_SENSOR_PORT_INDEX_S0_S1_OUT       D
#define COLOR_SENSOR_PORT_DIRECTION_S2_S3       DDR_(COLOR_SENSOR_PORT_INDEX_S2_S3)
#define COLOR_SENSOR_PORT_DIRECTION_S0_S1_OUT   DDR_(COLOR_SENSOR_PORT_INDEX_S0_S1_OUT)
#define COLOR_SENSOR_PORT_S2_S3                 PORT_(COLOR_SENSOR_PORT_INDEX_S2_S3)
#define COLOR_SENSOR_PORT_S0_S1_OUT             PORT_(COLOR_SENSOR_PORT_INDEX_S0_S1_OUT)
#define COLOR_SENSOR_OUTPUT                     PIN_(COLOR_SENSOR_PORT_INDEX_S0_S1_OUT)
#define S0_PIN                                  PIND2
#define S1_PIN                                  PIND3
#define S2_PIN                                  PINB1
#define S3_PIN                                  PINB2
#define OUT_PIN                                 PIND4
#define RED                                     1
#define GREEN                                   2
#define BLUE                                    3


void color_sensor_init();
void set_color_to_detect(uint8_t color);
unsigned int read_color_sensor(unsigned int out_pin, unsigned int timeout); 
long Convert_input_frequency(long frequency, long in_min, long in_max, long out_min, long out_max);
#endif