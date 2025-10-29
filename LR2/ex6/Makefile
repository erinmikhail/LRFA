CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99 -I.
TARGET = student_manager


all: $(TARGET)

$(TARGET): main.c src.c include.h
	$(CC) $(CFLAGS) -o $(TARGET) main.c src.c


sanitize: main.c src.c include.h
	$(CC) $(CFLAGS) -fsanitize=address -o $(TARGET) main.c src.c


test: test.c src.c include.h
	$(CC) $(CFLAGS) -fsanitize=address -o test_program test.c src.c
	./test_program


clean:
	rm -f $(TARGET) test_program *.log

run: $(TARGET)
	./$(TARGET) test_data.txt trace.log

.PHONY: all test clean run sanitize