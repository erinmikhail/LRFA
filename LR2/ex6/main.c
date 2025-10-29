#include "include.h"

void print_menu(void) {
    printf("\n=== Меню ===\n");
    printf("1. Найти студента по ID\n");
    printf("2. Найти студента по фамилии\n");
    printf("3. Найти студента по имени\n");
    printf("4. Найти студентов по группе\n");
    printf("5. Отсортировать студентов по ID\n");
    printf("6. Отсортировать студентов по фамилии\n");
    printf("7. Отсортировать студентов по имени\n");
    printf("8. Отсортировать студентов по группе\n");
    printf("9. Записать данные студента по ID в трасс. файл\n");
    printf("10. Записать студентов с высоким баллом в трасс. файл\n");
    printf("11. Вывести всех студентов (для проверки)\n");
    printf("0. Выйти\n");
    printf("Выберите опцию: ");
}

void handle_menu_choice(int choice, StudentArray *students, const char *trace_file) {
    switch (choice) {
        case 1: 
            find_by_id(students); 
            break;
        case 2: 
            find_by_last_name(students); 
            break;
        case 3: 
            find_by_first_name(students); 
            break;
        case 4: 
            find_by_group(students); 
            break;
        case 5: 
            qsort(students->data, students->size, sizeof(Student), compare_id); 
            printf("Отсортировано по ID.\n"); 
            break;
        case 6: 
            qsort(students->data, students->size, sizeof(Student), compare_last_name); 
            printf("Отсортировано по фамилии.\n"); 
            break;
        case 7: 
            qsort(students->data, students->size, sizeof(Student), compare_first_name); 
            printf("Отсортировано по имени.\n"); 
            break;
        case 8: 
            qsort(students->data, students->size, sizeof(Student), compare_group); 
            printf("Отсортировано по группе.\n"); 
            break;
        case 9: 
            log_student_by_id(students, trace_file); 
            break;
        case 10: 
            log_top_students(students, trace_file); 
            break;
        case 11:
            if (students->size == 0) {
                printf("Нет загруженных студентов.\n");
            } else {
                printf("\n=== Все студенты (%d) ===\n", students->size);
                for (int i = 0; i < students->size; i++) {
                    printf("%u %s %s %s | Оценки: ", 
                           students->data[i].id, 
                           students->data[i].first_name, 
                           students->data[i].last_name, 
                           students->data[i].group);
                    for (int j = 0; j < EXAMS_COUNT; j++) {
                        printf("%hhu ", students->data[i].grades[j]);
                    }
                    printf("| Ср. балл: %.2f\n", calculate_cr_num(&students->data[i]));
                }
            }
            break;
        case 0: 
            printf("Выход...\n"); 
            break;
        default: 
            printf("Неверная опция! Пожалуйста, выберите от 0 до 11.\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Использование: %s <путь_к_файлу_данных> <путь_к_трассировочному_файлу>\n", argv[0]);
        return 1;
    }

    const char *data_file = argv[1];
    const char *trace_file = argv[2];

    StudentArray students = {NULL, 0};

    if (!load_students(data_file, &students)) {
        return 1;
    }

    int choice;
    do {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            choice = -1; 
        }
        handle_menu_choice(choice, &students, trace_file);
    } while (choice != 0);

    free_students(&students);
    return 0;
}