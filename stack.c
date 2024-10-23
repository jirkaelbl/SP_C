#include "stack.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int push(struct stack **root, int value) {

    struct stack *new_part_in_stack;

    if(!root) {
        return 0;
    }

    new_part_in_stack = malloc(sizeof(*new_part_in_stack));
    if (!new_part_in_stack) {
        return 0;
    }

    new_part_in_stack->key = value;

    if(!*root) {
        *root = new_part_in_stack;
        new_part_in_stack->next = NULL;
        return 1;
    }

    new_part_in_stack->next = *root;
    *root = new_part_in_stack;

    return 1;


}

int pop(struct stack **root) {

    struct stack *tmp;
    int returned_value;

    if(!root) {
        return 0;
    }

    if(!*root) {
        return 0;
    }

    tmp = *root;
    returned_value = tmp->key;
    *root = (*root)->next;

    free(tmp);    

    return returned_value;
}

void free_stack(struct stack **root) {

    struct stack *tmp;

    if(!root || !*root) {
        return;
    } 

    while(1) {
        tmp = *root;
        *root = (*root)->next;
        free(tmp);

        if(!*root) {
            break;
        }
    }
}

void top(struct stack *root) {

    if(!root) {
        printf("Zásobník je prázdný.");
        return;
    }

    printf("Vrchní prvek zásobníku: %d\n", root->key);

}

int isStackEmpty(struct stack *root) {

    if(!root) {
        return 1;
    }

    return 0;

}
