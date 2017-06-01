#include <handlers.h>
#include <hardwareCom.h>
#include <naiveConsole.h>

void keyboardHandlerC()
{
  inputB(0x60);
  ncPrint("Keyboard Interrupt Handled!");
}

void mouseHandlerC()
{
  inputB(0x60); //Si no leo datos el mouse no sigue interrumpiendo
  ncPrint("Mouse Interrupt Handled!");
}
