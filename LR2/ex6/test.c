#include "include.h"
#include <assert.h>

// Вспомогательные функции для тестирования
void test_calculate_average_grade(void) {
    printf("=== Тест calculate_cr_num ===\n");
    
    Student student = {
        .id = 1,
        .first_name = "Test",
        .last_name = "User", 
        .group = "TEST-01"
    };
    
    // Выделяем память под оценки
    student.grades = (unsigned char*)malloc(EXAMS_COUNT * sizeof(unsigned char));
    assert(student.grades != NULL);
    
    // Тест 1: Все оценки 5
    for (int i = 0; i < EXAMS_COUNT; i++) {
        student.grades[i] = 5;
    }
    double avg = calculate_cr_num(&student);
    assert(avg == 5.0);
    printf("Тест 1 пройден: средний балл 5.0 = %.2f\n", avg);
    
    // Тест 2: Разные оценки
    student.grades[0] = 5;
    student.grades[1] = 4;
    student.grades[2] = 3;
    student.grades[3] = 5;
    student.grades[4] = 4;
    avg = calculate_cr_num(&student);
    assert(avg == 4.2);
    printf("Тест 2 пройден: средний балл 4.2 = %.2f\n", avg);
    
    // Тест 3: Все оценки 2
    for (int i = 0; i < EXAMS_COUNT; i++) {
        student.grades[i] = 2;
    }
    avg = calculate_cr_num(&student);
    assert(avg == 2.0);
    printf("Тест 3 пройден: средний балл 2.0 = %.2f\n", avg);
    
    free(student.grades);
    printf("Все тесты calculate_cr_num пройдены!\n\n");
}

void test_compare_functions(void) {
    printf("=== Тест функций сравнения ===\n");
    
    Student student1 = {.id = 10, .first_name = "John", .last_name = "Smith", .group = "GROUP-A"};
    Student student2 = {.id = 20, .first_name = "Anna", .last_name = "Adams", .group = "GROUP-B"};
    
    // Тест compare_id
    int result = compare_id(&student1, &student2);
    assert(result < 0); // 10 < 20
    printf("Тест compare_id пройден: %d < 0\n", result);
    
    result = compare_id(&student2, &student1);
    assert(result > 0); // 20 > 10
    printf("Тест compare_id пройден: %d > 0\n", result);
    
    // Тест compare_last_name
    result = compare_last_name(&student1, &student2);
    assert(result > 0); // "Smith" > "Adams"
    printf("Тест compare_last_name пройден: %d > 0\n", result);
    
    result = compare_last_name(&student2, &student1);
    assert(result < 0); // "Adams" < "Smith"
    printf("Тест compare_last_name пройден: %d < 0\n", result);
    
    // Тест compare_first_name
    result = compare_first_name(&student1, &student2);
    assert(result > 0); // "John" > "Anna"
    printf("Тест compare_first_name пройден: %d > 0\n", result);
    
    // Тест compare_group
    result = compare_group(&student1, &student2);
    assert(result < 0); // "GROUP-A" < "GROUP-B"
    printf("Тест compare_group пройден: %d < 0\n", result);
    
    printf("Все тесты функций сравнения пройдены!\n\n");
}

void test_student_array_operations(void) {
    printf("=== Тест операций с массивом студентов ===\n");
    
    StudentArray students = {NULL, 0};
    
    // Тест инициализации
    assert(students.data == NULL);
    assert(students.size == 0);
    printf("Тест инициализации пройден\n");
    
    // Тест освобождения пустого массива
    free_students(&students);
    assert(students.data == NULL);
    assert(students.size == 0);
    printf("Тест освобождения пустого массива пройден\n");
    
    printf("Все тесты операций с массивом пройдены!\n\n");
}

void test_calculate_overall_average(void) {
    printf("=== Тест calculate_obcr_num ===\n");
    
    StudentArray students = {NULL, 0};
    
    // Тест с пустым массивом
    double overall_avg = calculate_obcr_num(&students);
    assert(overall_avg == 0.0);
    printf("Тест с пустым массивом пройден: %.2f == 0.0\n", overall_avg);
    
    // Создаем тестовых студентов
    students.size = 2;
    students.data = (Student*)malloc(students.size * sizeof(Student));
    assert(students.data != NULL);
    
    // Студент 1
    students.data[0].id = 1;
    strcpy(students.data[0].first_name, "Test1");
    strcpy(students.data[0].last_name, "User1");
    strcpy(students.data[0].group, "TEST-01");
    students.data[0].grades = (unsigned char*)malloc(EXAMS_COUNT * sizeof(unsigned char));
    for (int i = 0; i < EXAMS_COUNT; i++) {
        students.data[0].grades[i] = 5; // Средний = 5.0
    }
    
    // Студент 2
    students.data[1].id = 2;
    strcpy(students.data[1].first_name, "Test2");
    strcpy(students.data[1].last_name, "User2");
    strcpy(students.data[1].group, "TEST-01");
    students.data[1].grades = (unsigned char*)malloc(EXAMS_COUNT * sizeof(unsigned char));
    for (int i = 0; i < EXAMS_COUNT; i++) {
        students.data[1].grades[i] = 3; // Средний = 3.0
    }
    
    // Тест расчета общего среднего
    overall_avg = calculate_obcr_num(&students);
    assert(overall_avg == 4.0); // (5.0 + 3.0) / 2 = 4.0
    printf("Тест расчета общего среднего пройден: %.2f == 4.0\n", overall_avg);
    
    // Очистка
    free_students(&students);
    printf("Все тесты calculate_obcr_num пройдены!\n\n");
}

void test_comparators_edge_cases(void) {
    printf("=== Тест граничных случаев компараторов ===\n");
    
    Student student1 = {.id = 10, .first_name = "John", .last_name = "Smith", .group = "GROUP-A"};
    Student student2 = {.id = 10, .first_name = "John", .last_name = "Smith", .group = "GROUP-A"};
    
    // Тест одинаковых студентов
    int result = compare_id(&student1, &student2);
    assert(result == 0);
    printf("Тест одинаковых ID пройден: %d == 0\n", result);
    
    result = compare_last_name(&student1, &student2);
    assert(result == 0);
    printf("Тест одинаковых фамилий пройден: %d == 0\n", result);
    
    result = compare_first_name(&student1, &student2);
    assert(result == 0);
    printf("Тест одинаковых имен пройден: %d == 0\n", result);
    
    result = compare_group(&student1, &student2);
    assert(result == 0);
    printf("Тест одинаковых групп пройден: %d == 0\n", result);
    
    printf("Все тесты граничных случаев пройдены!\n\n");
}

void test_file_operations(void) {
    printf("=== Тест файловых операций ===\n");
    
    // Создаем тестовый файл
    FILE *test_file = fopen("test_data.txt", "w");
    assert(test_file != NULL);
    
    fprintf(test_file, "1 Ivan Petrov IKBO-01 5 4 5 3 5\n");
    fprintf(test_file, "2 Anna Sidorova IKBO-02 4 5 4 4 5\n");
    fprintf(test_file, "3 John Doe IKBO-01 3 4 3 4 3\n");
    fclose(test_file);
    
    // Тест загрузки студентов
    StudentArray students = {NULL, 0};
    int load_result = load_students("test_data.txt", &students);
    assert(load_result == 1);
    assert(students.size == 3);
    printf("Тест загрузки из файла пройден: загружено %d студентов\n", students.size);
    
    // Проверяем корректность загруженных данных
    assert(students.data[0].id == 1);
    assert(strcmp(students.data[0].first_name, "Ivan") == 0);
    assert(strcmp(students.data[0].last_name, "Petrov") == 0);
    assert(strcmp(students.data[0].group, "IKBO-01") == 0);
    assert(students.data[0].grades[0] == 5);
    printf("Тест корректности данных пройден\n");
    
    // Тест несуществующего файла
    load_result = load_students("nonexistent_file.txt", &students);
    assert(load_result == 0);
    printf("Тест несуществующего файла пройден\n");
    
    // Очистка
    free_students(&students);
    remove("test_data.txt"); // Удаляем тестовый файл
    printf("Все тесты файловых операций пройдены!\n\n");
}

void test_sorting_functions(void) {
    printf("=== Тест функций сортировки ===\n");
    
    // Создаем тестовый массив студентов
    StudentArray students = {NULL, 0};
    students.size = 3;
    students.data = (Student*)malloc(students.size * sizeof(Student));
    
    // Неупорядоченные данные
    students.data[0].id = 30; strcpy(students.data[0].last_name, "Smith");
    students.data[1].id = 10; strcpy(students.data[1].last_name, "Adams"); 
    students.data[2].id = 20; strcpy(students.data[2].last_name, "Brown");
    
    // Тест сортировки по ID
    qsort(students.data, students.size, sizeof(Student), compare_id);
    assert(students.data[0].id == 10);
    assert(students.data[1].id == 20);
    assert(students.data[2].id == 30);
    printf("Тест сортировки по ID пройден\n");
    
    // Тест сортировки по фамилии
    qsort(students.data, students.size, sizeof(Student), compare_last_name);
    assert(strcmp(students.data[0].last_name, "Adams") == 0);
    assert(strcmp(students.data[1].last_name, "Brown") == 0);
    assert(strcmp(students.data[2].last_name, "Smith") == 0);
    printf("Тест сортировки по фамилии пройден\n");
    
    free(students.data);
    printf("Все тесты сортировки пройдены!\n\n");
}

// Главная функция запуска всех тестов
void run_tests(void) {
    printf(" ЗАПУСК UNIT-ТЕСТОВ\n\n");
    
    test_calculate_average_grade();
    test_compare_functions();
    test_student_array_operations();
    test_calculate_overall_average();
    test_comparators_edge_cases();
    test_file_operations();
    test_sorting_functions();
    
    printf(" ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ!\n");
}

// ТОЧКА ВХОДА ДЛЯ ТЕСТОВОЙ ПРОГРАММЫ
int main(void) {
    run_tests();
    return 0;
}