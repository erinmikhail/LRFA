CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = text_formatter
SRC = main.c src.c test.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) test_input.txt test_expected.txt test_output.txt

.PHONY: all test clean