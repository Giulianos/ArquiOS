#include "lib.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);

void toggleVideoMode()
{
	systemCall(0x45, 0, 0, 0, 0, 0);
}

int getKeyState(int keycode)
{
	char state;

	systemCall(0x47, (uint64_t)&state, (uint64_t)keycode, 0, 0, 0);
	return state;
}

void drawBuffer(uint8_t * vbuffer)
{
	systemCall(0x046, 0, (uint64_t)vbuffer, 0, 0, 0);
}

void drawPixel(int x, int y, uint8_t * vbuffer, uint8_t atribute)
{
	if(x>79 || x<0 || y>25 || y<0)
		return;

	int position = (y*80 + x)*2;

	vbuffer[position] = ' ';
	vbuffer[position+1] = atribute;

}
