TARGET = s21_grep
CC = gcc
FLAGS = -Wall -Wextra -std=c11

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(FLAGS) $(TARGET).o -o $(TARGET)

$(TARGET).o: $(TARGET).c
	$(CC) $(FLAGS) -c $(TARGET).c