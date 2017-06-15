#include <stdint.h>
#include <interrupts.h>
#include <hardwareCom.h>
#include <handlers.h>
#include <lib.h>
#include "MouseDriver/driver.h"

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
  cli();
  //0110 1111 0111 1001
  writePICMask(0x6F79); //Habilito solo las interrupciones de teclado, mouse y las spurious (7 y 15)
  initMouse();
  setIDTEntry(0x21, (uint64_t)keyboardHandler); //Handler de la interrupcion de teclado
  setIDTEntry(0x2C, (uint64_t)mouseHandler); //Handler de la interrupcion de mouse
  setIDTEntry(0x80, (uint64_t)systemCallHandler);
  setIDTEntry(0x27, (uint64_t)spuriousInt7Handler);
  setIDTEntry(0x2F, (uint64_t)spuriousInt15Handler);
  sti();//Habilito las interrupciones
}
