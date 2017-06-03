#include "driver.h"

static uint8_t* screenBuffer = (uint8_t*) 0xB8000;
static uint16_t screenSize = 80*25;

uint8_t videoPrint(char* msg, uint8_t row, uint8_t col, uint8_t attr){
  uint16_t i;
  uint8_t * position = (uint8_t*)(screenBuffer + row*80*2 + col*2);
  for(i=0; (msg[i]!=0) && (position<(uint8_t*)(screenBuffer+screenSize*2)); i++){
    *(position++) = msg[i];
    *(position++) = attr;
  }
  return (position<(uint8_t*)(screenBuffer+screenSize*2));
}

uint8_t videoPutChar(char c, uint8_t row, uint8_t col, uint8_t attr){
  uint8_t * position = (uint8_t*)(screenBuffer + row*80*2 + col*2);
  *(position++) = c;
  *(position++) = attr;
  return (position<(uint8_t*)(screenBuffer+screenSize*2));
}
