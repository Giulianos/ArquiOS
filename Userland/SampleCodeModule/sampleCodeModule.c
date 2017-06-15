/* sampleCodeModule.c */
#include <stdint.h>

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);

int main() {
	//Lets print something through syscalls
	systemCall(0x04, 0x00, (uint64_t)"Hola!", 5, 0, 0);
	return 0xDEADBEEF;
}
