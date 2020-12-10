## Example showing how to link the .so shared library file, located at AutoDiff/build/lib:
## In the root directory where you downloaded this project, run ./config.sh
## In the directory at the same level of this Makefile, type command in the terminal: make
## Now run ./example

all: example.cpp
	g++ -Wall -o example -L../AutoDiff/build/lib -I../AutoDiff/build/include example.cpp -Wl,-rpath=${CURDIR}/../AutoDiff/build/lib -lAutoDiff

clean:
	rm *.o
