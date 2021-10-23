#ifndef KEYPAD_H
#define KEYPAD_H
#include <avr/io.h>

#define KEYPAD_DDR DDRD
#define KEYPAD_DATA_AVAIL_PIN PD5
#define KEYPAD_DATA_READ_ENABLE_PIN PD4
// data pins are PD0-3

#define KEYPAD_ERROR 0xFF

void keypad_init();
uint8_t keypad_input_ready();
uint8_t keypad_read();
uint8_t keypad_read_code();

#endif