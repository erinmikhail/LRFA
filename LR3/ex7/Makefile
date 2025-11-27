CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -I. -fsanitize=address
TARGET = interpreter

SOURCES = src/main.c src/interpreter.c src/logger.c
HEADERS = include/interpreter.h include/logger.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -Iinclude

sanitize: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES) -Iinclude

test: test_interpreter
	./test_interpreter

test_interpreter: tests/test_interpreter.c src/interpreter.c src/logger.c
	$(CC) $(CFLAGS) -o test_interpreter tests/test_interpreter.c src/interpreter.c src/logger.c -Iinclude

clean:
	rm -f $(TARGET) test_interpreter trace.log

run: $(TARGET)
	./$(TARGET)

.PHONY: all test clean run sanitize