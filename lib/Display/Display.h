/**
 * 1602A 16 character x 2 lines LCD display
 * 
 * 4 bit data mode: connect PB0-4 to display DB4-7 (pins 11-14)
 */

#include <stdint.h>

#define FUNC_SET_A 0b00000011
#define FUNC_SET_B 0b00000010
#define FUNC_SET_C 0b00001000
#define DISPLAY_OFF 0b00001000
#define DISPLAY_ON  0b00001100 // cursor off, blink off
#define DISPLAY_CLEAR 0b00000001
#define ENTRY_MODE_SET 0b00000110

#define LCD_DATA_DDR  DDRB
#define LCD_DATA_PORT PORTB
#define LCD_ENABLE    PB4
#define LCD_RS        PB5

/**
 * transmit a command or data to LCD
 * @param registerSelect 0=command, 1=data
 */
void writeToLCD(uint8_t registerSelect, uint8_t instruction);
void writeStringToLCD(char str[]);
void initLCD();
/**
 * pulse the enable line for 1 us (min ~500ns) and wait 100 us between
 * commands
 */
void pulseEnableLCD();
void clearLCD();
