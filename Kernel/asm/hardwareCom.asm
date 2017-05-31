global inputB
global outputB

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
