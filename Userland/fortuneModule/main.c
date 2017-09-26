/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"
#include "stdlib/stdio.h"
#include "stdlib/stdlib.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

int main()
{
	char buffer[LINE_LEN];
	init_printf(0, putc);
	printf("Vienvenido a al adibinador de la fortuna! Este mensaje es muy largo, y puede ser muy molesto al usuario. Tal vez deberiamos acortarlo?\n");
	printf("Cual es tu nonbre?: ");
	getline(buffer);
	printf("\nTu fortuna es:\n  ");
	uint64_t len = strlen(buffer);
	switch(len%6)
	{
		case 2: printf("You will forget that you ever knew me.\n"); break;
		case 3: printf("Your society will be sought by people of taste and refinement.\n"); break;
		case 4: printf("You will be honored for contributing your time and skill to a worthy cause.\n"); break;
		case 5: printf("Expect the worst, it's the least you can do.\n"); break;
		case 0: printf("Break into jail and claim police brutality.\n"); break;
		case 1: printf("Never be led astray onto the path of virtue\n"); break;
	}
	return 0xDEADBEEF;
}
