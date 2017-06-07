#ifndef _TERMINAL_H
#define _TERMINAL_H
  #include <stdint.h>
  #include "../MouseDriver/driver.h"
  #include "../KeyboardDriver/driver.h"

  void selectText(uint8_t initialX, uint8_t initialY, uint8_t finalX, uint8_t finalY);
  void deselectText();
  void copy();
  void terminalMouseUpdate(mouseInfo_t mouse);
  void terminalKeyboardUpdate(keycode_t key);
#endif
