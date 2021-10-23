#include <avr/io.h>
#include <util/delay.h>
#include "Display.h"

void writeToLCD(uint8_t registerSelect, uint8_t instruction) {
    // 0/LO for commands, 1/HI for data
    if (registerSelect == 0) {
        LCD_DATA_PORT &= ~(1 << LCD_RS); // Register Select LO
    } else if (registerSelect == 1) {
        LCD_DATA_PORT |= 1 << LCD_RS; // Register Select HI
    } else if (registerSelect == 2) { // INIT (pre 4-bit) command
        LCD_DATA_PORT &= ~(1 << LCD_RS); // Register Select LO
        LCD_DATA_PORT &= 0xf0; // data clear
        LCD_DATA_PORT |= instruction; // use the whole thing; doesn't repeat
        pulseEnableLCD();
        return;
    }

    LCD_DATA_PORT &= 0xf0; // data clear
    LCD_DATA_PORT |= (instruction >> 4); // load data MSB
    pulseEnableLCD(); // transmit
    LCD_DATA_PORT &= 0xf0; // data clear
    LCD_DATA_PORT |= (instruction & 0x0f); // load data LSB
    pulseEnableLCD(); // transmit

    return;
}

void writeStringToLCD(char str[]) {
    uint8_t i = 0;
    while (str[i] != 0) {
        if (i == 16) { // print 25 spaces to get us to the next line
            for (uint8_t j = 0; j < 24; j++) {
                writeToLCD(1, ' ');
            }
            while (str[i] == ' ') {
                i++; // skip this whitespace
            }
        }
        writeToLCD(1, str[i++]);
    }
}


void initLCD() {
    LCD_DATA_DDR |= 0b00111111; // using lower 6 bits of port
    LCD_DATA_PORT &= 0b11000000; // start with bits off
    _delay_ms(50);
    writeToLCD(2, FUNC_SET_A);
    _delay_ms(10);
    writeToLCD(2, FUNC_SET_A);
    _delay_us(200);
    writeToLCD(2, FUNC_SET_A);
    _delay_ms(5);
    writeToLCD(2, FUNC_SET_B);
    _delay_ms(5);
    writeToLCD(2, FUNC_SET_B);
    _delay_ms(5);
    writeToLCD(2, FUNC_SET_C);
    _delay_ms(5);
    writeToLCD(0, DISPLAY_OFF);
    _delay_ms(5);
    clearLCD();
    writeToLCD(0, ENTRY_MODE_SET);
    _delay_ms(100);
    writeToLCD(0, DISPLAY_ON);
    _delay_ms(5);
}

void clearLCD() {
    writeToLCD(0, DISPLAY_CLEAR);
    _delay_ms(24); // long execution time, per datasheet
}

void pulseEnableLCD() {
    LCD_DATA_PORT &= ~(1 << LCD_ENABLE);
    _delay_us(8);
    LCD_DATA_PORT |= 1 << LCD_ENABLE;
    _delay_us(8);
    LCD_DATA_PORT &= ~(1 << LCD_ENABLE);
    _delay_us(800);
}
