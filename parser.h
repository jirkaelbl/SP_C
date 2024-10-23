#include <stdio.h>
#ifndef PARSER_H
#define PARSER_H

int nacti_limity(char *argument, float *max_x, float *min_x, float *max_y, float *min_y);

void nacti_limity_defaultne(float *max_x, float *min_x, float *max_y, float *min_y);

int vytvor_soubor(FILE **soubor, char *argument);

#endif