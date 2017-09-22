include Makefile.inc

all: sampleCodeModule shellModule helpModule fortuneModule clearModule

shellModule:
		cd shellModule; make

helpModule:
		cd helpModule; make

clearModule:
		cd clearModule; make

fortuneModule:
		cd fortuneModule; make

sampleCodeModule:
	cd SampleCodeModule; make

clean:
	cd SampleCodeModule; make clean
	cd helpModule; make clean
	cd shellModule; make clean
	rm -rf *.bin


.PHONY: shellModule sampleCodeModule helpModule all clean fortuneModule clearModule
