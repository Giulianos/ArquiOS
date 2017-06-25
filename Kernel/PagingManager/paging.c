#include <stdint.h>

uint64_t * PDAddr = (uint64_t *)0x10000;

void mapUserspace(uint8_t * physicalAddr)
{
  //Me fijo de no querer pisar el espacio del kernel.
  if((uint64_t)physicalAddr>0x1400000)
  {
    //Estoy mapeando la entrada 9 de la PD (20MB) a physicalAddr
    uint64_t aux = PDAddr[9] & 0xFFF0000000000FFF; //Clean current address
    PDAddr[9] = aux & ((uint64_t)physicalAddr&0xFFFFFFFFFF000); //Set physicalAddr
  }
}
