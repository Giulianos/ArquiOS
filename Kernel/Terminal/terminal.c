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
static uint8_t selectedText[SCREEN_HEIGHT][SCREEN_WIDTH];
static uint8_t cursorX = SCREEN_WIDTH/2; //centrado
static uint8_t cursorY = SCREEN_HEIGHT/2;
static uint8_t pressingStartsX;
static uint8_t pressingStartsY;
static uint8_t pressingEndsX;
static uint8_t pressingEndsY;

void selectText(uint8_t initialX, uint8_t initialY, uint8_t finalX, uint8_t finalY)
{
  uint8_t x;
  uint8_t y;
  for(x=initialX, x<=finalX, x++)
  {
    for(y=initialY, y<=finalY, y++)
    {
      selectedText[y][x]=1;
    }
  }
}

void deselectText()
{
  uint8_t x;
  uint8_t y;
  for(x=pressingStartsX, x<=pressingEndsX, x++)
  {
    for(y=pressingStartsY, y<=pressingEndsY, y++)
    {
      selectedText[y][x]=0;
    }
  }
}

void copy()
{

}
void terminalMouseUpdate(mouseInfo_t mouse)
{
  //paso los valores de posX y posY al rango de la terminal.
  mouse.posX = (uint8_t)((mouse.posX*79)/999);
  mouse.posY = (uint8_t)(24-(mouse.posY*24)/349);
  static uint8_t state = QUIET;
  switch (state) {
    case QUIET: if(mouse.leftPressed && (cursorX != mouse.posX || cursorY != mouse.posY))
                { //paso a DRAGGING, debo seleccionar
                  pressingStartsX = cursorX;
                  pressingStartsY = cursorY;
                  selectText(cursorX ,cursorY, mouse.posX, mouse.posY);
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
                  selectText(cursorX, cursorY, cursorX, cursorY);
                  state = L_PRESSING;
                  break;
                }
                else //sigo en QUIET
                  break;
    case L_PRESSING:  if(!mouse.leftPressed)
                      { //paso a QUIET, copio y dejo de seleccionar
                        pressingEndsX = cursorX;
                        pressingEndsY = cursorY;
                        copy();
                        deselectText();
                        state = QUIET;
                        break;
                      }
                      if(!mouse.leftPressed && (cursorX != mouse.posX || cursorY != mouse.posY))
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
                      if(cursorX != mouse.posX || cursorY != mouse.posY)
                      { // paso a DRAGGING, selecciono y actualizo cursor
                        selectText(cursorX ,cursorY, mouse.posX, mouse.posY);
                        cursorX = mouse.posX;
                        cursorY = mouse.posY;
                        state = DRAGGING;
                        break;
                      }
                      else //sigo en L_PRESSING
                        break;

  case MOVING:  if(cursorX == mouse.posX && cursorY == mouse.posY)
                { //paso a QUIET
                  state = QUIET;
                  break;
                }
                if((cursorX == mouse.posX && cursorY == mouse.posY) && mouse.leftPressed)
                { // paso a L_PRESSING, inicializo pressing y selecciono
                  pressingStartsX = cursorX;
                  pressingStartsY = cursorY;
                  selectText(cursorX, cursorY, cursorX, cursorY);
                  state = L_PRESSING;
                  break;
                }
                if(mouse.leftPressed)
                { //paso a DRAGGING, inicializo pressing, selecciono y actualizo cursor
                  pressingStartsX = cursorX;
                  pressingStartsY = cursorY;
                  selectText(cursorX, cursorY, mouse.posX, mouse.posY);
                  cursorX = mouse.posX;
                  cursorY = mouse.posY;
                  state = DRAGGING;
                  break;
                }
    case DRAGGING:  if(!mouse.leftPressed)
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
                    if(cursorX == mouse.posX && cursorY == mouse.posY)
                    { //paso a L_PRESSING, selecciono posicion actual
                      selectText(cursorX, cursorY, cursorX, cursorY);
                      state = L_PRESSING;
                      break;
                    }
                    if((cursorX == mouse.posX && cursorY == mouse.posY)&&!mouse.leftPressed)
                    { //paso a QUIET, selecciono posicion actual, copio, dejo de seleccionar
                      selectText(cursorX, cursorY, cursorX, cursorY);
                      copy();
                      deselectText();
                      state = QUIET;
                      break;
                    }
                    else
                    { // sigo en DRAGGING, selecciono y actualizo cursor
                      selectText(cursorX, cursorY, mouse.posX, mouse.posY);
                      cursorX = mouse.posX;
                      cursorY = mouse.posY;
                      break;
                    }
  }
}