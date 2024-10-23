#ifndef STACK_H
#define STACK_H

struct stack {
    int key;
    struct stack *next;
};


int push(struct stack **root, int value);

int pop(struct stack **root);

void free_stack(struct stack **root);

void top(struct stack *root);

int isStackEmpty(struct stack *root);



#endif