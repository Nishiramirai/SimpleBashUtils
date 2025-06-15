CC = gcc
FLAGS = -Wall -Werror -Wextra -std=c11
BIN_PATH = bin
OBJ_PATH = obj
TARGET = cat

.PHONY: all clean

all: cat

cat: cat.o
	$(CC) $(FLAGS) $(OBJ_PATH)/cat.o -o $(BIN_PATH)/cat

cat.o: cat.c cat.h
	$(CC) $(FLAGS) -c cat.c -o $(OBJ_PATH)/cat.o

clean:
	rm $(BIN_PATH)/*
	rm $(OBJ_PATH)/*