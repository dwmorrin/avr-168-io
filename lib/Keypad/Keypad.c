#include "Keypad.h"

void keypad_init()
{
    // setup to read from a MM74922 16-key decoder
    KEYPAD_DDR |= (1 << KEYPAD_DATA_READ_ENABLE_PIN);
    // for now we will always read, maybe change this later
    PORTD &= ~(1 << KEYPAD_DATA_READ_ENABLE_PIN);
    KEYPAD_DDR &= 0xF0; // lower nibble = data input
    KEYPAD_DDR &= ~(1 << KEYPAD_DATA_AVAIL_PIN);
}

uint8_t keypad_input_ready()
{
    return PIND & (1 << KEYPAD_DATA_AVAIL_PIN);
}

uint8_t keypad_read_code()
{
    return PIND & 0x0F;
}

uint8_t keypad_read()
{
    switch(keypad_read_code())
    {
        case 0: return 1;
        case 1: return 2;
        case 2: return 3;
        case 3: return 65;
        case 4: return 4;
        case 5: return 5;
        case 6: return 6;
        case 7: return 66;
        case 8: return 7;
        case 9: return 8;
        case 10: return 9;
        case 11: return 67;
        case 12: return 42;
        case 13: return 0;
        case 14: return 35;
        case 15: return 68;
        default: return KEYPAD_ERROR;
    }
}