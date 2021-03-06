#include <stdint.h>
#include <naiveConsole.h>
#include "../KeyboardDriver/driver.h"
#include "../MouseDriver/driver.h"
#include "../VideoDriver/driver.h"
#include "../ModulesManager/modules.h"
#include "keyMapping.h"
#include "buffer.h"

#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25
#define QUIET 0
#define L_PRESSING 1
#define MOVING 2
#define DRAGGING 3 //apretar y mover
#define PASTE 4

#define DEFAULT_TEXT_ATTR BLACK_BG | WHITE_FG
#define SELECTED_TEXT_ATTR WHITE_FG | LIGHT_BLUE_BG
#define CURSOR_ATTR LIGHT_GREEN_BG | LIGHT_GREEN_FG

#define SYSCALL_READ 0x03
#define SYSCALL_WRITE 0x04
#define SYSCALL_EXECVE 0x0B
#define SYSCALL_EXIT 0x01
#define SYSCALL_CLEAR 0x44
#define SYSCALL_TOGGLEVIDEO 0x45
#define SYSCALL_VIDEODRAW 0x046
#define SYSCALL_GETKEYSTATE 0x47

static uint8_t screenText[SCREEN_HEIGHT][SCREEN_WIDTH];
static uint8_t selectedText[SCREEN_HEIGHT][SCREEN_WIDTH];
static uint8_t cursorX = SCREEN_WIDTH/2; //centrado
static uint8_t cursorY = SCREEN_HEIGHT/2;
static uint8_t pressingStartsX;
static uint8_t pressingStartsY;
static uint8_t pressingEndsX;
static uint8_t pressingEndsY;
static uint8_t enterPressed = 0;
static uint8_t readChars = 0;

static uint8_t videoModeEnabled = 0;

static uint8_t keyboardState[1024];

static uint8_t currentScreenRow = 0;
static uint8_t currentScreenCol = 0;
static uint8_t lastCopied[SCREEN_HEIGHT*SCREEN_WIDTH];


//TEXT

void terminalInit()
{
  //Initialize keyboardState
  uint16_t i;

  for(i=0; i<256; i++)
  {
    keyboardState[i]=0;
  }
}

void scrolling()
{
  uint8_t i;
  uint8_t j;
  for(i=0; i<SCREEN_HEIGHT-1; i++)
  {
    for(j=0; j<SCREEN_WIDTH; j++)
    {
      screenText[i][j] = screenText[i+1][j];
    }
  }
  for(j=0; j<SCREEN_WIDTH; j++)
    screenText[i][j] = ' ';
  currentScreenRow = SCREEN_HEIGHT-1;
  currentScreenCol = 0;
}

void terminalPutChar(uint8_t ascii)
{
  if(currentScreenRow == SCREEN_HEIGHT)
  {
    scrolling();
  }
  if(ascii == '\n') //enter
  {
    currentScreenRow++;
    currentScreenCol = 0;
    return;
  }
  screenText[currentScreenRow][currentScreenCol++] = ascii;
  if(currentScreenCol == SCREEN_WIDTH)
  {
    currentScreenCol = 0;
    currentScreenRow++;
  }
}

void videoDraw(uint8_t * vbuffer)
{
  //To do: write to screen
  //clearScreen();
  setVideoBuffer(vbuffer);
  return;
}

void terminalEraseChar()
{
  if(currentScreenRow == 0)
  {
    if(currentScreenCol == 0)
      return;
    currentScreenCol--;
  }
  else if(currentScreenCol == 0)
  {
    currentScreenRow--;
    currentScreenCol=SCREEN_WIDTH-1;
  } else
  {
    currentScreenCol--;
  }
  screenText[currentScreenRow][currentScreenCol] = ' ';
  return;
}

//VIDEO

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

void clearScreen() {
  uint8_t i, j;
  for(i=0; i<SCREEN_HEIGHT; i++)
  {
    for(j=0; j<SCREEN_WIDTH; j++)
    {
        screenText[i][j]=' ';
    }
  }
  currentScreenRow=0;
  currentScreenCol=0;
}

//KEYBOARD
void terminalKeyboardUpdate(keycode_t key)
{

  keyboardState[key.code] = key.action==KBD_ACTION_PRESSED?1:0;

	if(videoModeEnabled)
		return;

  static uint8_t state = 0;

  if(!(updateState(key, &state))&& key.action == KBD_ACTION_PRESSED)
  {
    uint8_t ascii = getAscii(key, state);
    if(ascii == 8)//backspace
    {
      if(bufferIsEmpty())
        return;
      terminalEraseChar(); //borro el char de la pantalla
      eraseFromBuffer(); //borro el char de la pantalla
      updateScreen();
    }
    else if(ascii == '\n')
    {
      enterPressed=1;
      terminalPutChar(ascii);
      updateScreen(); //actualizo la pantalla
    }
    else
    {
      readChars++;
      terminalPutChar(ascii); //muestro el char en pantalla
      putChar(ascii); //agrego el char al buffer
      updateScreen(); //actualizo la pantalla
    }
  }
}

//SYSCALLS

//Devuelve la cantidad de chars leidos
uint64_t readFromBuffer(uint8_t *target, uint64_t size)
{
  uint64_t i = 0;
  while(!enterPressed && readChars<size){/*Espero*/}
  enterPressed=0;
  readChars=0;
  while(!bufferIsEmpty())
  {
    *(target+i) = getChar();
    i++;
  }
  target[i]=0;
  return i;
}

uint64_t getKeyState(uint8_t keycode)
{
    return keyboardState[keycode];
}

void writeToScreen(uint8_t *target, uint64_t size)
{
  uint64_t i=0;
  while(i<size)
  {
    terminalPutChar(*(target++));
    i++;
  }
  updateScreen();
}

void run(uint64_t moduleNumber)
{
    if(moduleNumber>=getModulesQuantity())
    {
      writeToScreen("Error! Ese modulo no existe\n", 28);
    }
    else
    {
      loadModuleToRun(moduleNumber);
      runLoadedModule();
    }
    loadModuleToRun(0); //Go back to shell
  	runLoadedModule();
}

uint8_t toggleVideoMode()
{
  return videoModeEnabled=videoModeEnabled?0:1;
}

uint64_t terminalSysCallHandler(uint64_t rax,uint64_t rbx,uint64_t rcx,uint64_t rdx,uint64_t rsi,uint64_t rdi)
{
  switch(rax)
  {
    case SYSCALL_READ:
      readFromBuffer((uint8_t*)rcx, rdx);
      break;
    case SYSCALL_WRITE:
      writeToScreen((uint8_t*)rcx, rdx);
      break;
    case SYSCALL_EXECVE:
      run(rbx);
      break; //Recibe el numero de modulo, lo copia en memoria y lo ejecuta
    case SYSCALL_EXIT:
      run(0x00);
      break;
    case SYSCALL_TOGGLEVIDEO:
      toggleVideoMode();
      break;
    case SYSCALL_CLEAR:
      clearScreen();
      break;
    case SYSCALL_VIDEODRAW:
      videoDraw((uint8_t*)rcx);
      break;
    case SYSCALL_GETKEYSTATE:
      *((uint8_t *)rbx) = getKeyState(rcx);
       break;
    default:
      return 0;//imprimo "Undefined syscall"
  }
  return 0;

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
  for(x=0; x<SCREEN_WIDTH; x++)
  {
    for(y=0; y<SCREEN_HEIGHT; y++)
    {
      selectedText[y][x]=0;
    }
  }
}


void copy()
{
  uint8_t i, j, k=0;
  for(i=0; i<SCREEN_HEIGHT; i++)
  {
    for(j=0; j<SCREEN_WIDTH; j++)
    {
      if(selectedText[i][j] == 1)
        lastCopied[k++] = screenText[i][j];
    }
  }
  lastCopied[k++]=0;
}

//lastCopied tiene asciis
void paste()
{
  uint8_t i=0;
  while(lastCopied[i] != 0)
  {
    terminalPutChar(lastCopied[i]);
    putChar(lastCopied[i++]); //agrego el char al buffer
  }
  updateScreen();
}

void terminalMouseUpdate(mouseInfo_t mouse)
{
  if(videoModeEnabled)
  {
    //Actually we do nothing
    return;
  }
  //paso los valores de posX y posY al rango de la terminal.
  mouse.posX = (uint8_t)((mouse.posX*79)/999);
  mouse.posY = (uint8_t)(24-(mouse.posY*24)/349);
  static uint8_t state = QUIET;
  switch (state) {
    case PASTE: if(!mouse.rightPressed)
                {
                  state = QUIET;
                  break;
                }
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
                if(mouse.rightPressed)
                { //paso a PASTE
                  paste();
                  state = PASTE;
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
                        selectText(pressingStartsX ,pressingStartsY, mouse.posX, mouse.posY);
                        cursorX = mouse.posX;
                        cursorY = mouse.posY;
                        state = DRAGGING;
                        break;
                      }
                      if(mouse.rightPressed)
                      { //paso a PASTE
                        paste();
                        state = PASTE;
                        break;
                      }
                      else //sigo en L_PRESSING
                        break;

  case MOVING:  if((cursorX == mouse.posX && cursorY == mouse.posY) && mouse.leftPressed)
                { // paso a L_PRESSING, inicializo pressing y selecciono
                  pressingStartsX = cursorX;
                  pressingStartsY = cursorY;
                  selectText(cursorX, cursorY, cursorX, cursorY);
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
                  selectText(cursorX, cursorY, mouse.posX, mouse.posY);
                  cursorX = mouse.posX;
                  cursorY = mouse.posY;
                  state = DRAGGING;
                  break;
                }
                if(mouse.rightPressed)
                { //paso a PASTE
                  paste();
                  state = PASTE;
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
                    selectText(cursorX, cursorY, cursorX, cursorY);
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
                      selectText(cursorX, cursorY, cursorX, cursorY);
                      state = L_PRESSING;
                      break;
                    }
                    if(mouse.rightPressed)
                    { //paso a PASTE
                      paste();
                      state = PASTE;
                      break;
                    }
                    else
                    { // sigo en DRAGGING, selecciono y actualizo cursor
                      deselectText();
                      selectText(pressingStartsX ,pressingStartsY, mouse.posX, mouse.posY);
                      cursorX = mouse.posX;
                      cursorY = mouse.posY;
                      break;
                    }
  }
  updateScreen();
}
