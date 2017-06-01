#include <stdint.h>
#include <interrupts.h>
#include <hardwareCom.h>
#include <handlers.h>
#include <lib.h>

static IDTEntry_t* IDT = (IDTEntry_t*)0x0;

void setIDTEntry(uint16_t entry, uint64_t offset)
{
  IDT[entry].offset_1 = (uint16_t)(offset&0xffff);
  IDT[entry].offset_2 = (uint16_t)((offset>>16)&0xffff);
  IDT[entry].offset_3 = (uint32_t)((offset>>32)&0xffffffff);
  IDT[entry].selector = 0x08;
  IDT[entry].ist = 0x00;
  IDT[entry].type_attr = 0x8e;
  IDT[entry].zero = 0x00;
}

void configureInterrupts()
{
  writePICMask(0xFFFD); //Habilito solo las interrupciones de teclado
  setIDTEntry(0x21, (uint64_t)keyboardHandler);
  sti();//Habilito las interrupciones
}
