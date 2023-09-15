#include <avr/io.h>
#include <util/delay.h>
#include "ultrasonic_sensor.h"

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
    unsigned int echo_duration = 0;
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
  ;
}


void integer_to_char(int integer_input, char* character_array, char type)
{
  int reminder,quotient;    
  if (type == 2)  
  {	  
    quotient = integer_input/10;	  
    reminder = integer_input%10;	  
    character_array[0] = quotient+0x30;	  
    character_array[1] = reminder+0x30;	  
    character_array[2] = '\0';  
  }    
  if (type == 3)  
  {	  
    quotient = integer_input/100;	  
    reminder = integer_input%100;	  
    character_array[0] = quotient+0x30;	  
    quotient = reminder/10;	  
    reminder = reminder%10;	  
    character_array[1] = quotient+0x30;	  
    character_array[2] = reminder+0x30;	  
    character_array[3] = '\0';  
  } 
  if (type == 4)  
  {	  
    quotient = integer_input/1000;	// 1234  -- 1  
    reminder = integer_input%1000;	// 234  
    character_array[0] = quotient+0x30;	    //'1'
    quotient = reminder/100;	       // 234  -- 2
    reminder = reminder%100;	       // 34
    character_array[1] = quotient+0x30;	  // '2'
    quotient = reminder/10;	        //  3  
    reminder = reminder%10;	
    character_array[2] = quotient+0x30;	  
    character_array[3] = reminder+0x30;	  
    character_array[4] = '\0';  
  } 
}

int convert_ultrasonic_input_to_centimeters(int value)
{
char data_buffer[4],buffer[50],centimeters = 0;
 centimeters = value/10;
  //enables the value to be printed to serial monitor. 
  integer_to_char(c_m,data_buffer,3);
  printf(data_buffer);
  printf("cm\r\n");

   return centimeters;
}