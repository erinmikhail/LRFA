CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -std=c99
SANITIZE_FLAGS = -fsanitize=address
LIBS = -lm

# Основная программа
MAIN_SRCS = ex1_main.c ex1_func.c
MAIN_OBJS = $(MAIN_SRCS:.c=.o)
MAIN_TARGET = finite_representation

# Тестовая программа
TEST_SRCS = test_ex1.c ex1_func.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_TARGET = test_finite_representation

# Основная цель
all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_OBJS)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -o $(MAIN_TARGET) $(MAIN_OBJS) $(LIBS)

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -o $(TEST_TARGET) $(TEST_OBJS) $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(SANITIZE_FLAGS) -c $< -o $@

# Теперь test сразу запускает тесты
test: $(TEST_TARGET)
	./$(TEST_TARGET)

run: $(MAIN_TARGET)
	./$(MAIN_TARGET)

clean:
	rm -f $(MAIN_OBJS) $(TEST_OBJS) $(MAIN_TARGET) $(TEST_TARGET)

.PHONY: all test run clean