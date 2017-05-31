#ifndef _HARDWARE_COM_H
#define _HARDWARE_COM_H
#include <stdint.h>

  void outputB(uint16_t reg, uint8_t data);
  uint8_t inputB(uint16_t reg);
#endif
