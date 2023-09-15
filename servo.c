#include <avr/io.h>
#include <avr/interrupt.h>
#include  "servo.h "
 
#define TIME_VALUE	(40000) 
#define RESET_VALUE	(65636ul-TIME_VALUE)
#define STOP_VALUE	(TIME_VALUE*0.076)
//(TIME_VALUE*0.075)
#define RANGE		(TIME_VALUE*0.0482)
// (TIME_VALUE*0.025)
 
ISR(TIMER1_OVF_vect)
{
	TCNT1 = RESET_VALUE;
 
	SERVO_PORT |= (1<<LEFT_SERVO_PIN);
	SERVO_PORT |= (1<<RIGHT_SERVO_PIN);
}
 
ISR(TIMER1_COMPA_vect)
{
	SERVO_PORT &= ~(1<<LEFT_SERVO_PIN);
}
 
ISR(TIMER1_COMPB_vect)
{
	SERVO_PORT &= ~(1<<RIGHT_SERVO_PIN);
}
 
void init_servo(void)
{
	// Config pins as output
	SERVO_PORT_DIRECTION |= (1<<LEFT_SERVO_PIN);
	SERVO_PORT_DIRECTION |= (1<<RIGHT_SERVO_PIN);
 
	// Use mode 0, clkdiv = 8
	TCCR1A = 0;
	TCCR1B = (0<<CS12) | (1<<CS11) | (0<<CS10);
	// Interrupts on OCA, OCB and OVF
	TIMSK1 = (1<<OCIE1B) | (1<<OCIE1A) | (1<<TOIE1);
 
	TCNT1 = RESET_VALUE;
 
	left_servo_set_percentage(0);
	right_servo_set_percentage(0);
 
}
 
void left_servo_set_percentage(signed char percentage)
{
	if (percentage >= -100 && percentage <= 100)
	{
		OCR1A = RESET_VALUE+STOP_VALUE+(RANGE/100*percentage);
	}
}
 
void right_servo_set_percentage(signed char percentage)
{
	if (percentage >= -100 && percentage <= 100)
	{
		OCR1B = RESET_VALUE+STOP_VALUE+(RANGE/100*percentage);
	}
}