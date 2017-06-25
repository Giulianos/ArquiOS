#include <stdint.h>
static uint16_t f = 0; //first character in the buffer
static uint16_t l = 0; //last character in the buffer
#define MAX 4096 //dos pantallas, redondeo a 4KB
static uint8_t buffer[MAX+1];

void putChar(uint8_t c)
{
  if(l == MAX)
  {
    if(f == 0)
      return;
    buffer[0] = c;
    l = 1;
  }
  else
  {
    buffer[l] = c;
    l++;
  }
}

uint8_t getChar()
{
  if(f == l)
    return 0;
  if(f == MAX)
  {
    if(l == 0)
    {
      f = 0;
      return 0;
    }
    f = 1;
  }
  else
    f++;
  return buffer[f-1];
}

uint8_t bufferIsEmpty()
{
  return ((f == l)||(f == MAX && l == 0))?1:0;
}

void eraseFromBuffer()
{
  if(bufferIsEmpty())
    return;
  l = (l==0)?MAX:(l-1);
}
