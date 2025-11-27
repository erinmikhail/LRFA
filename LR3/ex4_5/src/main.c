#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "post_system.h"

void load_mappings(PostSystem *system, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: cannot open file %s\n", filename);
        return;
    }
    
    int office1, office2;
    int mapping_count = 0;
    
    printf("Loading office mappings...\n");
    
    while (fscanf(file, "%d %d", &office1, &office2) == 2) {
        if (!find_office_by_id(system, office1)) {
            int connections[] = {office2};
            add_post_office(system, office1, 10, connections, 1);
        }
        
        if (!find_office_by_id(system, office2)) {
            int connections[] = {office1};
            add_post_office(system, office2, 10, connections, 1);
        }
        
        mapping_count++;
    }
    
    fclose(file);
    printf("Loaded %d mappings\n", mapping_count);
}

void add_office_ui(PostSystem *system) {
    int id, capacity;
    printf("Enter office ID: ");
    scanf("%d", &id);
    printf("Enter office capacity: ");
    scanf("%d", &capacity);
    
    if (add_post_office(system, id, capacity, NULL, 0)) {
        printf("Office %d added\n", id);
    } else {
        printf("Error adding office %d\n", id);
    }
}

void remove_office_ui(PostSystem *system) {
    int id;
    printf("Enter office ID to remove: ");
    scanf("%d", &id);
    
    if (remove_post_office(system, id)) {
        printf("Office %d removed\n", id);
    } else {
        printf("Office %d not found\n", id);
    }
}

void add_letter_ui(PostSystem *system) {
    int from_id, to_id, priority, type_choice;
    char tech_data[100];
    
    printf("Enter from office ID: ");
    scanf("%d", &from_id);
    printf("Enter to office ID: ");
    scanf("%d", &to_id);
    printf("Enter priority: ");
    scanf("%d", &priority);
    printf("Letter type (1-Regular, 2-Urgent): ");
    scanf("%d", &type_choice);
    printf("Enter tech data: ");
    scanf("%s", tech_data);
    
    LetterType type = (type_choice == 2) ? URGENT : REGULAR;
    
    int letter_id = add_letter(system, type, priority, from_id, to_id, tech_data);
    if (letter_id > 0) {
        printf("Letter %d added\n", letter_id);
    } else {
        printf("Error adding letter\n");
    }
}

void mark_undeliverable_ui(PostSystem *system) {
    int letter_id;
    printf("Enter letter ID to mark undelivered: ");
    scanf("%d", &letter_id);
    
    if (mark_letter_undeliverable(system, letter_id)) {
        printf("Letter %d marked undelivered\n", letter_id);
    } else {
        printf("Letter %d not found\n", letter_id);
    }
}

void pickup_letter_ui(PostSystem *system) {
    int letter_id;
    printf("Enter letter ID to pickup: ");
    scanf("%d", &letter_id);
    
    if (pickup_letter(system, letter_id)) {
        printf("Letter %d picked up\n", letter_id);
    } else {
        printf("Letter %d not found or not delivered\n", letter_id);
    }
}

void print_letters_ui(PostSystem *system) {
    char filename[100];
    printf("Enter filename for letters list: ");
    scanf("%s", filename);
    
    print_all_letters(system, filename);
    printf("Letters saved to %s\n", filename);
}

void show_system_status(PostSystem *system) {
    printf("\n=== SYSTEM STATUS ===\n");
    printf("Offices: %d\n", system->office_count);
    printf("Letters: %d\n", system->letter_count);
    
    int in_transit = 0, delivered = 0, undelivered = 0;
    for (int i = 0; i < system->letter_count; i++) {
        switch (system->letters[i].state) {
            case IN_TRANSIT: in_transit++; break;
            case DELIVERED: delivered++; break;
            case UNDELIVERED: undelivered++; break;
        }
    }
    
    printf("In transit: %d\n", in_transit);
    printf("Delivered: %d\n", delivered);
    printf("Undelivered: %d\n", undelivered);
}

void show_main_menu() {
    printf("\n=== POSTAL SERVICE ===\n");
    printf("1. Add office\n");
    printf("2. Remove office\n");
    printf("3. Add letter\n");
    printf("4. Mark letter undelivered\n");
    printf("5. Pickup letter\n");
    printf("6. Show all letters\n");
    printf("7. System status\n");
    printf("8. Process delivery\n");
    printf("9. Exit\n");
    printf("Choice: ");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <mappings_file> <log_file>\n", argv[0]);
        return 1;
    }
    
    PostSystem *system = create_post_system(argv[2]);
    if (!system) {
        printf("Error creating system\n");
        return 1;
    }
    
    printf("Postal system started\n");
    printf("Log file: %s\n", argv[2]);
    
    load_mappings(system, argv[1]);
    
    int choice;
    int auto_process = 0;
    
    while (1) {
        if (!auto_process) {
            show_main_menu();
            scanf("%d", &choice);
        } else {
            choice = 8;
            sleep(1);
        }
        
        switch (choice) {
            case 1: add_office_ui(system); break;
            case 2: remove_office_ui(system); break;
            case 3: add_letter_ui(system); break;
            case 4: mark_undeliverable_ui(system); break;
            case 5: pickup_letter_ui(system); break;
            case 6: print_letters_ui(system); break;
            case 7: show_system_status(system); break;
            case 8:
                process_mail_delivery(system);
                if (!auto_process) {
                    printf("Enable auto mode? (1-yes, 0-no): ");
                    int auto_choice;
                    scanf("%d", &auto_choice);
                    auto_process = (auto_choice == 1);
                }
                break;
            case 9:
                printf("Exiting...\n");
                delete_post_system(system);
                return 0;
            default:
                printf("Invalid choice\n");
                break;
        }
        
        if (auto_process && (rand() % 10 == 0)) {
            show_system_status(system);
        }
    }
    
    delete_post_system(system);
    return 0;
}