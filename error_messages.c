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
    
    printf("Nebyly předány správné parametry na příkazové řádce při spuštění programu.\n\n");

    printf("Manual:\n\n");

    printf("Usage:\n   graph.exe <func> <out-file> [<limits>]\n\n");
    printf("Example:\n   graph.exe \"sin(2*x)ˆ3\" mygraph.ps 10:20:74:5\n\n");
    printf("Parametrs meaning are:\n");
    printf("   <func> .... mathematical function (you can ad it in \"\" with spaces between parts of function or without \"\" with no spaces\n");
    printf("   <out-file> .... file with PostScript code that draws you mathematical function into the graph\n");
    printf("   [<limits>] .... borders of graph with your mathematical function\n");

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

void selhalo_defaultni_nacteni_limit(int *message_result) {

    if(!message_result) {
        return;
    }

    *message_result = 6;
    
    printf("Selhalo defaultní naštění limit.\n");

}