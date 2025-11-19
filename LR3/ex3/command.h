#ifndef COMMANDS_H
#define COMMANDS_H

#include "list.h"

#define MAX_MODIFICATIONS 100

typedef enum {
    CMD_ADD,
    CMD_DELETE,
    CMD_MODIFY
} CommandType;

typedef struct {
    CommandType type;
    int index;
    Liver old_data;
    Liver new_data;
} Modification;

typedef struct {
    Modification modifications[MAX_MODIFICATIONS];
    int count;
    int current_index;
} CommandHistory;

void init_command_history(CommandHistory* history);
void add_modification(CommandHistory* history, Modification mod);
void undo_last_modifications(CommandHistory* history, LinkedList* list, int count);

#endif