#ifndef _VIDEO_DRIVER_DRIVER_H
#define _VIDEO_DRIVER_DRIVER_H

  #include <stdint.h>

  #define BLACK_BG 0x00
  #define BLUE_BG 0x10
  #define GREEN_BG 0x20
  #define CYAN_BG 0x30
  #define RED_BG 0x40
  #define MAGENTA_BG 0x50
  #define BROWN_BG 0x60
  #define LIGHT_GRAY_BG 0x70
  #define DARK_GRAY_BG 0x80
  #define LIGHT_BLUE_BG 0x90
  #define LIGHT_GREEN_BG 0xA0
  #define LIGHT_CYAN_BG 0xB0
  #define LIGHT_RED_BG 0xC0
  #define LIGHT_MAGENTA_BG 0xD0
  #define YELLOW_BG 0xE0
  #define WHITE_BG 0xF0

  #define BLACK_FG 0x00
  #define BLUE_FG 0x01
  #define GREEN_FG 0x02
  #define CYAN_FG 0x03
  #define RED_FG 0x04
  #define MAGENTA_FG 0x05
  #define BROWN_FG 0x06
  #define LIGHT_GRAY_FG 0x07
  #define DARK_GRAY_FG 0x08
  #define LIGHT_BLUE_FG 0x09
  #define LIGHT_GREEN_FG 0x0A
  #define LIGHT_CYAN_FG 0x0B
  #define LIGHT_RED_FG 0x0C
  #define LIGHT_MAGENTA_FG 0x0D
  #define YELLOW_FG 0x0E
  #define WHITE_FG 0x0F

  uint8_t videoPrint(char* msg, uint8_t row, uint8_t col, uint8_t attr);

#endif
