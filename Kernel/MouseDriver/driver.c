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

static void mouseWait(uint8_t bit);
static uint8_t mouseRead();
static void mouseWrite(uint8_t data);

void initMouse()
{
  //Habilito aux mouse dev.
  mouseWait(MOUSE_WAIT_WRITE); //Espero a poder escribir
  outputB(0x64, 0xA8);
  //Habilito el aux port
  mouseWait(MOUSE_WAIT_WRITE);
  outputB(0x64, 0x20); //Pido el compaq status byte
  mouseWait(MOUSE_WAIT_READ); //Espero los datos
  uint8_t compaq_status = inputB(0x60); //Leo el compaq status byte
  compaq_status |= 0x02; //Set bit 1 del compaq status byte
  //compaq_status &= 0xDF; //Clear bit 5 del compaq status byte
  mouseWait(MOUSE_WAIT_WRITE);
  outputB(0x64, 0x60); //Indico que voy a enviar el nuevo compaq status byte
  mouseWait(MOUSE_WAIT_WRITE); //Espero a poder escribir
  outputB(0x60, compaq_status);

  mouseWrite(0xF6);
  mouseRead();  //Espero el ACK

  mouseWrite(0xF4);
  mouseRead();  //Espero el ACK

}

static void mouseWrite(uint8_t data)
{
  mouseWait(MOUSE_WAIT_WRITE);
  outputB(0x64, 0xD4);
  mouseWait(MOUSE_WAIT_WRITE);
  outputB(0x60, data);
}

static uint8_t mouseRead()
{
  mouseWait(MOUSE_WAIT_READ);
  return inputB(0x60);
}

/* Espera al bit de lectura:0 | escritura:1 */
static void mouseWait(uint8_t bit)
{
  if(bit>1)
    return;
  if(!bit)
  {
    while(!(inputB(0x64)&0x01)){}
    return;
  }
  while(inputB(0x64)&0x02){}
}
