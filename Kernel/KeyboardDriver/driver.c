#include <stdint.h>
#include <hardwareCom.h>
#include "../Terminal/terminal.h"
#include "driver.h"

void keyboardDriver()
{
  static uint8_t phase = 0;
  static uint8_t secondB = 0;
  static uint8_t firstB;
  if(phase == 0)
  {
    firstB = inputB(0x60);
    if(firstB == 0xE0)
      phase++;
    else
    {
      terminalKeyboardUpdate(scancodeToKeycode(firstB, secondB));
    }
  }
  else
  {
    secondB = inputB(0x60);
    phase = 0;
    terminalKeyboardUpdate(scancodeToKeycode(firstB, secondB));
  }
}
