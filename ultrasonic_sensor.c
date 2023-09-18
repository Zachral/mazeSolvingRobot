#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "ultrasonic_sensor.h"

static unsigned int echo_duration;
static volatile int frontDistance = 0, leftDistance =0, rightDistance = 0;

ISR(TIMER2_COMPB_vect){
  leftDistance = get_distance_Ultrasonic_sensor(Left_Ultrasonic_Echo_pin); 
  rightDistance = get_distance_Ultrasonic_sensor(Right_Ultrasonic_Echo_pin);
  frontDistance = get_distance_Ultrasonic_sensor(Front_Ultrasonic_Echo_pin); 

  if(leftDistance < 9){

  }
  if(rightDistance < 9){

  }
  if(frontDistance < 9){

  }
  if(leftDistance < 4){

  }
  if(rightDistance < 4){

  }
  if(frontDistance < 4){

  }

}

void init_Ultrasonic_sensor(void)
{
  Ultrasonic_Triger_Port_Direction |= (Left_Ultrasonic_Trigger_pin);    // Ultrasonic Trigger pin
  Ultrasonic_Triger_Port &= ~(Left_Ultrasonic_Trigger_pin);   // Ultrasonic pin set to low
  
  Ultrasonic_Triger_Port_Direction |= (Right_Ultrasonic_Trigger_pin);    // Ultrasonic Trigger pin
  Ultrasonic_Triger_Port &= ~(Right_Ultrasonic_Trigger_pin);   // Ultrasonic pin set to low

  Ultrasonic_Triger_Port_Direction |= (Front_Ultrasonic_Trigger_pin);    // Ultrasonic Trigger pin
  Ultrasonic_Triger_Port &= ~(Front_Ultrasonic_Trigger_pin);   // Ultrasonic pin set to low

  Ultrasonic_Echo_Port_Direction &= ~(Left_Ultrasonic_Echo_pin);   // Ultrasonic Echo pin set to input
  Ultrasonic_Echo_Port |= Left_Ultrasonic_Echo_pin;      // Enable pullup

  Ultrasonic_Echo_Port_Direction &= ~(Right_Ultrasonic_Echo_pin);   // Ultrasonic Echo pin set to input
  Ultrasonic_Echo_Port |= Right_Ultrasonic_Echo_pin;      // Enable pullup

  Ultrasonic_Echo_Port_Direction &= ~(Front_Ultrasonic_Echo_pin);   // Ultrasonic Echo pin set to input
  Ultrasonic_Echo_Port |= Front_Ultrasonic_Echo_pin;      // Enable pullup

  //set timer registers and prescaler
  TCCR2A = 0; 
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22); 
	OCR2B = 250; 
	TIMSK2 = (1<<OCIE2B) | (1<<TOIE2); 
}

void trigger_Ultrasonic_sensor(void)
{
    Ultrasonic_Triger_Port |= (Left_Ultrasonic_Trigger_pin);
    Ultrasonic_Triger_Port |= (Right_Ultrasonic_Trigger_pin);
     Ultrasonic_Triger_Port |= (Front_Ultrasonic_Trigger_pin);
    _delay_us(10);
    Ultrasonic_Triger_Port &= ~(Left_Ultrasonic_Trigger_pin);
    Ultrasonic_Triger_Port &= ~(Right_Ultrasonic_Trigger_pin);
    Ultrasonic_Triger_Port &= ~(Front_Ultrasonic_Trigger_pin);
}

unsigned int read_Ultrasonic_sensor(unsigned int ultrasonicEchoPin)
{
    echo_duration = 0;
    while((Ultrasonic_Echo_Input&ultrasonicEchoPin) != ultrasonicEchoPin);
    while(((Ultrasonic_Echo_Input&ultrasonicEchoPin) == ultrasonicEchoPin) && (echo_duration<20000))
    {
      _delay_us(1);
      echo_duration++;
    }
    return echo_duration;
}

unsigned int get_distance_Ultrasonic_sensor(unsigned int ultrasonicEchoPin)
{
  trigger_Ultrasonic_sensor();
  return (read_Ultrasonic_sensor(ultrasonicEchoPin)/SCALE_FACTOR) + 20;
  
}

void integer_to_char(int integer_input, char* character_array)
{
  int reminder,quotient;    

  quotient = integer_input/100;	  
  reminder = integer_input%100;	  
  character_array[0] = quotient+0x30;	  
  quotient = reminder/10;	  
  reminder = reminder%10;	  
  character_array[1] = quotient+0x30;	  
  character_array[2] = reminder+0x30;	  
  character_array[3] = '\0';   

  return; 
}

int convert_ultrasonic_input_to_centimeters(int value){
  char data_buffer[4];
  int centimeters = 0;
  centimeters = value/10;
  //enables the value to be printed to serial monitor. 
  integer_to_char(centimeters,data_buffer);
  printf(data_buffer);
  printf("cm\r\n");

  return centimeters;
}

