# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = ex5_lr1
TEST_TARGET = test_ex5_lr1

# Исходные файлы
MAIN_SRCS = ex5_lr1.c ex5_lr1_func.c
TEST_SRCS = test_ex5_lr1.c ex5_lr1_func.c

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
	@echo "Running Unit Tests for ex5_lr1"
	@echo "========================================"
	./$(TEST_TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET) test_input.txt test_output.txt out_*.txt integration_test.txt

# Индивидуальные тесты для каждого флага
test-d: $(TARGET)
	@echo "=== Testing -d flag (remove digits) ==="
	@echo "Hello123 World456!" > test_input.txt
	./$(TARGET) -d test_input.txt
	@cat out_test_input.txt
	@echo ""

test-i: $(TARGET)
	@echo "=== Testing -i flag (count letters) ==="
	@echo "Hello123 World!" > test_input.txt
	./$(TARGET) -i test_input.txt
	@cat out_test_input.txt
	@echo ""

test-s: $(TARGET)
	@echo "=== Testing -s flag (count special chars) ==="
	@echo "Hello, World!" > test_input.txt
	./$(TARGET) -s test_input.txt
	@cat out_test_input.txt
	@echo ""

test-a: $(TARGET)
	@echo "=== Testing -a flag (replace with HEX) ==="
	@echo "A1" > test_input.txt
	./$(TARGET) -a test_input.txt
	@cat out_test_input.txt
	@echo ""

# Тесты с флагом -n
test-nd: $(TARGET)
	@echo "=== Testing -nd flag with custom output ==="
	@echo "Test123" > test_input.txt
	./$(TARGET) -nd test_input.txt custom_output.txt
	@cat custom_output.txt
	@echo ""
	@rm -f custom_output.txt

# Тесты ошибок
test-errors: $(TARGET)
	@echo "=== Testing error handling ==="
	@echo "Testing insufficient arguments:"
	-./$(TARGET)
	@echo ""
	@echo "Testing invalid flag:"
	-./$(TARGET) -x test_input.txt
	@echo ""
	@echo "Testing non-existent file:"
	-./$(TARGET) -d nonexistent.txt

# Демонстрация
demo: $(TARGET)
	@echo "=== Demonstration ==="
	@echo "Creating test file..."
	@echo "Hello123, World! Test@456" > demo_input.txt
	@echo "Line 2: ABCdef 789" >> demo_input.txt
	@echo "Original file:"
	@cat demo_input.txt
	@echo ""
	@echo "1. Remove digits (-d):"
	./$(TARGET) -d demo_input.txt
	@cat out_demo_input.txt
	@echo ""
	@echo "2. Count letters per line (-i):"
	./$(TARGET) -i demo_input.txt
	@cat out_demo_input.txt
	@echo ""
	@echo "3. Count special chars per line (-s):"
	./$(TARGET) -s demo_input.txt
	@cat out_demo_input.txt
	@echo ""
	@echo "4. Replace with HEX (-a):"
	./$(TARGET) -a demo_input.txt
	@cat out_demo_input.txt
	@echo ""
	@rm -f demo_input.txt out_demo_input.txt

.PHONY: all test clean test-d test-i test-s test-a test-nd test-errors demo