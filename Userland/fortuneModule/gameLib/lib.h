#ifndef _GAME_LIB_H
#define _GAME_LIB_H

#include <stdint.h>

void toggleVideoMode();
int getKeyState(int keycode);
void drawBuffer(uint8_t * vbuffer);
void drawPixel(int x, int y, uint8_t * vbuffer, uint8_t atribute);

#endif
