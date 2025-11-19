#include "command.h"
#include <stdlib.h>
#include <stdio.h>

void init_command_history(CommandHistory* history){
    history->count = 0;
    history->current_index = 0;
}

void add_modification(CommandHistory *history, Modification mod){
    if (history->current_index < MAX_MODIFICATIONS) {
        history->modifications[history->current_index] = mod;
        history->current_index++;
        history->count = history->current_index;
    } else{
        for (int i = 0; i < MAX_MODIFICATIONS -1; i++){
            history->modifications[i] = history->modifications[i + 1];
        }
        history->modifications[MAX_MODIFICATIONS - 1] = mod;
        history->count = MAX_MODIFICATIONS;
    }
}

void undo_last_modifications(){}