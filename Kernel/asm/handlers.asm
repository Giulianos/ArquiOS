global keyboardHandler
extern keyboardHandlerC
global mouseHandler
extern mouseHandlerC
global systemCallHandler
extern terminalSysCallHandler
global spuriousInt7Handler
global spuriousInt15Handler
extern inputB
extern outputB
extern ncPrintHex

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

systemCallHandler:
  pushaq
  cld
  mov r9, rdi
  mov r8, rsi
  mov r10, rdx
  mov rdx, rcx
  mov rcx, r10
  mov rdi, rax
  mov rsi, rbx
  call terminalSysCallHandler ; terminalSysCallHandler(rax,rbx,rcx,rdx,rsi,rdi)
  popaq
  iretq

spuriousInt7Handler:
  cli
  pushaq
  cld
  mov edi, 0x20
  mov esi, 0x0B
  call outputB ;recibe el registro a escribir (en edi) y el valor a escribir(en esi)
  mov edi, 0x20
  call inputB ;recibe el registro a leer en el registro edi
  and al, 0x80
  cmp al, 0x80
  je .salir ;Si era una spurious interrupt, no hago nada
  mov al, 0x20 ;Si no era, como no me importa IRQ7 simplemente mando
  out 0x20, al ;ACK al master pic
.salir
  popaq
  sti
  iretq

spuriousInt15Handler:
  cli
  pushaq
  cld
  mov edi, 0xA0
  mov esi, 0x0B
  call outputB ;recibe el registro a escribir (en edi) y el valor a escribir(en esi)
  mov edi, 0xA0
  call inputB ;recibe el registro a leer en el registro edi
  and al, 0x80
  cmp al, 0x80
  je .salir ;Si era una spurious interrupt, no hago nada
  mov al, 0x20 ;Si no era, como no me importa IRQ15 simplemente mando
  out 0xA0, al ;ACK al slave pic
.salir
  mov al, 0x20 ;Siempre mando
  out 0x20, al ;ACK al master pic
  popaq
  sti
  iretq
