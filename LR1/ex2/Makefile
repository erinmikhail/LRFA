# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = ex2_lr1
TEST_TARGET = test_ex2_lr1

# Исходные файлы
MAIN_SRCS = ex2_lr1.c ex2_lr1_func.c
TEST_SRCS = test_ex2_lr1.c ex2_lr1_func.c

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
	@echo "Running Unit Tests for ex2_lr1"
	@echo "========================================"
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) test_input.txt

# Индивидуальные тесты
test-primes: $(TARGET)
	@echo "=== Testing Prime Numbers ==="
	@echo "Test input: 5 numbers"
	@echo "5"
	@echo "1"
	@echo "5" 
	@echo "10"
	@echo "20"
	@echo "50" | ./$(TARGET)

test-small: $(TARGET)
	@echo "=== Testing Small Input ==="
	@echo "3"
	@echo "1"
	@echo "2"
	@echo "3" | ./$(TARGET)

test-single: $(TARGET)
	@echo "=== Testing Single Prime ==="
	@echo "1"
	@echo "1" | ./$(TARGET)

# Тесты ошибок (ожидаем ошибки)
test-errors: $(TARGET)
	@echo "=== Testing Error Handling ==="
	@echo "Testing invalid input (expected to fail):"
	-@echo "0" | ./$(TARGET)
	@echo ""
	-@echo "-5" | ./$(TARGET)
	@echo ""
	-@echo "2" | ./$(TARGET)
	-@echo "1" | ./$(TARGET)
	-@echo "-1" | ./$(TARGET)

# Проверка компиляции с разными флагами
check-compilation:
	@echo "=== Checking compilation with different flags ==="
	$(CC) -Wall -Werror -Wextra -Wpedantic -o $(TARGET) $(MAIN_SRCS) && echo " Basic flags: OK"
	$(CC) -Wall -Werror -Wextra -Wpedantic -fsanitize=address -o $(TARGET)_sanitize $(MAIN_SRCS) && echo " With sanitize: OK"
	$(CC) -Wall -Werror -Wextra -Wpedantic -O2 -o $(TARGET)_optimized $(MAIN_SRCS) && echo " With optimization: OK"

# Быстрая проверка простых чисел
quick-test: $(TEST_TARGET)
	@echo "=== Quick Prime Number Test ==="
	./$(TEST_TARGET)

.PHONY: all test clean test-primes test-small test-single test-errors check-compilation quick-test