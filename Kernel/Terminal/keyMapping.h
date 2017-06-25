#ifndef _KEY_MAPPING
#define _KEY_MAPPING

  #include "terminal.h"
  #include <stdint.h>
  uint8_t getAscii(keycode_t key, uint8_t state);
  uint8_t updateState(keycode_t key, uint8_t *state);

#endif
