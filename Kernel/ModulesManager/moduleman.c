#include <lib.h>
#include "modules.h"

static module_t modules[256];

extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

/*
*      +--------------------+
*      |       KERNEL       |
*      | MODULES/KERNEL BSS | 0x0000000 - endOfKernel
*      |....................|
*      +--------------------+
*      |   COPIED MODULES   | 0x0A00000 - 0x13FFFFF
*      +--------------------+
*      |    RUNTIME PAGE    | 0x1400000 - 0x15FFFFF
*      +--------------------+
*
*/

static uint8_t * expandedModulesArea = (uint8_t *)0xA00000; //10MB
static uint8_t * runtimePage = (uint8_t *)0x1400000;

/* Loads modules  */
static void loadModulesToKernel()
{
  //Read how many modules were packed
  uint32_t modulesQuantity = *((uint32_t *)(&endOfKernelBinary));
  uint8_t * currentModule = (uint8_t *)(&endOfKernelBinary+sizeof(uint32_t));
  uint8_t * moduleDest = expandedModulesArea;
  uint8_t i;
  for(i=0; i<modulesQuantity; i++)
  {
    loadModuleToKernel(&currentModule, &moduleDest, i);
  }
}

static void loadModuleToKernel(uint8_t ** module, uint8_t ** targetModuleAddress, uint8_t moduleNum)
{
	uint32_t moduleSize = readUint32(module);
  modules[moduleNum].id = moduleNum;
  modules[moduleNum].dir = *targetModuleAddress;
  modules[moduleNum].size = moduleSize;
	memcpy(targetModuleAddress, *module, moduleSize);
	*module += moduleSize;
  *targetModuleAddress += moduleSize;
}

static void loadModuleToRun(uint8_t id)
{
  memcpy(runtimePage, modules[id].dir, modules[id].size);
}

static uint32_t readUint32(uint8_t ** address)
{
	uint32_t result = *(uint32_t*)(*address);
	*address += sizeof(uint32_t);
	return result;
}
