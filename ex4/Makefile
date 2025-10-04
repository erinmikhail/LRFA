# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = ex4_lr1
TEST_TARGET = test_ex4_lr1

# Исходные файлы
MAIN_SRCS = ex4_lr1.c ex4_lr1_func.c
TEST_SRCS = test_ex4_lr1.c ex4_lr1_func.c

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
	@echo "Running Unit Tests for ex4_lr1"
	@echo "========================================"
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) test_input.txt

# Индивидуальные тесты
test-e: $(TARGET)
	@echo "=== Testing e calculation ==="
	@echo "0.0001" | ./$(TARGET) | head -20

test-pi: $(TARGET)
	@echo "=== Testing π calculation ==="
	@echo "0.001" | ./$(TARGET) | grep -A 5 "π"

test-ln2: $(TARGET)
	@echo "=== Testing ln(2) calculation ==="
	@echo "0.0001" | ./$(TARGET) | grep -A 5 "ln(2)"

test-sqrt2: $(TARGET)
	@echo "=== Testing √2 calculation ==="
	@echo "0.0000001" | ./$(TARGET) | grep -A 5 "√2"

test-gamma: $(TARGET)
	@echo "=== Testing γ calculation ==="
	@echo "0.0001" | ./$(TARGET) | grep -A 10 "γ"

# Тесты с разной точностью
test-precision: $(TARGET)
	@echo "=== Testing different precisions ==="
	@echo "Precision 0.001:" && echo "0.001" | ./$(TARGET) | grep "e (число Эйлера)" -A 3 | head -4
	@echo ""
	@echo "Precision 0.000001:" && echo "0.000001" | ./$(TARGET) | grep "e (число Эйлера)" -A 3 | head -4

# Проверка компиляции
check-compilation:
	@echo "=== Checking compilation ==="
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_SRCS) -lm && echo "✅ Compilation: OK"

# Быстрая проверка
quick-test: $(TEST_TARGET)
	@echo "=== Quick Test ==="
	./$(TEST_TARGET)

.PHONY: all test clean test-e test-pi test-ln2 test-sqrt2 test-gamma test-precision check-compilation quick-test