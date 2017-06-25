#ifndef _MODULESMAN_MODULES_H
#define _MODULESMAN_MODULES_H

typedef struct
{
  char * name;
  uint8_t id;
  uint8_t * dir;
  uint32_t size;
} module_t;

static void loadModulesToKernel();
static void loadModuleToRun(uint8_t id);

#endif
