CXX = g++
CXXFLAGS = -Wall -std=c++11 -O2

OBJECTS = bst.o main.o

main: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o main bst.o main.o

bst.o: bst.cpp bst.h
	$(CXX) -g $(CXXFLAGS) -c bst.cpp
	
main.o: main.cpp bst.h
	$(CXX) -g $(CXXFLAGS) -c main.cpp

clean: 
	rm -f *.o
	rm -f main