/*
Partes de este codigo fueron escritas
tomando informacion de:
  - http://wiki.osdev.org/PS/2_Mouse
  - http://wiki.osdev.org/Mouse_Input
  - http://forum.osdev.org/viewtopic.php?t=10247
*/

#include <hardwareCom.h>
#include "driver.h"

#define MOUSE_WAIT_READ   0x00
#define MOUSE_WAIT_WRITE  0x01
#define MOUSE_WAIT_TIMEOUT 10000 //Cantidad de iteraciones antes de abortar espera

static uint16_t mousePositionX = 0;
static uint16_t mousePositionY = 0;

static void mouseWait(uint8_t bit);
static uint8_t mouseRead();
static void mouseWrite(uint8_t data);

//Comandos del mouse: http://wiki.osdev.org/Mouse_Input#Useful_Mouse_Command_Set

void mouseDriver()
{

}

void initMouse()
{
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
  mouseRead();  //Espero el ACK

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
