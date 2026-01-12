CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

OBJECTS = main.o triangle.o
TARGET = main

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp triangle.h
	$(CXX) $(CXXFLAGS) -c main.cpp

triangle.o: triangle.cpp triangle.h
	$(CXX) $(CXXFLAGS) -c triangle.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)