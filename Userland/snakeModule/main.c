/* sampleCodeModule.c */
#include <stdint.h>
#include "stdlib/printf.h"
#include "stdlib/stdio.h"
#include "stdlib/stdlib.h"
#include "gameLib/lib.h"

extern uint64_t systemCall(uint64_t eax, uint64_t rbx, uint64_t rcx, uint64_t rdx, uint64_t rsi, uint64_t rdi);
extern void putc ( void* p, char c);

uint8_t screenBuffer[4000];

typedef enum {down_d, up_d, right_d, left_d} dir_t;

typedef struct
{
	char x;
	char y;
} point2d_t;

typedef struct
{
	dir_t direction;
	int length;
	point2d_t body[100];
	point2d_t fruit;
} snakeState_t;

char updatePosition(snakeState_t * state)
{
	int i;

	point2d_t tail = (state->body)[state->length - 1];

	for(i=state->length-1; i>0; i--)
	{
		(state->body)[i].x = (state->body)[i-1].x;
		(state->body)[i].y = (state->body)[i-1].y;
	}

	switch(state->direction)
	{
		case down_d:
			(state->body)[0].y++;
			break;
		case up_d:
			(state->body)[0].y--;
			break;
		case right_d:
			(state->body)[0].x++;
			break;
		case left_d:
			(state->body)[0].x--;
			break;
	}

	//Rollover
	(state->body)[0].y = (state->body)[0].y<0 ? 24 : (state->body)[0].y%25;
	(state->body)[0].x = (state->body)[0].x<0 ? 79 : (state->body)[0].x%80;

	if(((state->body)[0].x) == ((state->fruit).x) && ((state->body)[0].y) == ((state->fruit).y))
	{
		state->length++;
		(state->body)[state->length - 1] = tail;
		state->fruit.x = (state->fruit.x * 31 + state->fruit.y * 13)%80;
		state->fruit.y = (state->fruit.y * 31 + state->fruit.x * 13)%25;
	}

	return 1;
}

void updateDirection(snakeState_t * state)
{
	if(getKeyState(75) && state->direction != down_d) { state->direction = up_d; }
	if(getKeyState(85) && state->direction != up_d) { state->direction = down_d; }
	if(getKeyState(86) && state->direction != left_d) { state->direction = right_d; }
	if(getKeyState(84) && state->direction != right_d) { state->direction = left_d; }
}

void drawSnake(snakeState_t * state)
{
	int i;

	for(i=0; i<state->length; i++)
	{
		drawPixel((state->body)[i].x, (state->body)[i].y, (uint8_t *)&screenBuffer, 0xAA);
	}
	//Lets draw the fruit
	drawPixel((state->fruit).x, (state->fruit).y, (uint8_t *)&screenBuffer, 0xCC);
}

void initializeSnake(snakeState_t * state)
{
	state->direction = up_d;
	state->length = 4;

	(state->body)[0].y = (state->body)[1].y = (state->body)[2].y = (state->body)[3].y = 12;
	(state->body)[0].x = 12;
	(state->body)[1].x = 13;
	(state->body)[2].x = 14;
	(state->body)[3].x = 15;

	(state->fruit).x = 20;
	(state->fruit).y = 20;

}

int didAteBody(snakeState_t *  state)
{
	int i;

	for(i=state->length-1; i>0; i--)
	{
		if((state->body)[i].x == (state->body)[0].x && (state->body)[i].y == (state->body)[0].y)
			return 1;
	}
	return 0;
}

void clearScreenBuffer()
{
	int i;

	for(i=0; i<4000; i+=2)
	{
		screenBuffer[i]=' ';
		screenBuffer[i+1]=0x0;
	}
}

void delay()
{
	uint64_t i;
	for(i=0; i<10000000; i++)
	{
		i+1500;
	}
}

int main()
{
	char running = 1;

	init_printf(0, putc);

	snakeState_t snake;

	toggleVideoMode();

	clearScreenBuffer();

	initializeSnake(&snake);

	while(running) {
		updateDirection(&snake);
		updatePosition(&snake);
		if(didAteBody(&snake))
		{
			running = 0;
		}
		clearScreenBuffer();
		drawSnake(&snake);
		drawBuffer((uint8_t *)&screenBuffer);
		delay();
		if(getKeyState(79))
			running=0;
	}
	printf("Bye\n");

	toggleVideoMode();

	return 0;
}
