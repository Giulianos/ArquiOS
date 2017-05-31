#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include <stdint.h>

  /*Estructuras*/
  #pragma pack(push)
  #pragma pack(1)

  typedef struct {
     uint16_t offset_1; // offset bits 0..15
     uint16_t selector; // a code segment selector in GDT or LDT
     uint8_t ist;       // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
     uint8_t type_attr; // type and attributes
     uint16_t offset_2; // offset bits 16..31
     uint32_t offset_3; // offset bits 32..63
     uint32_t zero;     // reserved
  } IDTEntry_t;

  #pragma pack(pop)


  /*Funciones*/
  void configureInterrupts();

#endif
