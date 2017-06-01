#include <handlers.h>
#include <hardwareCom.h>
#include <naiveConsole.h>

void keyboardHandlerC()
{
  inputB(0x60);
  ncPrint("Keyboard Interrupt Handled!");
  outputB(0x20, 0x20);
  return;
}
