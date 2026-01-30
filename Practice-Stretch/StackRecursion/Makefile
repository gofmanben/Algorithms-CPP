CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = node.o list.o stackrecursion.o

stackrecursion: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o $@ $^

node.o: node.cpp node.h
	$(CXX) -g $(CXXFLAGS) -c node.cpp

list.o: list.cpp list.h node.h
	$(CXX) -g $(CXXFLAGS) -c list.cpp

clean: 
	rm -f *.o stackrecursion