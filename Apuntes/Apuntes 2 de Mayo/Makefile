CXX = g++
CXXFLAGS = -std=c++11 -g3 -Wall -lm
MKDIR = mkdir -p

LIBS = -lm -lpq

directorios:
	$(MKDIR) build dist

db.o: directorios db.c
	$(CXX) $(CXXFLAGS) -c db.c -o build/db.o

main.o: directorios main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o build/main.o

all: clean main.o db.o
	$(CXX) $(CXXFLAGS) -o dist/simulador-sec build/main.o build/db.o $(LIBS)
	rm -fr build

clean:
	rm -fr *.o a.out core simulador-sec dist build *.csv

.DEFAULT_GOAL := all
