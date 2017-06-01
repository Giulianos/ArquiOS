global keyboardHandler
extern keyboardHandlerC
global mouseHandler
extern mouseHandlerC
global dummyHandler

%include "./asm/macros.m"

keyboardHandler:
  pushaq
  cld
  call keyboardHandlerC
  mov al, 0x20
  out 0x20, al ;ACK al master pic
  popaq
  iretq

mouseHandler:
  pushaq
  cld
  call mouseHandlerC
  mov al, 0x20
  out 0xA0, al ;ACK al master pic
  out 0x20, al ;ACK al slave pic
  popaq
  iretq
