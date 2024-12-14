#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "ps_maker.h"


int vytvor_soubor(FILE **soubor, char *argument) {

    char cely_nazev[100];
    char *nazev_jmeno;
    char *nazev_pripona;
    char *token;
    int count = 0;


    /*Zde není ověřena existence *soubor, ta bude ze začátku vždy NULL, protoře soubor ještě nebyl vytvořen*/
    if (!soubor || !argument) {
        printf("Chyba při vytváření souboru!\n");
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

    fclose(*soubor);

    return count == 2;
}