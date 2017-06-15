/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

int main() {
	//Lets print something through syscalls
	char buffer[40];
	init_printf(0, putc);
	printf("Hola %d %s", 45, "<- eso es un numero!");
	return 0xDEADBEEF;
}
