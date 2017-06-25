include Makefile.inc

all: sampleCodeModule shellModule helpModule

shellModule:
		cd shellModule; make

helpModule:
		cd helpModule; make

sampleCodeModule:
	cd SampleCodeModule; make

clean:
	cd SampleCodeModule; make clean
	cd helpModule; make clean
	cd shellModule; make clean
	rm -rf *.bin


.PHONY: shellModule sampleCodeModule helpModule all clean
