CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main: main.o BinomialTreeModel02.o Option08.o BlackScholes.o
	$(CC) $(CFLAGS) -o main main.o BinomialTreeModel02.o Option08.o BlackScholes.o

main.o: main.cpp BinomialTreeModel02.h Option08.h BinLattice02.h BlackScholes.h
	$(CC) $(CFLAGS) -c main.cpp
	
Option08.o: BinLattice02.h BinomialTreeModel02.h Option08.h Option08.cpp
	$(CC) $(CFLAGS) -c Option08.cpp
	
BlackScholes.o: BlackScholes.h BlackScholes.cpp 
	$(CC) $(CFLAGS) -c BlackScholes.cpp	
	
BinomialTreeModel02.o: BinomialTreeModel02.h BinomialTreeModel02.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel02.cpp

	
clean:
	rm -rf main *.o



