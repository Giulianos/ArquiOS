global keyboardHandler
extern keyboardHandlerC
extern keyboardHandlerEnd

%include "./asm/macros.m"

keyboardHandler:
  pushaq
  call keyboardHandlerC
  mov al, 0x20
  out 0x20, al
  popaq
  iretq
