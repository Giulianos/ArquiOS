#include <stdint.h>
#include <naiveConsole.h>
#include "../KeyboardDriver/driver.h"
#include "../MouseDriver/driver.h"
#include "../VideoDriver/driver.h"
#include "keyMapping.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define QUIET 0
#define L_PRESSING 1
#define MOVING 2
#define DRAGGING 3 //apretar y mover

#define DEFAULT_TEXT_ATTR BLACK_BG | WHITE_FG
#define SELECTED_TEXT_ATTR WHITE_FG | LIGHT_BLUE_BG
#define CURSOR_ATTR LIGHT_GREEN_BG | LIGHT_GREEN_FG

static uint8_t screenText[SCREEN_HEIGHT][SCREEN_WIDTH];
static uint8_t selectedText[SCREEN_HEIGHT][SCREEN_WIDTH];
static uint8_t cursorX = SCREEN_WIDTH/2; //centrado
static uint8_t cursorY = SCREEN_HEIGHT/2;
static uint8_t pressingStartsX;
static uint8_t pressingStartsY;
static uint8_t pressingEndsX;
static uint8_t pressingEndsY;

//KEYBOARD
void terminalKeyboardUpdate(keycode_t key)
{
  static uint8_t state = 0;

  if(!(updateState(key, &state))&& key.action == KBD_ACTION_PRESSED)
  {
    uint8_t ascii = getAscii(key, state);
    ncPrintChar(ascii);
  }
}





//MOUSE
void selectText(uint8_t initialX, uint8_t initialY, uint8_t finalX, uint8_t finalY)
{
  uint16_t startPos = initialY * SCREEN_WIDTH + initialX;
  uint16_t endPos = finalY * SCREEN_WIDTH + finalX;
  uint8_t x, y;
  if(startPos>endPos)
  {
    uint16_t aux = startPos;
    startPos = endPos;
    endPos = aux;
  }
  while(startPos<=endPos)
  {
    y=startPos/SCREEN_WIDTH;
    x=startPos-y*SCREEN_WIDTH;
    selectedText[y][x]=1;
    startPos++;
  }
}

void deselectText()
{
  uint8_t x;
  uint8_t y;
  for(x=0; x<=SCREEN_WIDTH; x++)
  {
    for(y=0; y<=SCREEN_HEIGHT; y++)
    {
      selectedText[y][x]=0;
    }
  }
}

void updateScreen()
{
  uint8_t i, j, attr;
  for(i=0; i<SCREEN_HEIGHT; i++)
  {
    for(j=0; j<SCREEN_WIDTH; j++)
    {
        attr=(selectedText[i][j]==1)?SELECTED_TEXT_ATTR:DEFAULT_TEXT_ATTR;
        videoPutChar(screenText[i][j], i, j, attr);
    }
  }
  videoPutChar(screenText[cursorY][cursorX], cursorY, cursorX, CURSOR_ATTR);
}

void copy()
{

}

void terminalMouseUpdate(mouseInfo_t mouse)
{
  //paso los valores de posX y posY al rango de la terminal.
  mouse.posX = (uint8_t)((mouse.posX*79)/999);
  mouse.posY = (uint8_t)(24-(mouse.posY*24)/349);
  ncClear();
  ncPrintDec(mouse.posX);
  ncNewline();
  ncPrintDec(mouse.posY);
  static uint8_t state = QUIET;
  switch (state) {
    case QUIET: if(mouse.leftPressed && (cursorX != mouse.posX || cursorY != mouse.posY))
                { //paso a DRAGGING, debo seleccionar
                  pressingStartsX = cursorX;
                  pressingStartsY = cursorY;
                  deselectText();
                  selectText(pressingStartsX , pressingStartsY, mouse.posX, mouse.posY);
                  cursorX = mouse.posX;
                  cursorY = mouse.posY;
                  state = DRAGGING;
                  break;
                }
                else if(cursorX != mouse.posX || cursorY != mouse.posY)
                { // paso a MOVING, solo actualizo el cursor
                  cursorX = mouse.posX;
                  cursorY = mouse.posY;
                  state = MOVING;
                  break;
                }
                else if(mouse.leftPressed)
                { // paso a L_PRESSING, empiezo la seleccion
                  pressingStartsX = cursorX;
                  pressingStartsY = cursorY;
                  deselectText();
                  selectText(pressingStartsX , pressingStartsY, mouse.posX, mouse.posY);
                  state = L_PRESSING;
                  break;
                }
                else //sigo en QUIET
                  break;
    case L_PRESSING:  if(!mouse.leftPressed && (cursorX != mouse.posX || cursorY != mouse.posY))
                      { //paso a MOVING, copio, dejo de seleccionar y actualizo el cursor
                        pressingEndsX = cursorX;
                        pressingEndsY = cursorY;
                        copy();
                        deselectText();
                        cursorX = mouse.posX;
                        cursorY = mouse.posY;
                        state = MOVING;
                        break;
                      }
                      else if(!mouse.leftPressed)
                      { //paso a QUIET, copio y dejo de seleccionar
                        pressingEndsX = cursorX;
                        pressingEndsY = cursorY;
                        copy();
                        deselectText();
                        state = QUIET;
                        break;
                      }
                      else if(cursorX != mouse.posX || cursorY != mouse.posY)
                      { // paso a DRAGGING, selecciono y actualizo cursor
                        deselectText();
                        selectText(pressingStartsX , pressingStartsY, mouse.posX, mouse.posY);
                        cursorX = mouse.posX;
                        cursorY = mouse.posY;
                        state = DRAGGING;
                        break;
                      }
                      else //sigo en L_PRESSING
                        break;

  case MOVING:  if((cursorX == mouse.posX && cursorY == mouse.posY) && mouse.leftPressed)
                { // paso a L_PRESSING, inicializo pressing y selecciono
                  pressingStartsX = cursorX;
                  pressingStartsY = cursorY;
                  deselectText();
                  selectText(pressingStartsX , pressingStartsY, mouse.posX, mouse.posY);
                  state = L_PRESSING;
                  break;
                }
                else if(cursorX == mouse.posX && cursorY == mouse.posY)
                { //paso a QUIET
                  state = QUIET;
                  break;
                }
                else if(mouse.leftPressed)
                { //paso a DRAGGING, inicializo pressing, selecciono y actualizo cursor
                  pressingStartsX = cursorX;
                  pressingStartsY = cursorY;
                  deselectText();
                  selectText(pressingStartsX , pressingStartsY, mouse.posX, mouse.posY);
                  cursorX = mouse.posX;
                  cursorY = mouse.posY;
                  state = DRAGGING;
                  break;
                }
                else
                { //sigo en MOVING
                  cursorX = mouse.posX;
                  cursorY = mouse.posY;
                  break;
                }
    case DRAGGING:  if((cursorX == mouse.posX && cursorY == mouse.posY)&&!mouse.leftPressed)
                    { //paso a QUIET, selecciono posicion actual, copio, dejo de seleccionar
                      deselectText();
                      selectText(pressingStartsX , pressingStartsY, mouse.posX, mouse.posY);
                      pressingEndsX = cursorX;
                      pressingEndsY = cursorY;
                      copy();
                      deselectText();
                      state = QUIET;
                      break;
                    }
                    else if(!mouse.leftPressed)
                    { //paso a MOVING, copio y dejo de seleccionar, actualizo cursor
                      pressingEndsX = cursorX;
                      pressingEndsY = cursorY;
                      copy();
                      deselectText();
                      cursorX = mouse.posX;
                      cursorY = mouse.posY;
                      state = MOVING;
                      break;
                    }
                    else if(cursorX == mouse.posX && cursorY == mouse.posY)
                    { //paso a L_PRESSING, selecciono posicion actual
                      deselectText();
                      selectText(pressingStartsX , pressingStartsY, mouse.posX, mouse.posY);
                      state = L_PRESSING;
                      break;
                    }
                    else
                    { // sigo en DRAGGING, selecciono y actualizo cursor
                      deselectText();
                      selectText(pressingStartsX , pressingStartsY, mouse.posX, mouse.posY);
                      cursorX = mouse.posX;
                      cursorY = mouse.posY;
                      break;
                    }
  }
  updateScreen();
}
