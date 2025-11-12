CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -I -fsanitize=address
TARGET = program

all: $(TARGET)

$(TARGET): main.c vector.c vector.h
	$(CC) $(CFLAGS) -o $(TARGET) main.c vector.c

sanitize: main.c vector.c vector.h
	$(CC) $(CFLAGS) -o $(TARGET) main.c vector.c

test: test.c vector.c vector.h
	$(CC) $(CFLAGS) -o test_program test.c vector.c
	./test_program

clean:
	rm -f $(TARGET) test_program *.log

run: $(TARGET)
	./$(TARGET)

.PHONY: all test clean run sanitize