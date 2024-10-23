#include "error_messages.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void spravne(int *message_result) {

    if(!message_result) {
        return;
    }

    *message_result = 0;

    printf("Bez chyby/korektní ukončení činnosti programu.\n");

}

void nespravne_parametry(int *message_result) {

    if(!message_result) {
        return;
    }

    *message_result = 1;
    
    printf("Nebyly předány správné parametry na příkazové řádce při spuštění programu.\n");

}

void spatny_vzorecek(int *message_result) {

    if(!message_result) {
        return;
    }

    *message_result = 2;
    
    printf("Řetězec předaný programu jako první parametr není akceptovatelným zápisem matematické funkce (neobsahuje právě jednu proměnnou x, obsahuje nepovolené operátory, symboly, atp.).\n");

}

void spatny_vystupni_soubor(int *message_result) {

    if(!message_result) {
        return;
    }

    *message_result = 3;
    
    printf("Řetězec předaný programu jako druhý parametr nemůže být v hostitelském operačním systému názvem souboru nebo takový soubor nelze vytvořit či do něj ukládat informace.\n");

}

void spatny_rozsah(int *message_result) {

    if(!message_result) {
        return;
    }

    *message_result = 4;
    
    printf("Uvedený nepovinný třetí parametr nelze dekódovat jako rozsahy zobrazení, protože např. obsahuje nepovolené znaky nebo uvedené hodnoty nedávají smysl, apod.\n");

}