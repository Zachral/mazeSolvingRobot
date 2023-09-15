#ifndef _BUTTON_H__
#define _BUTTON_H__
#include <avr/io.h> 
#include <stdbool.h>
#include "common_defines.h"

#define BUTTON_PORT_INDEX       D
#define BUTTON_PORT_DIRECTION   DDR_(BUTTON_PORT_INDEX)
#define BUTTON_PORT             PORT_(BUTTON_PORT_INDEX)
#define BUTTON_INPUT_PIN        PIN_(BUTTON_PORT_INDEX)
#define BUTTON_PIN              7

#define BUTTON_IS_CLICKED(BUTTON_INPUT_PIN, BUTTON_PIN) !BIT_CHECK(BUTTON_INPUT_PIN, BUTTON_PIN)
#define DEBOUNCE_DELAY_MS 300


void buttonClick(volatile bool *buttonWasPressed);
void button_init();
#endif