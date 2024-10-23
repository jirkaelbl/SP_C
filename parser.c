#include "parser.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int je_cislo(const char *str) {

    char *endptr;

    if(!str) {
        return 0;
    }
    
    strtod(str, &endptr);

    return *endptr == '\0';
}

int nacti_limity(char *argument, float *max_x, float *min_x, float *max_y, float *min_y) {

    char *token;
    int count = 0;

    if(!argument || !max_x || !min_x || !max_y || !min_y) {
        return 0;
    }

    token = strtok(argument, ":");
    if (token != NULL && je_cislo(token)) {
        *max_x = (float) strtod(token, NULL);
        count++;
    } else {
        printf("Chyba: max_x není platné číslo.\n");
        return 0;
    }

    token = strtok(NULL, ":");
    if (token != NULL && je_cislo(token)) {
        *min_x = (float) strtod(token, NULL);
        count++;
    } else {
        printf("Chyba: min_x není platné číslo.\n");
        return 0;
    }

    token = strtok(NULL, ":");
    if (token != NULL && je_cislo(token)) {
        *max_y = (float) strtod(token, NULL);
        count++;
    } else {
        printf("Chyba: max_y není platné číslo.\n");
        return 0;
    }

    token = strtok(NULL, ":");
    if (token != NULL && je_cislo(token)) {
        *min_y = (float) strtod(token, NULL);
        count++;
    } else {
        printf("Chyba: min_y není platné číslo.\n");
        return 0;
    }

    if (strtok(NULL, ":") != NULL) {
        printf("Chyba: argument obsahuje více než 4 hodnoty.\n");
        return 0;
    }

    return count == 4;

}

void nacti_limity_defaultne(float *max_x, float *min_x, float *max_y, float *min_y) {

    if (!max_x || !min_x || !max_y || !min_y) {
        return;
    }

    *max_x = 10.0;
    *min_x = 10.0;
    *max_y = 10.0;
    *min_y = 10.0;
}

int vytvor_soubor(FILE **soubor, char *argument) {

    char cely_nazev[100];
    char *nazev_jmeno;
    char *nazev_pripona;
    char *token;
    int count = 0;

    if (!soubor || !argument) {
        return 0;
    }

    token = strtok(argument, ".");
    if (token != NULL) {
        nazev_jmeno = token;
        count++;
    } else {
        return 0;
    }

    token = strtok(NULL, ".");
    if (token != NULL && strcmp(token, "ps") == 0) {
        nazev_pripona = token;
        count++;
    } else {
        return 0;
    }

    if (strtok(NULL, ".") != NULL) {
        return 0;
    }

    sprintf(cely_nazev, "%s.%s", nazev_jmeno, nazev_pripona);

    *soubor = fopen(cely_nazev, "w");

    if (!*soubor) {
        printf("Chyba při vytváření souboru!\n");
        return 0;
    }

    fclose(*soubor);

    return count == 2;
}

