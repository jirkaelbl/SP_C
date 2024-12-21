#ifndef STACK_H
#define STACK_H

#include <stddef.h>


struct stack {

    size_t capacity;
    size_t item_size;
    size_t sp;
    void *items;

};



struct stack *stack_alloc(const size_t capacity, const size_t item_size);


int stack_init(struct stack *s, const size_t capacity, const size_t item_size);


void stack_deinit(struct stack *s);


void stack_dealloc(struct stack **s);


int stack_push(struct stack *s, const void *item);


int stack_pop(struct stack *s, void *item);


int stack_head(const struct stack *s, void *item);


size_t stack_item_count(const struct stack *s);



#endif