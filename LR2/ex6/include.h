#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 50
#define GROUP_LEN 15
#define EXAMS_COUNT 5

typedef struct{
    unsigned int id;
    char first_name[NAME_LEN];
    char last_name[NAME_LEN];
    char group[GROUP_LEN];
    unsigned char *grades; // дим массив с оценками
} Student;

typedef struct{
    Student *data;
    int size;
} StudentArray;

int load_students(const char *filename, StudentArray *students);
void free_students(StudentArray *students);
double calculate_cr_num(const Student *student);
double calculate_obcr_num(const StudentArray *students);

void find_by_id(const StudentArray *students);
void find_by_last_name(const StudentArray *students);
void find_by_first_name(const StudentArray *students);
void find_by_group(const StudentArray *students);

int compare_id(const void *a, const void *b);
int compare_last_name(const void *a, const void *b);
int compare_first_name(const void *a, const void *b);
int compare_group(const void *a, const void *b);

void log_student_by_id(const StudentArray *students, const char *trace_file);
void log_top_students(const StudentArray *students, const char *trace_file);

void print_menu(void);
void handle_menu_choice(int choise, StudentArray *students, const char *trace_file);

void run_tests(void);

#endif

