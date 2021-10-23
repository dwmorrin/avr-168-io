#include <Display.h>

int main()
{
  initLCD();
  writeStringToLCD("HELLO WORLD");

  while (1);

  return 0;
}