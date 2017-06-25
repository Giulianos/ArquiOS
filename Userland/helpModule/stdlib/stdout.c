#include <stdint.h>

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);

void putc ( void* p, char c)
{
  systemCall(0x04, 0x00, (uint64_t)&c, 1, 0, 0);
}
