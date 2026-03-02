CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

OBJECTS = main.o board.o queens.o
TARGET = main

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp board.h
	$(CXX) $(CXXFLAGS) -c main.cpp

board.o: board.cpp board.h
	$(CXX) $(CXXFLAGS) -c board.cpp

queens.o: queens.cpp queens.h
	$(CXX) $(CXXFLAGS) -c queens.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)