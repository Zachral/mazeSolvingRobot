#include <avr/io.h>
#include <util/delay.h>
#include "ultrasonic_sensor.h"


unsigned int echo_duration;

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
  ;
}