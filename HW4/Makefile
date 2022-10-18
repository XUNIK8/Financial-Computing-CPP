CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main: main.o BinomialTreeModel02.o Option05.o
	$(CC) $(CFLAGS) -o main main.o BinomialTreeModel02.o Option05.o

main.o: main.cpp BinomialTreeModel02.h Option05.h
	$(CC) $(CFLAGS) -c main.cpp

Option05.o: BinomialTreeModel02.h Option05.h Option05.cpp
	$(CC) $(CFLAGS) -c Option05.cpp
	
BinomialTreeModel02.o: BinomialTreeModel02.h BinomialTreeModel02.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel02.cpp
	
clean:
	rm -rf main *.o



