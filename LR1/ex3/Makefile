# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = ex3_lr1
TEST_TARGET = test_ex3_lr1

# Исходные файлы
MAIN_SRCS = ex3_lr1.c ex3_lr1_func.c
TEST_SRCS = test_ex3_lr1.c ex3_lr1_func.c

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
	@echo "Running Unit Tests"
	@echo "========================================"
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

# Индивидуальные тесты
test-quadratic: $(TARGET)
	@echo "=== Testing Quadratic Equations ==="
	./$(TARGET) -q 0.0001 1 -5 6
	@echo ""
	./$(TARGET) -q 0.0001 1 2 1

test-multiplicity: $(TARGET)
	@echo "=== Testing Multiplicity ==="
	./$(TARGET) -m 15 5
	@echo ""
	./$(TARGET) -m 4 16
	@echo ""
	./$(TARGET) -m 7 3

test-triangle: $(TARGET)
	@echo "=== Testing Triangle Validation ==="
	./$(TARGET) -t 0.0001 3 4 5
	@echo ""
	./$(TARGET) -t 0.0001 5 12 13
	@echo ""
	./$(TARGET) -t 0.0001 2 3 4

# Проверка компиляции
check-compilation:
	@echo "=== Checking compilation ==="
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_SRCS) -lm && echo " Compilation: OK"

.PHONY: all test clean test-quadratic test-multiplicity test-triangle check-compilation