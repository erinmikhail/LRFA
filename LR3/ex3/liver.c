#include <liver.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_liver(const Liver *liver){
    printf("ID: %u, Name: %s %s %s, Birth: %02d.%02d.%d, Gender: %c, Income: %.2f\n",
           liver->id, liver->surname, liver->name, liver->patronymic,
           liver->birth_date.tm_mday, liver->birth_date.tm_mon + 1, 
           liver->birth_date.tm_year + 1900, liver->gender, liver->income);
}

