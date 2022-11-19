CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

HW11: Main04.o GmtrAsianCall.o EurCall.o MCModel.o PathDepOption.o
	$(CC) $(CFLAGS) -o HW11 Main04.o GmtrAsianCall.o EurCall.o MCModel.o PathDepOption.o

Main04.o: Main04.cpp GmtrAsianCall.h PathDepOption.h
	$(CC) $(CFLAGS) -c Main04.cpp

GmtrAsianCall.o: EurCall.h PathDepOption.h GmtrAsianCall.h GmtrAsianCall.cpp
	$(CC) $(CFLAGS) -c GmtrAsianCall.cpp
	
PathDepOption.o: EurCall.h PathDepOption.h PathDepOption.cpp
	$(CC) $(CFLAGS) -c PathDepOption.cpp
	
EurCall.o: EurCall.h EurCall.cpp
	$(CC) $(CFLAGS) -c EurCall.cpp
	
MCModel.o: MCModel.h MCModel.cpp
	$(CC) $(CFLAGS) -c MCModel.cpp
	
clean:
	rm -rf  HW11 *.o



