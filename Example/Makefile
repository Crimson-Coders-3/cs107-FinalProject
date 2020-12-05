## This example aims to tell you how to link the .so shared library file, which locates at AutoDiff/build/lib and is created after you built the whole project
##
## In the root directory where you downloaded this project, run ./config.sh
## In this Makefile, replace /home/wenlin/github/cs107-FinalProject/AutoDiff/build/lib with the directory of this project in your computer (no need to remove AutoDiff/build/lib). Note we need absolute path for this step and the following step.
## In this Makefile, replace /home/wenlin/github/cs107-FinalProject/AutoDiff/build/lib with the directory of this project in your computer (same here, don't remove AutoDiff/build/lib)
## In the direcotry at the same level of this Makefile, tyoe command in the terminal: make
## Now run ./example

all: example.cpp
	LD_LIBRARY_PATH=/home/wenlin/github/cs107-FinalProject/AutoDiff/build/lib
	export LD_LIBRARY_PATH=/usr/local/lib:$$LD_LIBRARY_PATH
	g++ -L/home/wenlin/github/cs107-FinalProject/AutoDiff/build/lib/ -Wall -o example example.cpp -lAutoDiff

clean:
	rm *.o
