CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

OBJECTS = main.o graph.o node.o
TARGET = main

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp graph.h node.h
	$(CXX) $(CXXFLAGS) -c main.cpp

graph.o: graph.cpp graph.h node.h
	$(CXX) $(CXXFLAGS) -c graph.cpp

node.o: node.cpp node.h
	$(CXX) $(CXXFLAGS) -c node.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)