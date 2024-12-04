# Compiler used
CC = gcc
CXX = g++

# Compilation flags:
#  -g    Add debug information to the executable file
#  -Wall Turn on most, but not all, compiler warnings
CFLAGS  = -g -Wall
LINKING = -lglut -lGL -lGLU
TARGET = *

all:
	$(CXX) $(CFLAGS) -o trabalhocg $(TARGET).cpp $(LINKING)

clean:
	$(RM) $(TARGET)