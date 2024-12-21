#include "error_messages.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void spravne(int *message_result) {

    if (!message_result) {
        return;
    }

    *message_result = 0;

    printf("No error/correct termination of the program.\n");

}

void nespravne_parametry(int *message_result) {

    if (!message_result) {
        return;
    }

    *message_result = 1;
    
    printf("The correct parameters were not passed to the command line when the program was started.\n\n");

    printf("Manual:\n\n");

    printf("Usage:\n   graph.exe <func> <out-file> [<limits>]\n\n");
    printf("Example:\n   graph.exe \"sin(2*x)ˆ3\" mygraph.ps 10:20:74:5\n\n");
    printf("Parametrs meaning are:\n");
    printf("   <func> .... mathematical function (you can ad it in \"\" with spaces between parts of function or without \"\" with no spaces\n");
    printf("   <out-file> .... file with PostScript code that draws you mathematical function into the graph\n");
    printf("   [<limits>] .... borders of graph with your mathematical function\n");

}

void spatny_vzorecek(int *message_result) {

    if (!message_result) {
        return;
    }

    *message_result = 2;
    
    printf("The string passed to the program as the first parameter is not an acceptable notation of a mathematical function (it does not contain just one variable x, it contains illegal operators, symbols, etc.).\n");

}

void spatny_vystupni_soubor(int *message_result) {

    if (!message_result) {
        return;
    }

    *message_result = 3;
    
    printf("The string passed to the program as the second parameter cannot be a file name in the host operating system, or such a file cannot be created or have information stored in it.\n");

}

void spatny_rozsah(int *message_result) {

    if (!message_result) {
        return;
    }

    *message_result = 4;
    
    printf("The optional third parameter cannot be decoded as display ranges because it contains illegal characters or the values do not make sense, etc.\n");

}

void selhalo_defaultni_nacteni_limit(int *message_result) {

    if (!message_result) {
        return;
    }

    *message_result = 6;
    
    printf("The default limit setting failed.\n");

}

void nan_number(int *message_result) {

    if (!message_result) {
        return;
    }

    *message_result = 9;

    printf("Result of an example is NAN.\n");

}

void other_error(int *message_result) {

    if (!message_result) {
        return;
    }

    *message_result = 10;

    printf("There is other error.\n");

}

