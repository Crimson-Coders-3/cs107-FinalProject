## Example showing how to link the .so shared library file, located at AutoDiff/build/lib:
## In the root directory where you downloaded this project, run ./config.sh
## In the directory at the same level of this Makefile, type command in the terminal: make
## Now run ./example

AD_INCLUDE = ${CURDIR}/../AutoDiff/install/include
AD_LIB_PATH = ${CURDIR}/../AutoDiff/install/lib
AD_LIB_NAME = AutoDiff

all: example.cpp
	g++ -Wall -std=c++11 -o example -I${AD_INCLUDE} -L${AD_LIB_PATH} example.cpp -Wl,-rpath=${AD_LIB_PATH} -l${AD_LIB_NAME}

clean:
	rm *.o

