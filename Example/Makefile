## Run ./config.sh
## Run command: LD_LIBRARY_PATH = /../AutoDiff/build/lib
## Run command: export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
## g++ -L/home/morrisreeves/Documents/coding/cs107/cs107-FinalProject/AutoDiff/build/lib/ -Wall -o demo demo.cpp -lAutoDiff


all: example.o
	g++ -L/../AutoDiff/build/lib/ -Wall -o example example.cpp -lAutoDiff
	g++ example.o -o example

example.o: 
	LD_LIBRARY_PATH = /../AutoDiff/build/lib
	export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
	g++ -c example.cpp

clean:
	rm *.o