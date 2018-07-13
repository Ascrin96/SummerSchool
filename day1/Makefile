CC=g++
CFLAGS= -c -Wall -std=c++11
CVFLAGS=`pkg-config --libs --cflags opencv`


all: testOpenCV

testOpenCV: testOpenCV.o
	$(CC) testOpenCV.o -o testOpenCV

testOpenCV.o: testOpenCV.cpp
	$(CC) $(CFLAGS) $(CVFLAGS) testOpenCV.cpp

clean:
	rm -rf *.o hello