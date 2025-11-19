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


void safe_to_file(const LinkedList *list, const char* filename){
    FILE* file = fopen(filename, "w");
    if (!file){
        pritnf("error file write");
        return;
    }

    Uzel* current = list->head;
    while (current) {
        Liver* liver = &current->data;
        fprintf(file, "%u %s %s %s %d %d %d %c %.2f\n",
                liver->id, liver->surname, liver->name, liver->patronymic,
                liver->birth_date.tm_mday, liver->birth_date.tm_mon + 1, 
                liver->birth_date.tm_year + 1900, liver->gender, liver->income);
        
        current = current->next;
    }

    fclose(file);
}

void search_resident(const LinkedList* list){
    printf("Search by:\n");
    printf("1. ID\n");
    printf("2. Surname\n");
    printf("3. Gender\n");
    printf("4. Income range\n");

    int choice;
    scanf("%d", &choice);

    Uzel* current = list->head;
    int found = 0;

    switch (choice){
        case 1: {
            unsigned int id;
            printf("Enter ID; ");
            scanf("%u", &id);

            while (current){
                if (current->data.id == id){
                    print_liver(&current->data);
                    found = 1;
                }

                current = current->next;
            }

            break;
        }

        case 2: {
            char surname[50];
            printf("Enter surname: ");
            scanf("%49s", surname);

            while (current){
                if (strcmp(current->data.surname, surname) == 0){
                    print_liver(&current->data);
                    found = 1;
                }

                current = current->next;
            }

            break;
        }

        case 3: {
              char gender;
            printf("Enter gender (M/W): ");
            scanf("%c", &gender);
            
            while (current) {
                if (current->data.gender == gender) {
                    print_liver(&current->data);
                    found = 1;
                }

                current = current->next;
            }

            break;
        }

        case 4: {
            double exact_income;
            printf("Enter income ");
            scanf("%lf", &exact_income);

            while (current) {
                if (current->data.income == exact_income){
                    print_liver(&current->data);
                    found = 1;
                }

                current = current->next;
            }

            break;
        }

        default:
            printf("invalid choice\n");
            return;
    }

    if (!found){
        printf("no result\n");
    }
}

