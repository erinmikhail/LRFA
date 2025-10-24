CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
SANITIZE_FLAGS = -fsanitize=address
LIBS = -lm

SOURCES = main.c src.c test_srcMain.c
HEADERS = include.h
TARGET = program

$(TARGET): $(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -o $(TARGET) $(SOURCES) $(LIBS)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: test clean