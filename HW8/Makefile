CC = g++
CFLAGS = -Wall -ggdb3 -std=c++11

main: main.o NonlinearSolver02.o
	$(CC) $(CFLAGS) -o main main.o NonlinearSolver02.o

main.o: main.cpp NonlinearSolver02.h Bond.h
	$(CC) $(CFLAGS) -c main.cpp NonlinearSolver02.cpp
	
NonlinearSolver02.o: NonlinearSolver02.h NonlinearSolver02.cpp Bond.h
	$(CC) $(CFLAGS) -c NonlinearSolver02.cpp	


clean:
	rm -rf main *.o



