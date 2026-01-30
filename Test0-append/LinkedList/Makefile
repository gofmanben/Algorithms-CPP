CXX = g++
CXXFLAGS = -Wall

OBJECTS = linkedlist.o main.o

main: $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o main linkedlist.o main.o

linkedlist.o: linkedlist.cpp linkedlist.h
	$(CXX) -g $(CXXFLAGS) -c linkedlist.cpp
	
main.o: linkedlist.cpp linkedlist.h main.cpp
	$(CXX) -g $(CXXFLAGS) -c main.cpp

clean: 
	rm -f *.o
	rm -f main