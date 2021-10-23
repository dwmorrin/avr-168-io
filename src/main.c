#include <stdio.h>
#include <Display.h>
#include <Keypad.h>

int main()
{
  initLCD();
  uint8_t input_count = 0;
  while (1)
  {
    if (input_count == 16)
    {
      input_count = 0;
      clearLCD();
    }
    // wait for input
    while (!keypad_input_ready());
    uint8_t input = keypad_read();
    char message[32];
    if (input == KEYPAD_ERROR) {
      writeStringToLCD("ERROR");
    } else {
      ++input_count;
      if (input < 10) {
        sprintf(message, "%d", input);
      } else sprintf(message, "%c", input);
      writeStringToLCD(message);
    }
    // wait for release
    while (keypad_input_ready());
  }

  return 0;
}