CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main: main.o BinomialTreeModel.o Option01.o
	$(CC) $(CFLAGS) -o main main.o BinomialTreeModel.o Option01.o

main.o: main.cpp BinomialTreeModel.h Option01.h
	$(CC) $(CFLAGS) -c main.cpp

Option01.o: BinomialTreeModel.h Option01.h Option01.cpp
	$(CC) $(CFLAGS) -c Option01.cpp
	
BinomialTreeModel.o: BinomialTreeModel.h BinomialTreeModel.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel.cpp
	
clean:
	rm -rf OptionPricer01 *.o



