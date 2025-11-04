CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = ex8_program
TEST_TARGET = test_ex8_lr1

MAIN_SRC = ex8_lr1.c
FUNC_SRC = ex8_lr1_func.c
TEST_SRC = test_ex8_lr1.c
HEADER = ex8_lr1.h

all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(FUNC_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_SRC) $(FUNC_SRC)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(FUNC_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(FUNC_SRC)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

rebuild: clean all

run: $(TARGET)
	./$(TARGET)

check: test

.PHONY: all test clean rebuild run check