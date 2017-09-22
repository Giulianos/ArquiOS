/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"
#include "stdlib/stdio.h"
#include "stdlib/stdlib.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

int main()
{
	systemCall(0x44, 0, 0, 0, 0 ,0);
	return 0xDEADBEEF;
}
