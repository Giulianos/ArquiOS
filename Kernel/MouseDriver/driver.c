/*
Partes de este codigo fueron escritas
tomando informacion de:
  - http://wiki.osdev.org/PS/2_Mouse
  - http://wiki.osdev.org/Mouse_Input
  - http://forum.osdev.org/viewtopic.php?t=10247
*/

#include <hardwareCom.h>
#include "driver.h"
#include <naiveConsole.h>

#define MOUSE_WAIT_READ   0x00
#define MOUSE_WAIT_WRITE  0x01
#define MOUSE_WAIT_TIMEOUT 10000 //Cantidad de iteraciones antes de abortar espera

static int mousePositionX = 0;
static int mousePositionY = 0;

static uint8_t didOccurFirsrInterrupt = 0;

static void mouseWait(uint8_t bit);
static uint8_t mouseRead();
static void mouseWrite(uint8_t data);

//Comandos del mouse: http://wiki.osdev.org/Mouse_Input#Useful_Mouse_Command_Set

void mouseDriver()
{

  if(!didOccurFirsrInterrupt)
  {
    didOccurFirsrInterrupt=1;
    return;
  }

  static uint8_t phase = 0;
  static uint8_t flags;
  static int movX=0;
  static int movY=0;

  switch(phase)
  {
    case 0: flags=inputB(0x60);
            phase++;
            break;
    case 1: movX=inputB(0x60);
            if(flags&0x10)
              movX |= 0xFFFFFF00;
            phase++;
            break;
    case 2: movY=inputB(0x60);
            phase=0;if((flags&0x80) || (flags&0x40))
              return; //Descarto este paquete que solo tiene info de overflow (inservible)
            if(flags&0x20)
              movY |= 0xFFFFFF00;
            mousePositionX+=movX;
            mousePositionY+=movY;
            ncClear();
            ncPrintBin(flags);
            ncPrintChar(';');
            ncPrintSignedDec(movX);
            ncPrintChar(';');
            ncPrintSignedDec(movY);
            ncNewline();
            break;
  }

  /*
  if(phase == 0)
  {
    flags=inputB(0x60);
    phase++;
    return;
  } else if(phase == 1)
  {
    movX=inputB(0x60);
    phase++;
    mousePositionX += movX*(flags&0x10)?(-1):1;
    return;
  } else if(phase == 3)
  {
    movY=inputB(0x60);
    phase++;
    mousePositionY += movY*(flags&0x20)?(-1):1;
    return;
    ncClear();
    ncPrintDec(mousePositionX);
    ncPrintChar(';');
    ncPrintDec(mousePositionY);
    ncNewline();
    phase=0;
  }*/
}

void initMouse()
{
  ncPrint("Initializing MouseDriver!");
  ncNewline();
  //Habilito aux mouse dev. (opcional, pero mejor tenerlo)
  mouseWait(MOUSE_WAIT_WRITE); //Espero a poder escribir
  outputB(0x64, 0xA8);
  //Habilito el aux port
  mouseWait(MOUSE_WAIT_WRITE);
  outputB(0x64, 0x20); //Pido el compaq status byte
  uint8_t compaq_status = mouseRead(); //Leo el compaq status byte
  compaq_status |= 0x02; //Set bit 1 del compaq status byte
  mouseWait(MOUSE_WAIT_WRITE);
  outputB(0x64, 0x60); //Indico que voy a enviar el nuevo compaq status byte
  mouseWait(MOUSE_WAIT_WRITE); //Espero a poder escribir
  outputB(0x60, compaq_status);

  /* Default conf:
  Disables streaming, sets the packetrate to 100 per second, and resolution to 4 pixels per mm. */
  mouseWrite(0xF6);
  mouseRead();  //Espero el ACK

  /* Activo el envio automatico de paquetes */
  mouseWrite(0xF4);
  mouseRead(); //Espero ACK

  /* Leo y mustro el MouseID (debugging) */
  mouseWrite(0xF2);
  mouseRead(); //Espero el ACK
  uint8_t mouseID= mouseRead(); //Leo el mouseID
  ncPrintHex(mouseID);

  ncPrint("End of Initialization!");
  ncNewline();

}

static void mouseWrite(uint8_t data)
{
  //Espero a poder escribir
  mouseWait(MOUSE_WAIT_WRITE);
  //Le digo al mouse que le voy a enviar un comando
  outputB(0x64, 0xD4);
  //Espero a poder escribir
  mouseWait(MOUSE_WAIT_WRITE);
  //Le envio el comando
  outputB(0x60, data);
}

static uint8_t mouseRead()
{
  //Espero a poder leer
  mouseWait(MOUSE_WAIT_READ);
  //Leo del mouse
  return inputB(0x60);
}

/* Espera al bit de lectura:0 | escritura:1 */
static void mouseWait(uint8_t bit)
{
  uint16_t timeout = MOUSE_WAIT_TIMEOUT;
  if(bit>1)
    return;
  if(!bit)
  {
    while(!(inputB(0x64)&0x01) || timeout){ timeout--; }
    return;
  }
  while(inputB(0x64)&0x02 || timeout){ timeout--; }
}