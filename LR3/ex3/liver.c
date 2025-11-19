#include "liver.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_liver(const Liver *liver){
    printf("ID: %u, Name: %s %s %s, Birth: %02d.%02d.%d, Gender: %c, Income: %.2f\n",
           liver->id, liver->surname, liver->name, liver->patronymic,
           liver->birth_date.tm_mday, liver->birth_date.tm_mon + 1, 
           liver->birth_date.tm_year + 1900, liver->gender, liver->income);
}

int compare_liver_age(const Liver *l1, const Liver *l2){
    if(l1->birth_date.tm_year != l2->birth_date.tm_year){
        return l1->birth_date.tm_year - l2->birth_date.tm_year;
    }
    if (l1->birth_date.tm_mon != l2->birth_date.tm_mon){
        l1->birth_date.tm_mon - l2->birth_date.tm_mon;
    }
    if (l1->birth_date.tm_mday != l2->birth_date.tm_mday){
        return l1->birth_date.tm_mday - l2->birth_date.tm_mday;
    }
}

int int_valid_liver(const Liver *liver){
    if (liver->id < 0){
        return 0;
    }

    if (strlen(liver->surname) == 0){
        return 0;
    }
    for (int i = 0; liver->surname[i]; i++){
        if(!isalpha(liver->surname[i])){
            return 0;
        }
    }

     if (strlen(liver->name) == 0){
        return 0;
    }
    for (int i = 0; liver->name[i]; i++){
        if(!isalpha(liver->name[i])){
            return 0;
        }
    }

        for (int i = 0; liver->patronymic[i]; i++){
        if(!isalpha(liver->patronymic[i])){
            return 0;
        }
    }

    if (liver->gender != 'M' && liver->gender != 'W'){
        return 0;
    }

    if (liver->income < 0){
        return 0;
    }

    return 1;
}

Liver create_liver(unsigned int id, const char* surname, const char* name, 
                   const char* patronymic, struct tm birth_date, char gender, double income){
    Liver liver;
    liver.id = id;
    strcpy(liver.surname, surname);
    strcpy(liver.name, name);
    strcpy(liver.patronymic, patronymic);
    liver.birth_date = birth_date;
    liver.gender = gender;
    liver.income = income;
    return liver;        
}
