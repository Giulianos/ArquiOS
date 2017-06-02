#include <handlers.h>
#include <hardwareCom.h>
#include <naiveConsole.h>
#include "KeyboardDriver/driver.h"
void keyboardHandlerC()
{
  keyboardDriver();
}

void mouseHandlerC()
{
  inputB(0x60); //Si no leo datos el mouse no sigue interrumpiendo
  ncPrint("Mouse Interrupt Handled!");
}
