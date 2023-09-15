#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>
#include "button.h"

void button_init(){
    
	TCCR2A = 0; 
	TCCR2B = (1<<CS20) | (1<<CS21) | (1<<CS22); 
	OCR2B = 250; 
	TIMSK2 = (1<<OCIE2B) | (1<<TOIE2); 
    BIT_CLEAR(BUTTON_PORT_DIRECTION,BUTTON_PIN);
    BIT_SET(BUTTON_PORT, BUTTON_PIN); 
    return; 
}

void buttonClick(volatile bool *buttonWasPressed){
	 if (BUTTON_IS_CLICKED(BUTTON_INPUT_PIN,BUTTON_PIN)) {
		// Button press detected, wait for debouncing
		_delay_ms(DEBOUNCE_DELAY_MS);
		
		// Check the button state again after debouncing
		if (BUTTON_IS_CLICKED(BUTTON_INPUT_PIN, BUTTON_PIN)) {
			*buttonWasPressed = true; 
			}
		}
	return; 
}