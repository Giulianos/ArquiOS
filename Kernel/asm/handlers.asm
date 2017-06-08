global keyboardHandler
extern keyboardHandlerC
global mouseHandler
extern mouseHandlerC
global dummyHandler

%include "./asm/macros.m"

keyboardHandler:
  cli
  pushaq
  cld
  call keyboardHandlerC
  mov al, 0x20
  out 0x20, al ;ACK al master pic
  popaq
  sti
  iretq

mouseHandler:
  cli
  pushaq
  cld
  call mouseHandlerC
  mov al, 0x20
  out 0xA0, al ;ACK al master pic
  out 0x20, al ;ACK al slave pic
  popaq
  sti
  iretq
