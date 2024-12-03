# Compilador a ser utilizado
CC = gcc
CXX = g++

# Flags para o compilador:
#  -g    Adiciona informações de debug ao executável
#  -Wall Habilita todas as warnings
CFLAGS  = -g -Wall
LINKING = -lglut -lGL -lGLU
TARGET = *

all:
	$(CXX) $(CFLAGS) -o trabalhocg $(TARGET).cpp $(LINKING)

clean:
	$(RM) $(TARGET)