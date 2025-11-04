# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = ex6_lr1
TEST_TARGET = test_ex6_lr1

# Исходные файлы
MAIN_SRCS = ex6_lr1.c ex6_lr1_func.c
TEST_SRCS = test_ex6_lr1.c ex6_lr1_func.c

# Сборка основной программы
$(TARGET): $(MAIN_SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_SRCS) -lm

# Сборка тестовой программы
$(TEST_TARGET): $(TEST_SRCS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRCS) -lm

# Основные цели
all: $(TARGET) $(TEST_TARGET)

test: $(TEST_TARGET)
	@echo "========================================"
	@echo "Running Unit Tests for ex6_lr1"
	@echo "========================================"
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

# Проверка отдельных файлов
check-main:
	@echo "=== Checking main file ==="
	@cat -n ex6_lr1.c

check-headers:
	@echo "=== Checking headers ==="
	@cat -n ex6_lr1.h

check-func:
	@echo "=== Checking functions ==="
	@cat -n ex6_lr1_func.c

.PHONY: all test clean check-main check-headers check-func