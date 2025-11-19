#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "liver.h"
#include "command.h"

void load_from_file(LinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file %s\n", filename);
        return;
    }
    
    Liver liver;
    struct tm birth_date = {0};
    
    while (fscanf(file, "%u %49s %49s %49s %d %d %d %c %lf",
                  &liver.id, liver.surname, liver.name, liver.patronymic,
                  &birth_date.tm_mday, &birth_date.tm_mon, &birth_date.tm_year,
                  &liver.gender, &liver.income) == 9) {

        birth_date.tm_mon--;
        birth_date.tm_year -= 1900;
        liver.birth_date = birth_date;

        if (is_valid_liver(&liver)){
            insert_sorted_by_age(list, liver);
        } else {
            printf("invalid liver data: ");
            print_liver(&liver);
        }
    }

    fclose(file);
}




