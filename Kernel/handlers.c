#include <handlers.h>
#include <hardwareCom.h>
#include <naiveConsole.h>
#include "KeyboardDriver/driver.h"
#include "MouseDriver/driver.h"

void keyboardHandlerC()
{
  keyboardDriver();
}

void mouseHandlerC()
{
  mouseDriver();
}
