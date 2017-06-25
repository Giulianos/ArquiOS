#include <stdint.h>
#include "stdio.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);

uint64_t getline(char * buffer)
{
  return systemCall(0x03, 0x00, buffer, LINE_LEN, 0, 0);
}
