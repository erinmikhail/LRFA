CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -I./include -fsanitize=address
TARGET = post_system

SOURCES = src/main.c src/post_system.c src/heap.c
HEADERS = include/post_system.h include/heap.h

all: $(TARGET)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

sanitize: $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $(TARGET) $(SOURCES)

test: test_program
	@echo "=========================================="
	@echo "          RUNNING UNIT TESTS"
	@echo "=========================================="
	./test_program

test_program: tests/test.c src/post_system.c src/heap.c
	$(CC) $(CFLAGS) -I./include -o test_program tests/test.c src/post_system.c src/heap.c

clean:
	rm -f $(TARGET) test_program *.log *.txt

run: $(TARGET)
	./$(TARGET) mappings.txt system.log

.PHONY: all test clean run sanitize