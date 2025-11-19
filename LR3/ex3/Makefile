CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -I. -fsanitize=address
TARGET = resident_manager

SOURCES = main.c list.c liver.c command.c
HEADERS = list.h liver.h command.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

sanitize: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: test_program
	./test_program

test_program: test.c list.c liver.c command.c
	$(CC) $(CFLAGS) -o test_program test.c list.c liver.c command.c

clean:
	rm -f $(TARGET) test_program *.log

run: $(TARGET)
	./$(TARGET)

.PHONY: all test clean run sanitize