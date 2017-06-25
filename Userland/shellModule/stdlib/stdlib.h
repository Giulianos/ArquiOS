#ifndef _STDLIB_H
#define _STDLIB_H

#define execve(id) systemCall(0x0B, id, 0, 0, 0, 0)

#endif
