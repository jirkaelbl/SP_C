#include "stack.h"

#ifndef PARSER_H
#define PARSER_H

void accept_argument (char **parametr, char *argument);

int nacti_limity(char *argument, double *max_x, double *min_x, double *max_y, double *min_y);

int nacti_limity_defaultne(double *max_x, double *min_x, double *max_y, double *min_y);

int vytvor_soubor(FILE **soubor, char *argument);

int infix_to_rpn(char *infix, char *postfix);

#endif