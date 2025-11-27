#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/post_system.h"

PostSystem* create_post_system(const char *log_filename){
    PostSystem *system = malloc(sizeof(PostSystem));
    system->offices_capacity = 10;
    system->letters_capacity = 30;
    system->office_count = 0;
    system->letter_count = 0;
    system->next_letter_id = 1;
    strncpy(system->log_filename, log_filename, sizeof(system->log_filename) - 1);
    system->log_filename[sizeof(system->log_filename) - 1] = '\0';

    system->offices = malloc(system->offices_capacity * sizeof(PostOffice));
    system->letters = malloc(system->letters_capacity * sizeof(Letter));

    if (!system->offices || !system->letters){
        free(system->offices);
        free(system->letters);
        free(system);
        return NULL;
    }

    FILE *log_file = fopen(log_filename, "w");
    if (log_file){
        fclose(log_file);
    }

    log_event(system, "Post system init\n");
    return system;
}

void delete_post_system(PostSystem *system){
    if (!system){
        return;
    }

    log_event(system, "Post system shutdown\n");

    for (int i = 0; i < system->office_count; i++){
        delete_heap(&system->offices[i].letter_queue);
        free(system->offices[i].connected_ids);
    }

    free(system->offices);
    free(system->letters);
    free(system);
}

void log_event(const PostSystem *system, const char *message){
    if (!system){
        return;
    }

    FILE *log_file = fopen(system->log_filename, "a");
    if (log_file){
        time_t now = time(NULL);
        char *time_str = ctime(&now);
        time_str[strlen(time_str) - 1] = '\0';

        fprintf(log_file, "[%s] %s\n", time_str, message);
        fclose(log_file);
    }
}

PostOffice* find_office_by_id(const PostSystem *system, int id){
    if (!system){
        return NULL;
    }

    for (int i = 0; i < system->office_count; i++){
        if (system->offices[i].id == id){
            return (PostOffice*)&system->offices[i];
        }
    }

    return NULL;
}

Letter* find_letter_by_id(const PostSystem *system, int id){
    if (!system){
        return NULL;
    }

    for (int i = 0; i < system->letter_count; i++){
        if (system->letters[i].id == id){
            return (Letter*)&system->letters[i];
        }
    }

    return NULL;
}

int add_post_office(PostSystem* system, int id, int max_capacity, const int *connected_ids, int connected_count){
    if (!system || find_office_by_id(system, id)){
        return 0;
    }

    if (system->office_count >= system->offices_capacity) {
        system->offices_capacity *= 2;
        PostOffice *new_offices = realloc(system->offices, system->offices_capacity * sizeof(PostOffice));
        if (!new_offices) return 0;
        system->offices = new_offices;
    }
    
    PostOffice *office = &system->offices[system->office_count];
    office->id = id;
    office->max_capacity = max_capacity;
    office->current_load = 0;
    office->connected_count = connected_count;
    office->letter_queue = create_heap(10);

    if (connected_count > 0){
        office->connected_ids = malloc(connected_count * sizeof(int));
        if (!office->connected_ids){
            return 0;
        }
        memcpy(office->connected_ids, connected_ids, connected_count * sizeof(int));
    } else {
        office->connected_ids = NULL;
    }

    system->office_count++;

    char message[100];
    snprintf(message, sizeof(message), "added post office %d with capacity %d", id, max_capacity);
    log_event(system,message);

    return 1;
}

int remove_post_office(PostSystem *system, int id){
    if (!system){
        return 0;
    }

    int office_index = -1;
    for (int i = 0; i < system->office_count; i++){
        if (system->offices[i].id == id){
            office_index = i;
            break;
        }
    }

    if (office_index == -1){
        return 0;
    }

    PostOffice *office = &system->offices[office_index];

    while (!is_empty_heap(&office->letter_queue)){
        int letter_id = pop_heap(&office->letter_queue);
        Letter *letter = find_letter_by_id(system, letter_id);

        if (letter){
            if (letter->to_post_id == id || letter->from_post_id == id){
                letter->state = UNDELIVERED;
                char message[100];
                snprintf(message,sizeof(message), "Letter %d marked as undelivered - office %d removed", letter->id, id);
                log_event(system, message);
            } else {
                int redirected = 0;
                for (int j = 0; j < office->connected_count && !redirected; j++){
                    PostOffice *connected = find_office_by_id(system, office->connected_ids[j]);
                    if (connected && connected->current_load < connected->max_capacity){
                        push_heap(&connected->letter_queue, letter->id);
                        connected->current_load++;
                        letter->current_post_id = connected->id;
                        redirected = 1;

                        char message[100];
                        snprintf(message, sizeof(message), "Letter %d redirected to office %d", letter->id, connected->id);
                        log_event(system, message);
                    }
                }

                if (!redirected){
                    letter->state = UNDELIVERED;
                    char message[100];
                    snprintf(message, sizeof(message), "Letter %d marked as undelivered - no route", letter->id);
                    log_event(system, message);
                }
            }
        }
    }

    delete_heap(&office->letter_queue);
    free(office->connected_ids);

    for (int i = office_index; i < system->office_count -1; i++){
        system->offices[i] = system->offices[i + 1];
    }
    system->office_count--;

    char message[100];
    snprintf(message, sizeof(message), "Removed post office %d", id);
    log_event(system, message);
    
    return 1;
}

int add_letter(PostSystem *system, LetterType type, int priority, int from_post_id, int to_post_id, const char *tech_data){
    if (!system || !find_office_by_id(system, from_post_id) || !find_office_by_id(system, to_post_id)){
        return 0;
    }

    if (system->letter_count >= system->letters_capacity) {
        system->letters_capacity *= 2;
        Letter *new_letters = realloc(system->letters, system->letters_capacity * sizeof(Letter));
        if (!new_letters) return 0;
        system->letters = new_letters;
    }

     Letter *letter = &system->letters[system->letter_count];
    letter->id = system->next_letter_id++;
    letter->type = type;
    letter->state = IN_TRANSIT;
    letter->priority = priority;
    letter->from_post_id = from_post_id;
    letter->to_post_id = to_post_id;
    letter->current_post_id = from_post_id;
    if (tech_data) {
        strncpy(letter->tech_data, tech_data, sizeof(letter->tech_data) - 1);
        letter->tech_data[sizeof(letter->tech_data) - 1] = '\0';
    } else {
        letter->tech_data[0] = '\0';
    }
    
    system->letter_count++;

     PostOffice *from_office = find_office_by_id(system, from_post_id);
    if (from_office->current_load < from_office->max_capacity) {
        push_heap(&from_office->letter_queue, letter->id);
        from_office->current_load++;
        
        char message[150];
        snprintf(message, sizeof(message), "Added letter %d from office %d to office %d (priority: %d)", 
                letter->id, from_post_id, to_post_id, priority);
        log_event(system, message);
        
        return letter->id;
    } else {
        letter->state = UNDELIVERED;
        char message[100];
        snprintf(message, sizeof(message), "Letter %d undelivered - office %d full", letter->id, from_post_id);
        log_event(system, message);
        return letter->id;
    }
}

int mark_letter_undeliverable(PostSystem *system, int letter_id) {
    if (!system){
        return 0;
    }
    
    Letter *letter = find_letter_by_id(system, letter_id);
    if (!letter){
        return 0;
    }
    
    letter->state = UNDELIVERED;

    PostOffice *office = find_office_by_id(system, letter->current_post_id);
    if (office && office->current_load > 0) {
        office->current_load--;
    }
    
    char message[100];
    snprintf(message, sizeof(message), "Letter %d marked as undelivered by user", letter_id);
    log_event(system, message);
    
    return 1;
}

int pickup_letter(PostSystem *system, int letter_id) {
    if (!system){
        return 0;
    } 
    
    Letter *letter = find_letter_by_id(system, letter_id);
    if (!letter || letter->state != DELIVERED) {
        return 0;
    }

     int letter_index = -1;
    for (int i = 0; i < system->letter_count; i++) {
        if (system->letters[i].id == letter_id) {
            letter_index = i;
            break;
        }
    }
    if (letter_index == -1){
        return 0;
    }

    for (int i = letter_index; i < system->letter_count - 1; i++) {
        system->letters[i] = system->letters[i + 1];
    }
    system->letter_count--;
    
    char message[100];
    snprintf(message, sizeof(message), "Letter %d picked up from system", letter_id);
    log_event(system, message);
    
    return 1;
}

void process_mail_delivery(PostSystem *system) {
    if (!system) return;

    int *letters_to_process = malloc(system->letter_count * sizeof(int));
    int process_count = 0;

    for (int i = 0; i < system->office_count; i++) {
        PostOffice *office = &system->offices[i];

        Heap temp_queue = create_heap(office->letter_queue.size);
        while (!is_empty_heap(&office->letter_queue)) {
            int letter_id = pop_heap(&office->letter_queue);
            push_heap(&temp_queue, letter_id);
            letters_to_process[process_count++] = letter_id;
        }

        while (!is_empty_heap(&temp_queue)) {
            int letter_id = pop_heap(&temp_queue);
            push_heap(&office->letter_queue, letter_id);
        }
        delete_heap(&temp_queue);
    }

    for (int i = 0; i < process_count; i++) {
        int letter_id = letters_to_process[i];
        Letter *letter = find_letter_by_id(system, letter_id);
        
        if (!letter || letter->state != IN_TRANSIT) {
            continue;
        }
        
        PostOffice *current_office = find_office_by_id(system, letter->current_post_id);
        if (!current_office) {
            continue;
        }

        if (current_office->id == letter->to_post_id) {
            Heap temp_queue = create_heap(current_office->letter_queue.size);
            while (!is_empty_heap(&current_office->letter_queue)) {
                int id = pop_heap(&current_office->letter_queue);
                if (id != letter_id) {
                    push_heap(&temp_queue, id);
                }
            }

            while (!is_empty_heap(&temp_queue)) {
                int id = pop_heap(&temp_queue);
                push_heap(&current_office->letter_queue, id);
            }
            delete_heap(&temp_queue);
            
            current_office->current_load--;
            letter->state = DELIVERED;
            
            char message[100];
            snprintf(message, sizeof(message), "Letter %d delivered to office %d", letter_id, current_office->id);
            log_event(system, message);
            continue;
        }

        int next_office_id = -1;
        PostOffice *target_office = find_office_by_id(system, letter->to_post_id);
        int is_connected_to_target = 0;

        for (int k = 0; k < current_office->connected_count; k++) {
            if (current_office->connected_ids[k] == letter->to_post_id) {
                is_connected_to_target = 1;
                break;
            }
        }

        if (is_connected_to_target && target_office && 
            target_office->current_load < target_office->max_capacity) {
            next_office_id = letter->to_post_id;
        }

        else {
            for (int k = 0; k < current_office->connected_count; k++) {
                PostOffice *connected = find_office_by_id(system, current_office->connected_ids[k]);
                if (connected && connected->current_load < connected->max_capacity) {
                    next_office_id = connected->id;
                    break;
                }
            }
        }

        if (next_office_id != -1) {
            Heap temp_queue = create_heap(current_office->letter_queue.size);
            while (!is_empty_heap(&current_office->letter_queue)) {
                int id = pop_heap(&current_office->letter_queue);
                if (id != letter_id) {
                    push_heap(&temp_queue, id);
                }
            }

            while (!is_empty_heap(&temp_queue)) {
                int id = pop_heap(&temp_queue);
                push_heap(&current_office->letter_queue, id);
            }
            delete_heap(&temp_queue);
            
            current_office->current_load--;

            PostOffice *next_office = find_office_by_id(system, next_office_id);
            push_heap(&next_office->letter_queue, letter_id);
            next_office->current_load++;
            letter->current_post_id = next_office_id;
            
            char message[100];
            snprintf(message, sizeof(message), "Letter %d moved from office %d to office %d", 
                    letter_id, current_office->id, next_office_id);
            log_event(system, message);
        } 
        else {
            letter->state = UNDELIVERED;
            
            char message[100];
            snprintf(message, sizeof(message), "Letter %d undelivered - no route from office %d", 
                    letter_id, current_office->id);
            log_event(system, message);
        }
    }
    
    free(letters_to_process);
}

void print_all_letters(const PostSystem *system, const char *filename) {
    if (!system || !filename) {
        return;
    }
    
    FILE *file = fopen(filename, "w");
    if (!file) {
        return;
    }
    
    fprintf(file, "=== ALL LETTERS IN SYSTEM ===\n");
    fprintf(file, "ID\tType\t\tState\t\tPriority\tFrom\tTo\tCurrent\tTech Data\n");
    fprintf(file, "-----------------------------------------------------------------------------------------\n");
    
    for (int i = 0; i < system->letter_count; i++) {
        const Letter *letter = &system->letters[i];
        
        const char *type_str = (letter->type == REGULAR) ? "Regular" : "Urgent";
        
        const char *state_str;
        switch (letter->state) {
            case IN_TRANSIT: state_str = "In Transit"; break;
            case DELIVERED: state_str = "Delivered"; break;
            case UNDELIVERED: state_str = "Undelivered"; break;
            default: state_str = "Unknown";
        }
        
        fprintf(file, "%-3d\t%-10s\t%-12s\t%-8d\t%-4d\t%-4d\t%-7d\t%s\n",
                letter->id, type_str, state_str, letter->priority,
                letter->from_post_id, letter->to_post_id, 
                letter->current_post_id, letter->tech_data);
    }
    
    fclose(file);
    
    char message[100];
    snprintf(message, sizeof(message), "All letters printed to %s", filename);
    log_event(system, message);
}