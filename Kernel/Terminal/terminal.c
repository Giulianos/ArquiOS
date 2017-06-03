#include <stdint.h>
#include "MouseDriver/driver.h"
#include "KeyboardDriver/driver.h"
#include "VideoDriver/driver.h"
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define QUIET 0
#define L_PRESSING 1
#define MOVING 2
#define DRAGGING 3 //apretar y mover
static uint8_t screenText[SCREEN_HEIGHT][SCREEN_WIDTH];
static uint8_t screenOverlay[SCREEN_HEIGHT][SCREEN_WIDTH];
static uint8_t cursorX;
static uint8_t cursorY;


void updateMouseCursor(mouseInfo_t mouse)
{
  uint8_t state = QUIET;
  switch (state) {
    case QUIET: if(mouse.leftPressed && (cursorX != mouse.posX || cursorY != mouse.posY))
                {
                  selectText(cursorX ,cursorY, mouse.posX, mouse.posY);
                  cursorX = mouse.posX;
                  cursorY = mouse.posY;
                  state = DRAGGING;
                  break;
                }

    case L_PRESSING:
    case MOVING:
    case DRAGGING:
  }

}
