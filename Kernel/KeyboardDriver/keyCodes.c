#include <stdint.h>
#include "driver.h"

keycode_t scancodeToKeycode(uint8_t fbyte, uint8_t sbyte)
{
  keycode_t retKeycode;
  if(fbyte!=0xE0)
  {
    if(fbyte>=0x81)
    {
      retKeycode.action = KBD_ACTION_RELEASED;
      fbyte-=0x80;
    } else
    {
      retKeycode.action = KBD_ACTION_PRESSED;
    }
    switch(fbyte)
    {
      case 0x01: retKeycode.code = 0x00; break;
      case 0x3B: retKeycode.code = 0x01; break;
      case 0x3C: retKeycode.code = 0x02; break;
      case 0x3D: retKeycode.code = 0x03; break;
      case 0x3E: retKeycode.code = 0x04; break;
      case 0x3F: retKeycode.code = 0x05; break;
      case 0x40: retKeycode.code = 0x06; break;
      case 0x41: retKeycode.code = 0x07; break;
      case 0x42: retKeycode.code = 0x08; break;
      case 0x43: retKeycode.code = 0x09; break;
      case 0x44: retKeycode.code = 0x0A; break;
      case 0x58: retKeycode.code = 0x0C; break;
      case 0x56: retKeycode.code = 0x10; break;
      case 0x02: retKeycode.code = 0x11; break;
      case 0x03: retKeycode.code = 0x12; break;
      case 0x04: retKeycode.code = 0x13; break;
      case 0x05: retKeycode.code = 0x14; break;
      case 0x06: retKeycode.code = 0x15; break;
      case 0x07: retKeycode.code = 0x16; break;
      case 0x08: retKeycode.code = 0x17; break;
      case 0x09: retKeycode.code = 0x18; break;
      case 0x0A: retKeycode.code = 0x19; break;
      case 0x0B: retKeycode.code = 0x1A; break;
      case 0x0C: retKeycode.code = 0x1B; break;
      case 0x0D: retKeycode.code = 0x1C; break;
      case 0x0E: retKeycode.code = 0x1D; break;
      case 0x0F: retKeycode.code = 0x21; break;
      case 0x10: retKeycode.code = 0x22; break;
      case 0x11: retKeycode.code = 0x23; break;
      case 0x12: retKeycode.code = 0x24; break;
      case 0x13: retKeycode.code = 0x25; break;
      case 0x14: retKeycode.code = 0x26; break;
      case 0x15: retKeycode.code = 0x27; break;
      case 0x16: retKeycode.code = 0x28; break;
      case 0x17: retKeycode.code = 0x29; break;
      case 0x18: retKeycode.code = 0x2A; break;
      case 0x19: retKeycode.code = 0x2B; break;
      case 0x1A: retKeycode.code = 0x2C; break;
      case 0x1B: retKeycode.code = 0x2D; break;
      case 0x2B: retKeycode.code = 0x2E; break;
      case 0x3A: retKeycode.code = 0x32; break;
      case 0x1E: retKeycode.code = 0x33; break;
      case 0x1F: retKeycode.code = 0x34; break;
      case 0x20: retKeycode.code = 0x35; break;
      case 0x21: retKeycode.code = 0x36; break;
      case 0x22: retKeycode.code = 0x37; break;
      case 0x23: retKeycode.code = 0x38; break;
      case 0x24: retKeycode.code = 0x39; break;
      case 0x25: retKeycode.code = 0x3A; break;
      case 0x26: retKeycode.code = 0x3B; break;
      case 0x27: retKeycode.code = 0x3C; break;
      case 0x28: retKeycode.code = 0x3D; break;
      case 0x1C: retKeycode.code = 0x3E; break;
      case 0x2A: retKeycode.code = 0x3F; break;
      case 0x2C: retKeycode.code = 0x40; break;
      case 0x2D: retKeycode.code = 0x41; break;
      case 0x2E: retKeycode.code = 0x42; break;
      case 0x2F: retKeycode.code = 0x43; break;
      case 0x30: retKeycode.code = 0x44; break;
      case 0x31: retKeycode.code = 0x45; break;
      case 0x32: retKeycode.code = 0x46; break;
      case 0x33: retKeycode.code = 0x47; break;
      case 0x34: retKeycode.code = 0x48; break;
      case 0x35: retKeycode.code = 0x49; break;
      case 0x36: retKeycode.code = 0x4A; break;
      case 0x1D: retKeycode.code = 0x4C; break;
      case 0x38: retKeycode.code = 0x4E; break;
      case 0x39: retKeycode.code = 0x4F; break;
      default:   retKeycode.code=0x00;
    }
  } else
  {
    if(sbyte>=0x81)
    {
      retKeycode.action = KBD_ACTION_RELEASED;
      sbyte-=0x80;
    } else
    {
      retKeycode.action = KBD_ACTION_PRESSED;
    }
    switch(sbyte)
    {
      case 0x37: retKeycode.code = 0x0D; break;
      case 0x52: retKeycode.code = 0x1E; break;
      case 0x47: retKeycode.code = 0x1F; break;
      case 0x49: retKeycode.code = 0x20; break;
      case 0x53: retKeycode.code = 0x2F; break;
      case 0x4F: retKeycode.code = 0x30; break;
      case 0x51: retKeycode.code = 0x31; break;
      case 0x5B: retKeycode.code = 0x4D; break;
      case 0x38: retKeycode.code = 0x50; break;
      case 0x5C: retKeycode.code = 0x51; break;
      case 0x1D: retKeycode.code = 0x53; break;
      case 0x48: retKeycode.code = 0x4B; break;
      case 0x4B: retKeycode.code = 0x54; break;
      case 0x50: retKeycode.code = 0x55; break;
      case 0x4D: retKeycode.code = 0x56; break;
    }
  }
  return retKeycode;
}
