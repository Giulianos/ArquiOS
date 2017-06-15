include ../Makefile.inc

MODULE=../0000-sampleCodeModule.bin
SOURCES_C=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
OBJECTS_C=$(SOURCES_C:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS_C) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o $(MODULE) $(OBJECTS_C) $(OBJECTS_ASM)

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf asm/*.o *.o *.bin

.PHONY: all clean print
