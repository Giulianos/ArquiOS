#ifndef _KEY_MAPPING
#define _KEY_MAPPING

  #include "terminal.h"
  #include <stdint.h>
  uint8_t getAsciiUS(keycode_t key, uint8_t state);
  uint8_t updateStateUS(keycode_t key, uint8_t *state);
  uint8_t getAsciiLA(keycode_t key, uint8_t state);
  uint8_t updateStateLA(keycode_t key, uint8_t *state);

  #define getAscii(k, s) getAsciiLA(k, s)
  #define updateState(k, s) updateStateLA(k, s)
  
#endif
