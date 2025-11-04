# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Werror -Wextra -Wpedantic -fsanitize=address
TARGET = number_converter
TEST_TARGET = test_ex7_lr1

# Исходные файлы
MAIN_SRC = ex7_lr1.c
FUNC_SRC = ex7_lr1_func.c
TEST_SRC = test_ex7_lr1.c
HEADER = ex7_lr1.h

# Основная цель - сборка программы
all: $(TARGET)

$(TARGET): $(MAIN_SRC) $(FUNC_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN_SRC) $(FUNC_SRC)

# Сборка и запуск тестов
test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRC) $(FUNC_SRC) $(HEADER)
	$(CC) $(CFLAGS) -o $(TEST_TARGET) $(TEST_SRC) $(FUNC_SRC)

# Очистка
clean:
	rm -f $(TARGET) $(TEST_TARGET) test_input.txt test_output.txt test_error_input.txt test_error_output.txt

# Пересборка
rebuild: clean all

# Запуск с примером
run: $(TARGET)
	./$(TARGET) input.txt output.txt

# Проверка стиля кода (опционально)
check:
	@echo "Checking code style..."
	@! grep -n "printf" ex7_lr1_func.c | grep -v "//" || (echo "Error: printf in func.c" && exit 1)

.PHONY: all test clean rebuild run check