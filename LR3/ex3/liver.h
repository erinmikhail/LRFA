#ifndef LIVER_H
#define LIVER_H

#include <time.h>

typedef struct{
    unsigned int id;
    char surname[50];
    char name[50];
    char patronymic[50];
    struct tm birth_date;
    char gender;
    double income;
} Liver;

void print_liver(const Liver *liver);
int compare_liver_age(const Liver *l1, const Liver *l2);
int is_valid_liver(const Liver *liver);
Liver create_liver(unsigned int id, const char* surname, const char* name, 
                   const char* patronymic, struct tm birth_date, char gender, double income);
#endif