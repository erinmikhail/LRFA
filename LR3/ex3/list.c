#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

LinkedList create_list(void){
    LinkedList list;
    list.head = NULL;
    list.tail = NULL;
    list.size = 0;
    return list;
}

void erase_list(LinkedList *list){
    while (list->size > 0){
        pop_frint_list(list);
    }
}
