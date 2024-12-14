#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "calculator.h"
#include "stack.h"
#include "operator.h"

#ifndef NAN
#define NAN (0.0/0.0)
#endif

#define MAX_LENGTH 256

static int pocet_casti_vypoctu(char *operator) {

    if (!operator) {
        return 0;
    }

    if (*operator == '+' || *operator == '-' || *operator == '*' || *operator == '/' || *operator == '^') return 2;
    if (*operator == '_' || *operator == 'a' || *operator == 'e' || *operator == 'l' || *operator == 'g'
     || *operator == 's' || *operator == 'c' || *operator == 't' || *operator == 'm' || *operator == 'n'
      || *operator == 'b' || *operator == 'h' || *operator == 'j' || *operator == 'k') return 1;
    return 0;
}

int vypocet_vzorce(double *y, /*double x,*/const char *postfix) {

    struct stack *s = stack_alloc(MAX_LENGTH, sizeof(double));
    char *token;
    char expr_copy[MAX_LENGTH];
    double a, b;
    strncpy(expr_copy, postfix, MAX_LENGTH);
    token = strtok(expr_copy, " ");

    if (!s) {
        return 0;
    }

    if (!postfix) {
        stack_dealloc(&s);
        return 0;
    }

    

    while (token != NULL) {

        if (sscanf(token, "%lf", y) == 1) {

            stack_push(s, y);

        } else if (pocet_casti_vypoctu(token) == 2) {
            
            stack_pop(s, &b);
            stack_pop(s, &a);
            
            if (make_num_operation(y, token, a, b) == EXIT_FAILURE) {
                
               stack_dealloc(&s);
               return 0;

            }
            stack_push(s, y);

        } else if (pocet_casti_vypoctu(token) == 1) {

            stack_pop(s, &a);

            if (make_num_operation(y, token, a, 0) == EXIT_FAILURE) {
                
                stack_dealloc(&s);
                return 0;

            }
            stack_push(s, y);

        } else if (pocet_casti_vypoctu(token) == 0) {

            stack_dealloc(&s);
            return 0;

        }

        token = strtok(NULL, " ");
    }

    stack_pop(s, y);

    if (stack_item_count(s) != 0) {

        return 0;

    }

    stack_dealloc(&s);
    return 1;
}
