#include "include.h"

int load_students(const char *filename, StudentArray *students){
    FILE *file = fopen(filename, "r");
    if (!file){
        printf("Ошибкаб не открывается %s\n", filename);
        return 0;
    }

    students->size = 0;
    students->data = NULL;

    Student temp_student;
        while (fscanf(file, "%u %49s %49s %9s",
                  &temp_student.id,
                  temp_student.first_name,
                  temp_student.last_name,
                  temp_student.group) == 4) {

        temp_student.grades = (unsigned char*)malloc(EXAMS_COUNT * sizeof(unsigned char));
        if (!temp_student.grades) {
            printf("Ошибка выделения памяти для оценок.\n");
            fclose(file);
            free_students(students);
            return 0;
        }

        for (int i = 0; i < EXAMS_COUNT; i++) {
            if (fscanf(file, "%hhu", &temp_student.grades[i]) != 1) {
                printf("Ошибка чтения оценок для студента %u.\n", temp_student.id);
                free(temp_student.grades);
                fclose(file);
                free_students(students);
                return 0;
            }
        }

        Student *new_data = (Student*)realloc(students->data, (students->size + 1) * sizeof(Student));
        if (!new_data) {
            printf("Ошибка перевыделения памяти для массива студентов.\n");
            free(temp_student.grades);
            fclose(file);
            free_students(students);
            return 0;
        }
        students->data = new_data;
        students->data[students->size] = temp_student; // временный студент коп в массив
        students->size++;
    }

    fclose(file);
    printf("Загружено %d студентов.\n", students->size);
    return 1;
}


void free_students(StudentArray *students){
    for (int i = 0; i < students->size; i++){
        free(students->data[i].grades);
    }
    free(students->data);
    students->data = NULL;
    students->size = 0;
}

double calculate_cr_num(const Student *student){
    int sum = 0;
    for (int i = 0; i < EXAMS_COUNT; i++){
        sum += student->grades[i];
    }
    return (double)sum / EXAMS_COUNT;
}

double calculate_obcr_num(const StudentArray *students){
    if (students->size == 0){
        return 0.0;
    }
    double total_sum = 0.0;
    for (int i = 0; i < students->size; i++){
        total_sum += calculate_cr_num(&students->data[i]);
    }
    return total_sum / students->size;
}

void find_by_id(const StudentArray *students) {
    unsigned int id;
    printf("Введите ID для поиска: ");
    scanf("%u", &id);
    int found = 0;
    for (int i = 0; i < students->size; i++) {
        if (students->data[i].id == id) {
            printf("Найден: %u %s %s %s\n", students->data[i].id, students->data[i].first_name, students->data[i].last_name, students->data[i].group);
            found = 1;
            break; // ID предположительно уникален
        }
    }
    if (!found) {
        printf("Студент с ID %u не найден.\n", id);
    }
}

void find_by_last_name(const StudentArray *students) {
    char name[NAME_LEN];
    printf("Введите фамилию для поиска: ");
    scanf("%49s", name);
    int found = 0;
    for (int i = 0; i < students->size; i++) {
        if (strcmp(students->data[i].last_name, name) == 0) {
            printf("Найден: %u %s %s %s\n", students->data[i].id, students->data[i].first_name, students->data[i].last_name, students->data[i].group);
            found = 1;
        }
    }
    if (!found) {
        printf("Студент с фамилией '%s' не найден.\n", name);
    }
}

void find_by_first_name(const StudentArray *students) {
    char name[NAME_LEN];
    printf("Введите имя для поиска: ");
    scanf("%49s", name);
    int found = 0;
    for (int i = 0; i < students->size; i++) {
        if (strcmp(students->data[i].first_name, name) == 0) {
            printf("Найден: %u %s %s %s\n", students->data[i].id, students->data[i].first_name, students->data[i].last_name, students->data[i].group);
            found = 1;
        }
    }
    if (!found) {
        printf("Студент с именем '%s' не найден.\n", name);
    }
}

void find_by_group(const StudentArray *students) {
    char group[GROUP_LEN];
    printf("Введите группу для поиска: ");
    scanf("%9s", group);
    int found = 0;
    for (int i = 0; i < students->size; i++) {
        if (strcmp(students->data[i].group, group) == 0) {
            printf("Найден: %u %s %s %s\n", students->data[i].id, students->data[i].first_name, students->data[i].last_name, students->data[i].group);
            found = 1;
        }
    }
    if (!found) {
        printf("Студенты из группы '%s' не найдены.\n", group);
    }
}

int compare_id(const void *a, const void *b) {
    const Student *studentA = (const Student*)a;
    const Student *studentB = (const Student*)b;
    return (studentA->id > studentB->id) - (studentA->id < studentB->id);
}

int compare_last_name(const void *a, const void *b) {
    const Student *studentA = (const Student*)a;
    const Student *studentB = (const Student*)b;
    return strcmp(studentA->last_name, studentB->last_name);
}

int compare_first_name(const void *a, const void *b) {
    const Student *studentA = (const Student*)a;
    const Student *studentB = (const Student*)b;
    return strcmp(studentA->first_name, studentB->first_name);
}

int compare_group(const void *a, const void *b) {
    const Student *studentA = (const Student*)a;
    const Student *studentB = (const Student*)b;
    return strcmp(studentA->group, studentB->group);
}

void log_student_by_id(const StudentArray *students, const char *trace_file) {
    unsigned int id;
    printf("Введите ID студента для записи в трассировочный файл: ");
    scanf("%u", &id);

    FILE *file = fopen(trace_file, "a"); 
    if (!file) {
        printf("Ошибка открытия трассировочного файла для записи.\n");
        return;
    }

    int found = 0;
    for (int i = 0; i < students->size; i++) {
        if (students->data[i].id == id) {
            double avg = calculate_cr_num(&students->data[i]);
            fprintf(file, "Студент по ID %u: %s %s, Группа: %s, Средний балл: %.2f\n",
                    id, students->data[i].first_name, students->data[i].last_name,
                    students->data[i].group, avg);
            found = 1;
            printf("Информация о студенте с ID %u записана в трассировочный файл.\n", id);
            break;
        }
    }
    if (!found) {
        printf("Студент с ID %u не найден. В трассировочный файл ничего не записано.\n", id);
    }
    fclose(file);
}

void log_top_students(const StudentArray *students, const char *trace_file) {
    double overall_avg = calculate_obcr_num(students);
    if (students->size == 0) {
        printf("Нет данных о студентах.\n");
        return;
    }

    FILE *file = fopen(trace_file, "a");
    if (!file) {
        printf("Ошибка открытия трассировочного файла для записи.\n");
        return;
    }

    fprintf(file, "\n--- Студенты со средним баллом выше общего (%.2f) ---\n", overall_avg);
    int logged = 0;
    for (int i = 0; i < students->size; i++) {
        double student_avg = calculate_cr_num(&students->data[i]);
        if (student_avg > overall_avg) {
            fprintf(file, "%s %s (Ср. балл: %.2f)\n",
                    students->data[i].first_name,
                    students->data[i].last_name,
                    student_avg);
            logged++;
        }
    }
    if (logged == 0) {
        fprintf(file, "Таких студентов нет.\n");
    } else {
        printf("Информация о %d студентах с высоким баллом записана в трассировочный файл.\n", logged);
    }
    fclose(file);
}