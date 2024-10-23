#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error_messages.h"
#include "stack.h"
#include "parser.h"

#define PI = 3.14159265359
#define eul = 2.71828182845904


void accept_argument (char **parametr) {

    *parametr = malloc(100 * sizeof(char));
    if (*parametr == NULL) {
        printf("Chyba: Alokace paměti selhala.\n");
        exit(1);
    }

}


int main(int argc, char *argv[]) {

    int message_result = 1;

    char *prvni_parametr_vzorec = NULL, *druhy_parametr_vzorec = NULL, *treti_parametr_vzorec = NULL;

    long y;

    float max_x_limit, min_x_limit, max_y_limit, min_y_limit;

    struct stack *root = NULL;

    FILE *soubor;


    if (argc < 3 || argc > 4) {
        nespravne_parametry(&message_result);
        return message_result;
    }
    
    accept_argument(&prvni_parametr_vzorec);
    accept_argument(&druhy_parametr_vzorec);


    strncpy(prvni_parametr_vzorec, argv[1], 99);




    if (argc == 3) {
        nacti_limity_defaultne(&max_x_limit, &min_x_limit, &max_y_limit, &min_y_limit);
    }


    if (argc == 4) {

        accept_argument(&treti_parametr_vzorec);
        strncpy(treti_parametr_vzorec, argv[3], 99);

        if (nacti_limity(treti_parametr_vzorec, &max_x_limit, &min_x_limit, &max_y_limit, &min_y_limit) == 0) {

            free(treti_parametr_vzorec);
            spatny_rozsah(&message_result);
            return message_result;

        }
        
    }


    strncpy(druhy_parametr_vzorec, argv[2], 99);

    if (vytvor_soubor(&soubor, druhy_parametr_vzorec) == 0) {
        free(druhy_parametr_vzorec);
        spatny_vystupni_soubor(&message_result);
        return message_result;
    }


    printf("%s\n", prvni_parametr_vzorec);
    printf("%s\n", druhy_parametr_vzorec);
    printf("Limity: %f:%f:%f:%f\n", max_x_limit, min_x_limit, max_y_limit, min_y_limit);















    spravne(&message_result);

    free(prvni_parametr_vzorec);
    free(druhy_parametr_vzorec);
    free(treti_parametr_vzorec); 
    

    return message_result;

}

