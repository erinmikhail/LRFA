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
        printf("error file write");
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


void add_resident(LinkedList* list, CommandHistory* history) {
    Liver liver;
    struct tm birth_date = {0};
    
    printf("Enter ID: ");
    scanf("%u", &liver.id);
    
    printf("Enter surname: ");
    scanf("%49s", liver.surname);
    
    printf("Enter name: ");
    scanf("%49s", liver.name);
    
    printf("Enter patronymic: ");
    scanf("%49s", liver.patronymic);
    
    printf("Enter birth date (day month year): ");
    scanf("%d %d %d", &birth_date.tm_mday, &birth_date.tm_mon, &birth_date.tm_year);
    birth_date.tm_mon--; 
    birth_date.tm_year -= 1900; 
    liver.birth_date = birth_date;
    
    printf("Enter gender (M/W): ");
    scanf(" %c", &liver.gender);
    
    printf("Enter income: ");
    scanf("%lf", &liver.income);
    
    if (!is_valid_liver(&liver)) {
        printf("Invalid liver data\n");
        return;
    }
    
    Modification mod;
    mod.type = CMD_ADD;
    mod.index = list->size; 
    mod.new_data = liver;
    add_modification(history, mod);
    
    insert_sorted_by_age(list, liver);
    printf("Resident added successfully\n");
}


void delete_resident(LinkedList *list, CommandHistory* history){
    unsigned int id;
    printf("Enter ID resid delete ");
    scanf("%u", &id);

    int index = find_liver_by_id(list, id);
    if (index == -1) {
        printf("resid with ID not found\n");
        return;
    }

    Liver liver = get_at_list(list, index);

    Modification mod;
    mod.type = CMD_DELETE;
    mod.index = index;
    mod.old_data = liver;
    add_modification(history, mod);

    delete_at_list(list, index);
    printf("resid deletd sucs");
}

void modify_resident(LinkedList *list, CommandHistory* history){
    unsigned int id;
    printf("enter id: ");
    scanf("%u", &id);

    int index = find_liver_by_id(list, id);
    if (index == -1) {
        printf("Resident with ID %u not found\n", id);
        return;
    }
    
    Liver old_liver = get_at_list(list, index);
    Liver new_liver = old_liver;
    
    printf("Modifying resident: ");
    print_liver(&old_liver);

        printf("Enter new surname (current: %s): ", new_liver.surname);
    scanf("%49s", new_liver.surname);
    
    printf("Enter new name (current: %s): ", new_liver.name);
    scanf("%49s", new_liver.name);
    
    printf("Enter new patronymic (current: %s): ", new_liver.patronymic);
    scanf("%49s", new_liver.patronymic);
    
    printf("Enter new birth date (day month year) (current: %02d.%02d.%d): ",
           old_liver.birth_date.tm_mday, old_liver.birth_date.tm_mon + 1, 
           old_liver.birth_date.tm_year + 1900);
    scanf("%d %d %d", &new_liver.birth_date.tm_mday, 
          &new_liver.birth_date.tm_mon, &new_liver.birth_date.tm_year);
    new_liver.birth_date.tm_mon--;
    new_liver.birth_date.tm_year -= 1900;
    
    printf("Enter new gender (M/W) (current: %c): ", new_liver.gender);
    scanf(" %c", &new_liver.gender);
    
    printf("Enter new income (current: %.2f): ", new_liver.income);
    scanf("%lf", &new_liver.income);
    
    if (!is_valid_liver(&new_liver)) {
        printf("Invalid liver data\n");
        return;
    }

    Modification mod;
    mod.type = CMD_MODIFY;
    mod.index = index;
    mod.old_data = old_liver;
    mod.new_data = new_liver;
    add_modification(history, mod);

    delete_at_list(list, index);
    insert_sorted_by_age(list, new_liver);
    
    printf("Resident modified successfully\n");
}

void undo_modifications(CommandHistory* history, LinkedList* list, int count){
    int total_modifications = history->current_index;

    if (total_modifications == 0) {
        printf("No modifications to undo\n");
        return;
    }
    
    int undo_count = total_modifications / 2;
    printf("Total modifications: %d\n", total_modifications);
    printf("Undoing %d modifications...\n", undo_count);
    
    undo_last_modifications(history, list, undo_count);
    
    printf("Successfully undone %d modifications\n", undo_count);

}


int main() {
    LinkedList list = create_list();
    CommandHistory history;
    init_command_history(&history);
    
    char filename[100];
    int choice;
    
    printf("Resident Management System\n");
    
    do {
        printf("\nMenu:\n");
        printf("1. Load from file\n");
        printf("2. Save to file\n");
        printf("3. Display all residents\n");
        printf("4. Search resident\n");
        printf("5. Add resident\n");
        printf("6. Modify resident\n");
        printf("7. Delete resident\n");
        printf("8. Undo modifications\n");
        printf("9. Test stack operations\n");
        printf("10. Test queue operations\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter filename: ");
                scanf("%99s", filename);
                load_from_file(&list, filename);
                break;
                
            case 2:
                printf("Enter filename: ");
                scanf("%99s", filename);
                safe_to_file(&list, filename);
                break;
                
            case 3:
                print_list(&list);
                break;
                
            case 4:
                search_resident(&list);
                break;
                
            case 5:
                add_resident(&list, &history);
                break;
                
            case 6:
                modify_resident(&list, &history);
                break;
                
            case 7:
                delete_resident(&list, &history);
                break;
                
            case 8:
                undo_modifications(&history, &list);
                break;
                
            case 9:
                printf("Testing stack operations...\n");
                if (list.size > 0) {
                    Liver top = peek_stack(&list);
                    printf("Top of stack: ");
                    print_liver(&top);
                }
                break;
                
            case 10:
                printf("Testing queue operations...\n");
                if (list.size > 0) {
                    Liver front = peek_queue(&list);
                    printf("Front of queue: ");
                    print_liver(&front);
                }
                break;
                
            case 0:
                printf("Exiting...\n");
                break;
                
            default:
                printf("Invalid choice\n");
        }
    } while (choice != 0);
    
    delete_list(&list);
    return 0;
}