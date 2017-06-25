#include <stdint.h>
/*
uint64_t * PDAddr = (uint64_t *)0x10000;

void mapUserspace(uint8_t * physicalAddr)
{
  //Estoy mapeando la entrada 5 de la PD (12MB) a physicalAddr
  uint64_t aux = PDAddr[5] & 0xFFF0000000000FFF; //Clean current address
  PDAddr[5] = aux & ((uint64_t)physicalAddr&0xFFFFFFFFFF000);
  aux = PDAddr[6] & 0xFFF0000000000FFF;
  PDAddr[6] = aux & ((uint64_t)physicalAddr&0xFFFFFFFFFF000);
}
*/
