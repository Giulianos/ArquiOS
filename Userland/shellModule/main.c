/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"
#include "stdlib/stdio.h"
#include "stdlib/stdlib.h"
#include "commandParser.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

int main()
{
	char buffer[LINE_LEN];
	init_printf(0, putc);
	printf(">");
	getline(buffer);
	execve(parseCommand(buffer));
	return 0xDEADBEEF;
}
