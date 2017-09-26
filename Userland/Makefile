include Makefile.inc

all: sampleCodeModule shellModule helpModule fortuneModule clearModule snakeModule

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

snakeModule:
	cd snakeModule; make

clean:
	cd SampleCodeModule; make clean
	cd helpModule; make clean
	cd shellModule; make clean
	cd snakeModule; make clean
	rm -rf *.bin


.PHONY: shellModule sampleCodeModule helpModule all clean fortuneModule clearModule snakeModule
