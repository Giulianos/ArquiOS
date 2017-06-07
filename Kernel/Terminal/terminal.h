#ifndef _TERMINAL_H
#define _TERMINAL_H
  #include <stdint.h>
  #include "../MouseDriver/driver.h"
  #include "../KeyboardDriver/driver.h"
  //posibles estados del teclado:
  #define SHIFT_PRESSED 0x01
  #define CAPS_LOCK_ENABLED 0x02
  #define CONTROL_PRESSED 0x04
  #define ALT_PRESSED 0x08
  #define ALT_GR_PRESSED 0x10
  #define RIGHT_SHIFT_PRESSED 0x20

  void selectText(uint8_t initialX, uint8_t initialY, uint8_t finalX, uint8_t finalY);
  void deselectText();
  void copy();
  void terminalMouseUpdate(mouseInfo_t mouse);
  void terminalKeyboardUpdate(keycode_t key);

#endif
