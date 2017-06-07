#ifndef _MOUSEDRIVER_DRIVER_H
#define _MOUSEDRIVER_DRIVER_H

  #include <stdint.h>

  typedef struct
  {
    uint16_t posX;
    uint16_t posY;
    uint8_t leftPressed;
    uint8_t rightPressed;
  } mouseInfo_t;

  void initMouse();
  void mouseDriver();

#endif
