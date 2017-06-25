include Makefile.inc

SAMPLE_DATA=0001-sampleDataModule.bin

all: sampleCodeModule sampleDataModule helpModule

sampleCodeModule:
	cd SampleCodeModule; make

helpModule:
		cd helpModule; make

sampleDataModule:
	printf "This is sample data." >> $(SAMPLE_DATA) && dd if=/dev/zero bs=1 count=1 >> $(SAMPLE_DATA)

clean:
	cd SampleCodeModule; make clean
	cd helpModule; make clean
	rm -rf *.bin


.PHONY: sampleCodeModule helpModule all clean
