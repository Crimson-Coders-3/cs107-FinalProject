all: example.cpp
	g++ -Wall -o example -L../AutoDiff/build/lib -I../AutoDiff/build/include example.cpp -Wl,-rpath=${CURDIR}/../AutoDiff/build/lib -lAutoDiff
clean:
	rm *.o
