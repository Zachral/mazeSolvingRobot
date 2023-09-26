#ifndef _ULTRASONIC_SENSOR_H___
#define _ULTRASONIC_TRIGGER_ECHO_H___

#include "common_defines.h"

#define    BIT7    0x80
#define    BIT6    0x40
#define    BIT5    0x20
#define    BIT4    0x10
#define    BIT3    0x08
#define    BIT2    0x04
#define    BIT1    0x02
#define    BIT0    0x01

/*Need to change according to connections*/
#define ULTRASONIC_PORT_IND             C            
#define LEFT_ULTRASONIC_ECHO            0            
#define LEFT_ULTRASONIC_TRIGGER         1            
#define FRONT_ULTRASONIC_ECHO           2            
#define FRONT_ULTRASONIC_TRIGGER        3            
#define RIGHT_ULTRASONIC_ECHO           4            
#define RIGHT_ULTRASONIC_TRIGGER        5     

//Change to calibrate sensor distance
#define SCALE_FACTOR      3


#define Ultrasonic_Triger_Port_Direction            DDR_(ULTRASONIC_PORT_IND)
#define Ultrasonic_Triger_Port                      PORT_(ULTRASONIC_PORT_IND)
#define Left_Ultrasonic_Trigger_pin                  BIT_(LEFT_ULTRASONIC_TRIGGER)
#define Right_Ultrasonic_Trigger_pin                  BIT_(RIGHT_ULTRASONIC_TRIGGER)
#define Front_Ultrasonic_Trigger_pin                  BIT_(FRONT_ULTRASONIC_TRIGGER)

#define Ultrasonic_Echo_Port_Direction              DDR_(ULTRASONIC_PORT_IND)
#define Ultrasonic_Echo_Port                        PORT_(ULTRASONIC_PORT_IND)
#define Ultrasonic_Echo_Input                       PIN_(ULTRASONIC_PORT_IND)
#define Left_Ultrasonic_Echo_pin                    BIT_(LEFT_ULTRASONIC_ECHO)
#define Right_Ultrasonic_Echo_pin                    BIT_(RIGHT_ULTRASONIC_ECHO)
#define Front_Ultrasonic_Echo_pin                    BIT_(FRONT_ULTRASONIC_ECHO)

void init_Ultrasonic_sensor(void);
void trigger_Ultrasonic_sensor(void);
unsigned int read_Ultrasonic_sensor(unsigned int ultrasonicEchoPin);
unsigned int get_distance_Ultrasonic_sensor(unsigned int ultrasonicEchoPin);
int convert_ultrasonic_input_to_centimeters(int value);
void integer_to_char(int integer_input, char* character_array);
void reset_sensors(int *frontDistance, int *leftDistance, int *rightDistance);
void read_ultrasonic_sensor(int *frontDistance, int *leftDistance,  int *rightDistance);



#endif