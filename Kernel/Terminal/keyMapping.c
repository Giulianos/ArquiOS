#include "keyMapping.h"
uint8_t getAscii(keycode_t key, uint8_t state)
{
  if(((state & SHIFT_PRESSED) || (state & RIGHT_SHIFT_PRESSED)) && (state & CAPS_LOCK_ENABLED))
  switch (key.code)
  {
    //case 1D://back
    //case 3E://enter
    case 0x11: return '!';
    case 0x12: return '@';
    case 0x13: return '#';
    case 0x14: return '$';
    case 0x15: return '%';
    case 0x16: return '^';
    case 0x17: return '&';
    case 0x18: return '*';
    case 0x19: return '('; //1
    case 0x1A: return ')';//0

    case 0x22: return 'q';
    case 0x23: return 'w';
    case 0x24: return 'e';
    case 0x25: return 'r';
    case 0x26: return 't';
    case 0x27: return 'y';
    case 0x28: return 'u';
    case 0x29: return 'i';
    case 0x2A: return 'o';
    case 0x2B: return 'p';

    case 0x33: return 'a';
    case 0x34: return 's';
    case 0x35: return 'd';
    case 0x36: return 'f';
    case 0x37: return 'g';
    case 0x38: return 'h';
    case 0x39: return 'j';
    case 0x3A: return 'k';
    case 0x3B: return 'l';
    case 0x3C: return 164;//enie (mayus 165)

    case 0x40: return 'z';
    case 0x41: return 'x';
    case 0x42: return 'c';
    case 0x43: return 'v';
    case 0x44: return 'b';
    case 0x45: return 'n';
    case 0x46: return 'm';
    case 0x47: return '<';
    case 0x48: return '>';
    case 0x49: return '?';

    case 0x4F: return ' ';

  }
  else if(state & SHIFT_PRESSED || state & RIGHT_SHIFT_PRESSED)
  {
    switch (key.code)
    {
      //case 1D://back
      //case 3E://enter
      case 0x11: return '!';
      case 0x12: return '@';
      case 0x13: return '#';
      case 0x14: return '$';
      case 0x15: return '%';
      case 0x16: return '^';
      case 0x17: return '&';
      case 0x18: return '*';
      case 0x19: return '('; //1
      case 0x1A: return ')';//0
      case 0x1B: return '_';//0

      case 0x22: return 'Q';
      case 0x23: return 'W';
      case 0x24: return 'E';
      case 0x25: return 'R';
      case 0x26: return 'T';
      case 0x27: return 'Y';
      case 0x28: return 'U';
      case 0x29: return 'I';
      case 0x2A: return 'O';
      case 0x2B: return 'P';

      case 0x33: return 'A';
      case 0x34: return 'S';
      case 0x35: return 'D';
      case 0x36: return 'F';
      case 0x37: return 'G';
      case 0x38: return 'H';
      case 0x39: return 'J';
      case 0x3A: return 'K';
      case 0x3B: return 'L';
      case 0x3C: return 165;//enie

      case 0x40: return 'Z';
      case 0x41: return 'X';
      case 0x42: return 'C';
      case 0x43: return 'V';
      case 0x44: return 'B';
      case 0x45: return 'N';
      case 0x46: return 'M';
      case 0x47: return '<';
      case 0x48: return '>';
      case 0x49: return '?';

      case 0x4F: return ' ';

    }
  }
  else if(state & CAPS_LOCK_ENABLED)
  {
    switch (key.code)
    {
      //case 1D://back
      //case 3E://enter
      case 0x11: return '1';
      case 0x12: return '2';
      case 0x13: return '3';
      case 0x14: return '4';
      case 0x15: return '5';
      case 0x16: return '6';
      case 0x17: return '7';
      case 0x18: return '8';
      case 0x19: return '9'; //1
      case 0x1A: return '0';//0

      case 0x22: return 'Q';
      case 0x23: return 'W';
      case 0x24: return 'E';
      case 0x25: return 'R';
      case 0x26: return 'T';
      case 0x27: return 'Y';
      case 0x28: return 'U';
      case 0x29: return 'I';
      case 0x2A: return 'O';
      case 0x2B: return 'P';

      case 0x33: return 'A';
      case 0x34: return 'S';
      case 0x35: return 'D';
      case 0x36: return 'F';
      case 0x37: return 'G';
      case 0x38: return 'H';
      case 0x39: return 'J';
      case 0x3A: return 'K';
      case 0x3B: return 'L';
      case 0x3C: return 165;//enie

      case 0x40: return 'Z';
      case 0x41: return 'X';
      case 0x42: return 'C';
      case 0x43: return 'V';
      case 0x44: return 'B';
      case 0x45: return 'N';
      case 0x46: return 'M';
      case 0x47: return ',';
      case 0x48: return '.';
      case 0x49: return '/';

      case 0x4F: return ' ';

    }
  }
  else
  {
    switch (key.code)
    {
      //case 1D://back
      //case 3E://enter
      case 0x11: return '1';
      case 0x12: return '2';
      case 0x13: return '3';
      case 0x14: return '4';
      case 0x15: return '5';
      case 0x16: return '6';
      case 0x17: return '7';
      case 0x18: return '8';
      case 0x19: return '9'; //1
      case 0x1A: return '0';//0

      case 0x22: return 'q';
      case 0x23: return 'w';
      case 0x24: return 'e';
      case 0x25: return 'r';
      case 0x26: return 't';
      case 0x27: return 'y';
      case 0x28: return 'u';
      case 0x29: return 'i';
      case 0x2A: return 'o';
      case 0x2B: return 'p';

      case 0x33: return 'a';
      case 0x34: return 's';
      case 0x35: return 'd';
      case 0x36: return 'f';
      case 0x37: return 'g';
      case 0x38: return 'h';
      case 0x39: return 'j';
      case 0x3A: return 'k';
      case 0x3B: return 'l';
      case 0x3C: return 164;//enie (mayus 165)

      case 0x40: return 'z';
      case 0x41: return 'x';
      case 0x42: return 'c';
      case 0x43: return 'v';
      case 0x44: return 'b';
      case 0x45: return 'n';
      case 0x46: return 'm';
      case 0x47: return ',';
      case 0x48: return '.';
      case 0x49: return '/';

      case 0x4F: return ' ';

    }
  }

}

//returns either key is Modifier or not
uint8_t updateState(keycode_t key, uint8_t *state)
{
  //shift
  if(key.code == 0x3F)
  {
    if(key.action == KBD_ACTION_PRESSED)
      *state = *state | SHIFT_PRESSED;
    else
      *state = *state & !SHIFT_PRESSED;
    return 1;
  }
  //right shift
  if(key.code == 0x4A)
  {
    if(key.action == KBD_ACTION_PRESSED)
      *state = *state | RIGHT_SHIFT_PRESSED;
    else
      *state = *state & !RIGHT_SHIFT_PRESSED;
    return 1;
  }
  //capsLock
  if(key.code == 0x32)
  {
    if(key.action == KBD_ACTION_PRESSED)
    {
      if(*state & CAPS_LOCK_ENABLED)
        *state = *state & !CAPS_LOCK_ENABLED;
      else
        *state = *state | CAPS_LOCK_ENABLED;
    }
    return 1;
  }
  //alt
  if(key.code == 0x4E)
  {
    if(key.action == KBD_ACTION_PRESSED)
      *state = *state | ALT_PRESSED;
    else
      *state = *state & !ALT_PRESSED;
    return 1;
  }
  //control
  if(key.code == 0x4C)
  {
    if(key.action == KBD_ACTION_PRESSED)
      *state = *state | CONTROL_PRESSED;
    else
      *state = *state & !CONTROL_PRESSED;
    return 1;
  }
  //alt gr
  if(key.code == 0x50)
  {
    if(key.action == KBD_ACTION_PRESSED)
      *state = *state | ALT_GR_PRESSED;
    else
      *state = *state & !ALT_GR_PRESSED;
    return 1;
  }
  return 0;
}
