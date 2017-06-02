#include <stdint.h>
#include <naiveConsole.h>

void keyboardDriver()
{
  static uint8_t phase = 0;
  static uint8_t seccondB = 0;
  static uint8_t firstB;
  if(phase == 0)
  {
    firstB = inputB(0x60);
    if(firstB == 0xE0)
      phase++;
    else
    {
      ncPrintHex(firstB);
      ncNewline();
    }
  }
  else
  {
    seccondB = inputB(0x60);
    phase = 0;
    ncPrintHex(firstB);
    ncPrintChar(' ');
    ncPrintHex(seccondB);
    ncNewline();
  }
}
