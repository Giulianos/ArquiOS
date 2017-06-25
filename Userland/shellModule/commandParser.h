#ifndef _COMMANDPARSER_H
#define _COMMANDPARSER_H

#include <stdint.h>

typedef struct
{
  char * cmdstr;
  int cmdlen;
  int id;
} command_t;

uint8_t parseCommand(char * cmd);

#endif
