CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

TestEuropeanOption: EuropeanOption.o TestEuropeanOption.o
	$(CC) $(CFLAGS) -o TestEuropeanOption EuropeanOption.o TestEuropeanOption.o

TestEuropeanOption.o: EuropeanOption.hpp TestEuropeanOption.cpp
	$(CC) $(CFLAGS) -c TestEuropeanOption.cpp
	
EuropeanOpion.o: EuropeanOption.hpp EuropeanOption.cpp
	$(CC) $(CFLAGS) -c EuropeanOption.cpp
	
clean:
	rm -rf TestEuropeanOption *.o



