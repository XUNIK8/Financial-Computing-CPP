CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main: main.o BinomialTreeModel02.o Option05.o DoubDigitOpt.o StrangleOpt.o ButterflyOpt.o
	$(CC) $(CFLAGS) -o main main.o BinomialTreeModel02.o Option05.o DoubDigitOpt.o StrangleOpt.o ButterflyOpt.o

main.o: main.cpp BinomialTreeModel02.h Option05.h DoubDigitOpt.h StrangleOpt.h ButterflyOpt.h
	$(CC) $(CFLAGS) -c main.cpp
	
DoubDigitOpt.o: DoubDigitOpt.h DoubDigitOpt.cpp Option05.h
	$(CC) $(CFLAGS) -c DoubDigitOpt.cpp
	
StrangleOpt.o: StrangleOpt.h StrangleOpt.cpp Option05.h
	$(CC) $(CFLAGS) -c StrangleOpt.cpp

ButterflyOpt.o: ButterflyOpt.h ButterflyOpt.cpp Option05.h
	$(CC) $(CFLAGS) -c ButterflyOpt.cpp
	
Option05.o: BinomialTreeModel02.h Option05.h Option05.cpp
	$(CC) $(CFLAGS) -c Option05.cpp
	
BinomialTreeModel02.o: BinomialTreeModel02.h BinomialTreeModel02.cpp
	$(CC) $(CFLAGS) -c BinomialTreeModel02.cpp
	
clean:
	rm -rf main *.o



