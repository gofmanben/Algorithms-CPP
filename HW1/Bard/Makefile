CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

OBJECTS = main.o wordlist.o linkedlist.o
TARGET = main

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

main.o: main.cpp linkedlist.h
	$(CXX) $(CXXFLAGS) -c main.cpp

wordlist.o: wordlist.cpp wordlist.h
	$(CXX) -g $(CXXFLAGS) -c wordlist.cpp

linkedlist.o: linkedlist.cpp linkedlist.h 
	$(CXX) -g $(CXXFLAGS) -c linkedlist.cpp

clean:
	rm -f $(OBJECTS) $(TARGET)