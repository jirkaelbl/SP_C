#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "error_messages.h"
#include "stack.h"
#include "parser.h"
#include "operator.h"
#include "calculator.h"
#include "ps_maker.h"

#define MAX_LENGTH 256


void free_memory(char **object) {

    if (!object || !*object) {
        return;
    }

    free(*object);
    *object = NULL;

}


int main(int argc, char *argv[]) {

    int message_result = 1;

    char *prvni_parametr_vzorec = NULL, *druhy_parametr_vzorec = NULL, *treti_parametr_vzorec = NULL;

    char postfix_notace[MAX_LENGTH];

    double y = 0.0;
    
    FILE *soubor;

    double max_x_limit, min_x_limit, max_y_limit, min_y_limit;


    /**
     * OVĚŘENÍ A PŘIJÍMANÍ PARAMTERŮ Z PŘÍKAZOVÉ ŘÁDKY A JEJICH ULOŽENÍ (VZOREC, SOUBOR, LIMITY)
     */

    switch (argc) {
        case 3:

            #define FREE_PARAMETRES                   \
                free_memory(&prvni_parametr_vzorec);  \
                free_memory(&druhy_parametr_vzorec);  \
            

            accept_argument(&prvni_parametr_vzorec, argv[1]);
            accept_argument(&druhy_parametr_vzorec, argv[2]);

            /* TODO: v parseru vyřešit uložení vzorce */
            if (!infix_to_rpn(prvni_parametr_vzorec, postfix_notace)) {
                FREE_PARAMETRES;
                spatny_vzorecek(&message_result);
                return message_result;
            }

            if (vytvor_soubor(&soubor, druhy_parametr_vzorec) == 0) {
                FREE_PARAMETRES;
                spatny_vystupni_soubor(&message_result);
                return message_result;
            }

            if (!nacti_limity_defaultne(&max_x_limit, &min_x_limit, &max_y_limit, &min_y_limit)) {
                FREE_PARAMETRES;
                selhalo_defaultni_nacteni_limit(&message_result);
                return message_result;
            }

            FREE_PARAMETRES;

            #undef FREE_PARAMETRES

            break;

        case 4:

            #define FREE_PARAMETRES                   \
                free_memory(&prvni_parametr_vzorec);  \
                free_memory(&druhy_parametr_vzorec);  \
                free_memory(&treti_parametr_vzorec);  \


            accept_argument(&prvni_parametr_vzorec, argv[1]);
            accept_argument(&druhy_parametr_vzorec, argv[2]);
            accept_argument(&treti_parametr_vzorec, argv[3]);

            /* TODO: v parseru vyřešit uložení vzorce */
            if (!infix_to_rpn(prvni_parametr_vzorec, postfix_notace)) {
                FREE_PARAMETRES;
                spatny_vzorecek(&message_result);
                return message_result;
            }


            if (vytvor_soubor(&soubor, druhy_parametr_vzorec) == 0) {
                FREE_PARAMETRES;
                spatny_vystupni_soubor(&message_result);
                return message_result;
            }

            if (nacti_limity(treti_parametr_vzorec, &max_x_limit, &min_x_limit, &max_y_limit, &min_y_limit) == 0) {
                FREE_PARAMETRES;
                spatny_rozsah(&message_result);
                return message_result;
            }   

            FREE_PARAMETRES;

            #undef FREE_PARAMETRES

            break;
        default:
            nespravne_parametry(&message_result);
            return message_result;
    }


    /**
     * VÝPOČET HODNOTY Y V CYKLU A NÁSLEDNÉ ZAZNAMENÁNÍ DO POSTSCRIPT SOUBORU
     */

    printf("%s\n", postfix_notace);

    if (!vypocet_vzorce(&y, postfix_notace)) {

        spatny_vzorecek(&message_result);
        return message_result;

    }
    


    printf("Limity: %f:%f:%f:%f\n", max_x_limit, min_x_limit, max_y_limit, min_y_limit);
    printf("%s\n", postfix_notace);
    printf("%f\n", y);


















    spravne(&message_result);

    return message_result;

}

