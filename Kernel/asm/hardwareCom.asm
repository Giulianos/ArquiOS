global inputB
global outputB
global systemCall

;recibe el registro a leer en el registro edi
inputB:
  push rbp
  mov rbp, rsp
  sub rsp, 0x04
  mov [rbp-0x04], edi
  mov dx, word[rbp-0x04]
  in al, dx
  mov rsp, rbp
  pop rbp
  ret

;recibe el registro a escribir (en edi) y el valor a escribir(en esi)
outputB:
  push rbp
  mov rbp, rsp
  sub rsp, 0x08                         ;guardo espacio para guardar ambos valores recibidos
  mov [rbp-0x04], edi                   ;registro
  mov [rbp-0x08], esi                   ;dato
  mov dx, word[rbp-0x04]                ;registro
  mov al, byte[rbp-0x08]                ;dato
  out dx, al
  mov rsp, rbp
  pop rbp
  ret

; uint64_t systemCall(eax, ebx, ecx, edx, esi, edi)
systemCall:
  push rbp
  mov rbp, rsp
  mov rax, rdi
  mov rbx, rsi
  mov rcx, rdx
  mov rdx, r10
  mov rsi, r8
  mov rdi, r9
  int 0x80
  mov rsp, rbp
  pop rbp
  ret
