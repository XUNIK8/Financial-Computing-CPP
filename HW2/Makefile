CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main: main.o BinomialTreeModel.o Option02.o
	$(CC) $(CFLAGS) -o main main.o BinomialTreeModel.o Option02.o

main.o: main.cpp BinomialTreeModel.h Option02.h
	$(CC) $(CFLAGS) -c main.cpp

Option02.o: BinomialTreeModel.h Option02.h Option02.cpp
	$(CC) $(CFLAGS) -c Option02.cpp
	
BinomialTreeModel.o: BinomialTreeModel.h BinomialTreeModel.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel.cpp
	
clean:
	rm -rf OptionPricer01 *.o



