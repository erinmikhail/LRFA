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


// вспомогтательные функции для работы посикс
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
            return (PostOffice*)&system->letters[i];
        }
    }

    return NULL;
}

// упр отдел
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
    snprintf(message, sizeof(message), "added post office %d eith capacity %d", id, max_capacity);
    log_event(system,message);

    return 1;
}

int remove_post_office(PostSystem *system, int id){
    if (!system){
        return 0;
    }

    
}