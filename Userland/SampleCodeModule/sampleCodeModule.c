/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"
#include "stdlib/string.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

int main() {
	//Lets print something through syscalls
	char buffer[40];
	uint64_t * pml4 = (char *)0x2000;
	uint64_t * pdp = (char *)0x3000;
	init_printf(0, putc);
	printf(":::SampleCodeModule:::", pml4);
	printf("First PML4 Entry dump(@0x%x): \n", pml4);
	for(int i=0; i<64; i++) {
		printf("%c", (*pml4>>(63-i))&0x1?'1':'0');
	}
	printf("\n");
	printf("First PDP Entry dump(@0x%x): \n", pdp);
	for(int i=0; i<64; i++) {
		printf("%c", (*pdp>>(63-i))&0x1?'1':'0');
	}
	printf("\n");
	//printf("PDP Base Address[0:16]: %x\n", (*pml4>>12)&0xFFFF);
	//printf("PDP Base Address[0:16]: %x\n", (*pml4>>12)&0xFFFF);
	return 0xDEADBEEF;
}
