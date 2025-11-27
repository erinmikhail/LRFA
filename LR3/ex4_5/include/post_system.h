#ifndef POST_SYSTEM_H
#define POST_SYSTEM_H

#include "heap.h"
#include <time.h>

typedef enum{
    IN_TRANSIT,
    DELIVERED,
    UNDELIVERED
} LetterState;

typedef enum{
    REGULAR,
    URGENT
} LetterType;

typedef struct{
    int id;
    LetterType type;
    LetterState state;
    int priority;
    int from_post_id;
    int to_post_id;
    char tech_data[100];
    int current_post_id;
}Letter;

typedef struct{
    int id;
    int max_capacity;
    Heap letter_queue;
    int *connected_ids;
    int connected_count;
    int current_load;
} PostOffice;

typedef struct{
    PostOffice *offices;
    Letter *letters;
    int office_count;
    int letter_count;
    int offices_capacity;
    int letters_capacity;
    int next_letter_id;
    char log_filename[100];
}PostSystem;

PostSystem* create_post_system(const char *log_filename);
void delete_post_system(PostSystem *system);

int add_post_office(PostSystem *system, int id, int max_capacity, const int *connected_ids, int connected_count);
int remove_post_office(PostSystem *system, int id);

int add_letter(PostSystem *system, LetterType type, int priority, int from_post_id, int to_post_id, const char *tech_data);
int mark_letter_undeliverable(PostSystem *system, int letter_id);
int pickup_letter(PostSystem *system, int letter_id);

void process_mail_delivery(PostSystem *system);

PostOffice* find_office_by_id(const PostSystem *system, int id);
Letter* find_letter_by_id(const PostSystem *system, int id);
void log_event(const PostSystem *system, const char *message);

void print_all_letters(const PostSystem *system, const char *filename);
#endif