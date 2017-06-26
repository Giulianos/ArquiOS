#include "stdlib/string.h"
#include "commandParser.h"

static command_t commands[] =
{
	{"help", 4, 1},
	{"sample", 6, 2},
	{"fortune", 7, 3},
	{"clear", 5, 4}
};

uint8_t parseCommand(char * cmd)
{
	for(int i=0; i<(sizeof(commands)/sizeof(command_t)); i++)
	{
		if(!strncmp(commands[i].cmdstr, cmd, commands[i].cmdlen))
			return commands[i].id;
	}
	return 100;
}
