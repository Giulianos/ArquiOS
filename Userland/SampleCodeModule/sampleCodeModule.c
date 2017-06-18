/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"
#include "stdlib/string.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

int main() {
	//Lets print something through syscalls
	char buffer[40];
	init_printf(0, putc);
	printf("Hola soy el sampleCodeModule y repito todo lo que digas\n");
	while(1){
		printf("- ");
		systemCall(0x3, 0, buffer, 40, 0, 0);
		if(!strcmp(buffer, "Hola")) {
			printf("+ Hola, como andas?\n");
		} else {
			printf("+ %s\n", buffer);
		}
	}
	return 0xDEADBEEF;
}
