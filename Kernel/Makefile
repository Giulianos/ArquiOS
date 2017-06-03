include Makefile.inc

KERNEL=kernel.bin
KEYBOARD_DRIVER=$(wildcard KeyboardDriver/*.c)
MOUSE_DRIVER=$(wildcard MouseDriver/*.c)
VIDEO_DRIVER=$(wildcard VideoDriver/*.c)
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_KEYBOARD_DRIVER=$(KEYBOARD_DRIVER:.c=.o)
OBJECTS_MOUSE_DRIVER=$(MOUSE_DRIVER:.c=.o)
OBJECTS_VIDEO_DRIVER=$(VIDEO_DRIVER:.c=.o)
LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(STATICLIBS) $(OBJECTS_ASM) $(OBJECTS_KEYBOARD_DRIVER) $(OBJECTS_MOUSE_DRIVER) $(OBJECTS_VIDEO_DRIVER)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_ASM) $(STATICLIBS) $(OBJECTS_KEYBOARD_DRIVER) $(OBJECTS_MOUSE_DRIVER) $(OBJECTS_VIDEO_DRIVER)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin

.PHONY: all clean
