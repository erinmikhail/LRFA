#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "vector.h"

VECTOR_TYPE CopyFunc(VECTOR_TYPE value) {
    return value;
}

void DeleteFunc(VECTOR_TYPE value) {
    (void)value;
}

void print_vector(const Vector* vec) {
    printf("Vector [size: %zu, capacity: %zu]: ", vec->size, vec->capacity);
    for (size_t i = 0; i < vec->size; i++) {
        void* value_ptr = get_at_vector(vec, i);
        int value = *(int*)value_ptr;  
        printf("%d ", value);
    }
    printf("\n");
}

void print_menu() {
    printf("\n=== Vector Operations (void* type) ===\n");
    printf("1.  Create new vector\n");
    printf("2.  Push back element\n");
    printf("3.  Get element by index\n");
    printf("4.  Delete element by index\n");
    printf("5.  Print vector\n");
    printf("6.  Compare two vectors\n");
    printf("7.  Copy vector\n");
    printf("8.  Create new copy of vector\n");
    printf("9.  Erase vector contents\n");
    printf("10. Delete vector\n");
    printf("0.  Exit\n");
    printf("Choose: ");
}

int main() {
    Vector vec1, vec2, *vec_copy = NULL;
    int choice, value;
    size_t index;
    int initialized1 = 0, initialized2 = 0;
    
    printf("=== Dynamic Vector Demo ===\n");
    printf("Vector type: void* (storing int* pointers)\n\n");
    
    while (1) {
        print_menu();
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }
        
        switch (choice) {
            case 0:
                printf("Exiting...\n");
                if (initialized1) erase_vector(&vec1);
                if (initialized2) erase_vector(&vec2);
                if (vec_copy) delete_vector(vec_copy);
                return 0;
                
            case 1: {
                size_t capacity;
                printf("Enter initial capacity: ");
                scanf("%zu", &capacity);
                vec1 = create_vector(capacity, CopyFunc, DeleteFunc);
                initialized1 = 1;
                printf("Vector created successfully!\n");
                break;
            }
            
            case 2:
                if (!initialized1) {
                    printf("Error: Create vector first (option 1)!\n");
                    break;
                }
                printf("Enter integer value to push: ");
                scanf("%d", &value);
                
                int* value_ptr = malloc(sizeof(int));
                *value_ptr = value;
                push_back_vector(&vec1, value_ptr);
                
                printf("Value %d added to vector\n", value);
                break;
                
            case 3:
                if (!initialized1) {
                    printf("Error: Create vector first (option 1)!\n");
                    break;
                }
                printf("Enter index: ");
                scanf("%zu", &index);
                if (index >= vec1.size) {
                    printf("Error: Invalid index! Valid range: 0 to %zu\n", vec1.size - 1);
                } else {
                    void* elem_ptr = get_at_vector(&vec1, index);
                    int elem = *(int*)elem_ptr;
                    printf("Element at index %zu: %d\n", index, elem);
                }
                break;
                
            case 4:
                if (!initialized1) {
                    printf("Error: Create vector first (option 1)!\n");
                    break;
                }
                printf("Enter index to delete: ");
                scanf("%zu", &index);
                if (index >= vec1.size) {
                    printf("Error: Invalid index! Valid range: 0 to %zu\n", vec1.size - 1);
                } else {
                    delete_at_vector(&vec1, index);
                    printf("Element at index %zu deleted\n", index);
                }
                break;
                
            case 5:
                if (!initialized1) {
                    printf("Error: Create vector first (option 1)!\n");
                    break;
                }
                print_vector(&vec1);
                break;
                
            case 6:
                if (!initialized1 || !initialized2) {
                    printf("Error: Both vectors must be created!\n");
                    printf("Use option 1 for first vector and option 7 to create second\n");
                    break;
                }
                if (is_equal_vector(&vec1, &vec2)) {
                    printf("Vectors are EQUAL\n");
                } else {
                    printf("Vectors are NOT equal\n");
                }
                break;
                
            case 7:
                if (!initialized1) {
                    printf("Error: Create first vector first!\n");
                    break;
                }
                if (!initialized2) {
                    vec2 = create_vector(1, CopyFunc, DeleteFunc);
                    initialized2 = 1;
                }
                copy_vector(&vec2, &vec1);
                printf("Vector 1 copied to Vector 2\n");
                break;
                
            case 8:
                if (!initialized1) {
                    printf("Error: Create vector first!\n");
                    break;
                }
                if (vec_copy) {
                    delete_vector(vec_copy);
                }
                vec_copy = copy_vector_new(&vec1);
                printf("New vector copy created in heap\n");
                break;
                
            case 9:
                if (!initialized1) {
                    printf("Error: Create vector first!\n");
                    break;
                }
                erase_vector(&vec1);
                printf("Vector contents erased\n");
                break;
                
            case 10:
                if (!initialized1) {
                    printf("Error: Create vector first!\n");
                    break;
                }
                erase_vector(&vec1);
                initialized1 = 0;
                printf("Vector deleted\n");
                break;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}