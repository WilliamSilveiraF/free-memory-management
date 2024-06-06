# Makefile for Memory Management System

# Compiler and Linker
CXX = g++

# Flags for compiler
CXXFLAGS = -Wall -std=c++11 -I./Bitmap -I./BitmapMemoryManager -I./LinkedListMemoryManager -I./MemoryManager -I./MemoryBlock

# Build executable
TARGET = MemoryManagerApp

# Source files
SOURCES = main.cpp \
          Bitmap/Bitmap.cpp \
          BitmapMemoryManager/BitmapMemoryManager.cpp \
          LinkedListMemoryManager/LinkedListMemoryManager.cpp \
          MemoryBlock/MemoryBlock.cpp \
          MemoryManager/MemoryManager.cpp

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

# Dependency rules for objects
Bitmap/Bitmap.o: Bitmap/Bitmap.cpp Bitmap/Bitmap.h
BitmapMemoryManager/BitmapMemoryManager.o: BitmapMemoryManager/BitmapMemoryManager.cpp BitmapMemoryManager/BitmapMemoryManager.h Bitmap/Bitmap.h
LinkedListMemoryManager/LinkedListMemoryManager.o: LinkedListMemoryManager/LinkedListMemoryManager.cpp LinkedListMemoryManager/LinkedListMemoryManager.h MemoryBlock/MemoryBlock.h
MemoryBlock/MemoryBlock.o: MemoryBlock/MemoryBlock.cpp MemoryBlock/MemoryBlock.h
MemoryManager/MemoryManager.o: MemoryManager/MemoryManager.cpp MemoryManager/MemoryManager.h BitmapMemoryManager/BitmapMemoryManager.h LinkedListMemoryManager/LinkedListMemoryManager.h
main.o: main.cpp MemoryManager/MemoryManager.h
