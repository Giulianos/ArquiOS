#ifndef _KEYBOARD_DRIVER_H
#define _KEYBOARD_DRIVER_H

  #define KBD_ACTION_PRESSED 0
  #define KBD_ACTION_RELEASED 1

  typedef struct
  {
    uint8_t code;
    uint8_t action;
  } keycode_t;

  void keyboardDriver();
  keycode_t scancodeToKeycode(uint8_t fbyte, uint8_t sbyte);

#endif
