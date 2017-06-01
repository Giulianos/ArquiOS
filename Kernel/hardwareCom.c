#include <hardwareCom.h>

#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD 0xA0
#define PIC_SLAVE_DATA 0xA1

void writePICMask(uint16_t mask)
{
  outputB(PIC_MASTER_DATA, (uint8_t)(mask&0xFF));
  outputB(PIC_SLAVE_DATA, (uint8_t)((mask>>8)&0xFF));
}
