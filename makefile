# Makefile for Memory Management System

# Compiler and Linker
CXX = g++

# Flags for compiler
CXXFLAGS = -Wall -std=c++11

# Build executable
TARGET = MemoryManagerApp

# Source files
SOURCES = main.cpp MemoryBlock.cpp Bitmap.cpp BitmapMemoryManager.cpp LinkedListMemoryManager.cpp MemoryManager.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Rule to link the program
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

# Rule to compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean workspace
clean:
	rm -f $(OBJECTS) $(TARGET)

# Rule for making everything clean
distclean: clean
	rm -f $(TARGET)
