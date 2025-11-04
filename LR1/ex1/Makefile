# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = ex1_lr1
TEST_TARGET = test_ex1_lr1

# Исходные файлы
MAIN_SRCS = ex1_lr1.c ex1_lr1_func.c
TEST_SRCS = test_ex1_lr1.c ex1_lr1_func.c

# Сборка основной программы
$(TARGET): $(MAIN_SRCS)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_SRCS)

# Сборка тестовой программы
$(TEST_TARGET): $(TEST_SRCS)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRCS)

# Основные цели
all: $(TARGET) $(TEST_TARGET)

test: $(TEST_TARGET)
	@echo "========================================"
	@echo "Running Unit Tests for ex1_lr1"
	@echo "========================================"
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

# Индивидуальные тесты для каждого флага
test-h: $(TARGET)
	@echo "=== Testing Flag -h (Multiples) ==="
	@echo "10 -h" | ./$(TARGET)

test-p: $(TARGET)
	@echo "=== Testing Flag -p (Prime Check) ==="
	@echo "7 -p" | ./$(TARGET)

test-s: $(TARGET)
	@echo "=== Testing Flag -s (Hexadecimal) ==="
	@echo "255 -s" | ./$(TARGET)

test-e: $(TARGET)
	@echo "=== Testing Flag -e (Exponent Table) ==="
	@echo "5 -e" | ./$(TARGET)

test-a: $(TARGET)
	@echo "=== Testing Flag -a (Sum) ==="
	@echo "10 -a" | ./$(TARGET)

test-f: $(TARGET)
	@echo "=== Testing Flag -f (Factorial) ==="
	@echo "5 -f" | ./$(TARGET)

# Тесты всех флагов
test-all-flags: $(TARGET)
	@echo "=== Testing All Flags ==="
	@echo "Testing -h:" && echo "10 -h" | ./$(TARGET) && echo ""
	@echo "Testing -p:" && echo "7 -p" | ./$(TARGET) && echo ""
	@echo "Testing -s:" && echo "255 -s" | ./$(TARGET) && echo ""
	@echo "Testing -e:" && echo "5 -e" | ./$(TARGET) && echo ""
	@echo "Testing -a:" && echo "10 -a" | ./$(TARGET) && echo ""
	@echo "Testing -f:" && echo "5 -f" | ./$(TARGET) && echo ""

# Тесты ошибок (ожидаем ошибки)
test-errors: $(TARGET)
	@echo "=== Testing Error Handling ==="
	@echo "Testing invalid flag (expected to fail):"
	-@echo "10 -x" | ./$(TARGET)
	@echo ""
	@echo "Testing non-positive number (expected to fail):"
	-@echo "0 -h" | ./$(TARGET)
	@echo ""
	@echo "Testing invalid format (expected to fail):"
	-@echo "abc -h" | ./$(TARGET)

# Проверка компиляции с разными флагами
check-compilation:
	@echo "=== Checking compilation with different flags ==="
	$(CC) -Wall -Werror -Wextra -Wpedantic -o $(TARGET) $(MAIN_SRCS) && echo " Basic flags: OK"
	$(CC) -Wall -Werror -Wextra -Wpedantic -fsanitize=address -o $(TARGET)_sanitize $(MAIN_SRCS) && echo " With sanitize: OK"
	$(CC) -Wall -Werror -Wextra -Wpedantic -O2 -o $(TARGET)_optimized $(MAIN_SRCS) && echo " With optimization: OK"

# Быстрая проверка
quick-test: $(TEST_TARGET)
	@echo "=== Quick Test ==="
	./$(TEST_TARGET)

# Демонстрация всех возможностей
demo: $(TARGET)
	@echo "=== Demonstration of All Features ==="
	@echo "1. Multiples of 7:" && echo "7 -h" | ./$(TARGET) && echo ""
	@echo "2. Check if 17 is prime:" && echo "17 -p" | ./$(TARGET) && echo ""
	@echo "3. Hexadecimal of 255:" && echo "255 -s" | ./$(TARGET) && echo ""
	@echo "4. Exponent table up to 3:" && echo "3 -e" | ./$(TARGET) && echo ""
	@echo "5. Sum of numbers 1-20:" && echo "20 -a" | ./$(TARGET) && echo ""
	@echo "6. Factorial of 8:" && echo "8 -f" | ./$(TARGET) && echo ""

.PHONY: all test clean test-h test-p test-s test-e test-a test-f test-all-flags test-errors check-compilation quick-test demo