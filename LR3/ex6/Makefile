CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -I. -fsanitize=address
TARGET = br

SOURCES = main.c brackets.c
HEADERS = brackets.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

sanitize: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: test_program
	./test_program

test_program: test.c brackets.c
	$(CC) $(CFLAGS) -o test_program test.c brackets.c

clean:
	rm -f $(TARGET) test_program

run: $(TARGET)
	./$(TARGET)

.PHONY: all test clean run sanitize