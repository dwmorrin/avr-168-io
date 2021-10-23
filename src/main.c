#include <stdio.h>
#include <util/delay.h>
#include <Display.h>
#include <Keypad.h>

int main()
{
  initLCD();
  while (1)
  {
    // wait for input
    while (!keypad_input_ready());
    char input = keypad_read_char();
    char message[32];
    if (input == KEYPAD_ERROR) {
      writeStringToLCD("ERROR");
    } else if (input == '*') {
      clearLCD();
    } else {
      // echo input
      sprintf(message, "%c", input);
      writeStringToLCD(message);
    }
    // wait for release
    while (keypad_input_ready());
  }

  return 0;
}