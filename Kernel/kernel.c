#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interrupts.h>
#include "PagingManager/paging.h"
#include "ModulesManager/modules.h"

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

extern uint64_t systemCall(uint64_t rax,uint64_t rbx,uint64_t rcx,uint64_t rdx,uint64_t rsi,uint64_t rdi);

static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	loadModulesToKernel();
	clearBSS(&bss, &endOfKernel - &bss);
	return getStackBase();
}

int main()
{
	ncClear();
	//mapUserspace(0x1000000);
	configureInterrupts();

	((EntryPoint)sampleCodeModuleAddress)();

	//systemCall();

	while(1){
	}

	return 0;
}
