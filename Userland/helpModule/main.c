/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"
#include "stdlib/string.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

int main() {
	init_printf(0, putc);
	printf("Los comandos disponibles son: ");
	printf("\nhelp    Muestra los comandos disponibles");
	printf("\nfortune  Ejecuta el programa fortune");
	printf("\nsample  Muestra informacion de paginacion");
	return 0xDEADBEEF;
}
