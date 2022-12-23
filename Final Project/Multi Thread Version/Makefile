CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11 -lcurl -lpthread

Main01: Main01.o EODMarketData.o Sorting_and_Sample.o ReturnCalculation.o gnuplot.o
	$(CC) $(CFLAGS) -o Main01 Main01.o EODMarketData.o Sorting_and_Sample.o ReturnCalculation.o gnuplot.o

Main01.o: gnuplot.h Sorting_and_Sample.h EODMarketData.h Main01.cpp 
	$(CC) $(CFLAGS) -c Main01.cpp
	
Sorting_and_Sample.o: Sorting_and_Sample.h Sorting_and_Sample.cpp EODMarketData.h
	$(CC) $(CFLAGS) -c Sorting_and_Sample.cpp
	
ReturnCalculation.o: ReturnCalculation.h ReturnCalculation.cpp EODMarketData.h Sorting_and_Sample.h
	$(CC) $(CFLAGS) -c ReturnCalculation.cpp

EODMarketData.o: EODMarketData.h EODMarketData.cpp
	$(CC) $(CFLAGS) -c EODMarketData.cpp
	
gnuplot.o: gnuplot.cpp gnuplot.h
	$(CC) $(CFLAGS) -c gnuplot.cpp

clean:
	rm -rf  Main01  *.o
