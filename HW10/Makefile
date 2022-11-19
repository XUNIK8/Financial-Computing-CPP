CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

HW10: Main03.o MCModel.o PathDepOption.o
	$(CC) $(CFLAGS) -o HW10 Main03.o MCModel.o PathDepOption.o

Main03.o: Main03.cpp MCModel.h PathDepOption.h
	$(CC) $(CFLAGS) -c Main03.cpp

PathDepOption.o: MCModel.h PathDepOption.h PathDepOption.cpp
	$(CC) $(CFLAGS) -c PathDepOption.cpp
	
MCModel.o: MCModel.h MCModel.cpp
	$(CC) $(CFLAGS) -c MCModel.cpp
	
clean:
	rm -rf  HW10 *.o



