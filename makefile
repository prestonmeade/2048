FLAGS= -Wall -std=c++11 -g -O0 -pedantic-errors


all: 2048 clean

2048: 2048.o Swipe.o
	g++ $(FLAGS) -o 2048 2048.o Swipe.o

2048.o: 2048.cpp Swipe.h
	g++ $(FLAGS) -c 2048.cpp

Swipe.o: Swipe.cpp Swipe.h
	g++ $(FLAGS) -c Swipe.cpp


clean:
	rm -f *.o
