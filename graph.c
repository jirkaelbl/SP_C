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
#define EPSILON 1e-9

static int are_equal(double a, double b) {
    return fabs(a - b) < EPSILON;
}

static int delete_array(double *** array, int i) {

    int j;

    if (!array || !*array || !**array) {
        return 0;
    }

    for (j = 0; j < i; j++) {
            free((*array)[j]);
        }
    free(*array);
    return 1;

}

static int prepare_array(double ***array, int length_of_array) {

    int i, j;

    if (length_of_array == 0) {
        return 0;
    }

    *array = (double **)malloc(length_of_array * sizeof(double *));
    if (*array == NULL) {
        return 0;
    }

    for (i = 0; i < length_of_array; i++) {
        (*array)[i] = (double *)malloc(2 * sizeof(double));
        if ((*array)[i] == NULL) {
            
            delete_array(array, i);
            return 0;

        }
    }

    return 1;

}

static void free_memory(char **object) {

    if (!object || !*object) {
        return;
    }

    free(*object);
    *object = NULL;

}


int main(int argc, char *argv[]) {

    int message_result = 1;
    int i = 0, j;

    char *prvni_parametr_vzorec = NULL, *druhy_parametr_vzorec = NULL, *treti_parametr_vzorec = NULL;
    char *title_of_file = NULL;

    char postfix_notace[MAX_LENGTH];

    double y = 0.0;
    double x;

    int length_of_array;
    double **array = NULL;
    
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

            if (!nacti_limity_defaultne(&max_x_limit, &min_x_limit, &max_y_limit, &min_y_limit)) {
                FREE_PARAMETRES;
                selhalo_defaultni_nacteni_limit(&message_result);
                return message_result;
            }

            accept_argument(&title_of_file, druhy_parametr_vzorec);

            if (vytvor_soubor(&soubor, druhy_parametr_vzorec, min_x_limit, max_x_limit, min_y_limit, max_y_limit) == 0) {
                FREE_PARAMETRES;
                spatny_vystupni_soubor(&message_result);
                return message_result;
            }

            if (!make_shorter_infix(prvni_parametr_vzorec)) {
                FREE_PARAMETRES;
                delete_file(&soubor, title_of_file);
                spatny_vzorecek(&message_result);
                return message_result;
            }

            if (!infix_to_rpn(prvni_parametr_vzorec, postfix_notace)) {
                FREE_PARAMETRES;
                delete_file(&soubor, title_of_file);
                spatny_vzorecek(&message_result);
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

            if (nacti_limity(treti_parametr_vzorec, &max_x_limit, &min_x_limit, &max_y_limit, &min_y_limit) == 0) {
                FREE_PARAMETRES;
                spatny_rozsah(&message_result);
                return message_result;
            }

            if (are_equal(min_x_limit, -0.0)) {
                min_x_limit = 0.0;
            }

            if (are_equal(max_x_limit, -0.0)) {
                max_x_limit = 0.0;
            }

            if (are_equal(min_y_limit, -0.0)) {
                min_y_limit = 0.0;
            }

            if (are_equal(max_y_limit, -0.0)) {
                max_y_limit = 0.0;
            }

            accept_argument(&title_of_file, druhy_parametr_vzorec);

            if (vytvor_soubor(&soubor, druhy_parametr_vzorec, min_x_limit, max_x_limit, min_y_limit, max_y_limit) == 0) {
                FREE_PARAMETRES;
                spatny_vystupni_soubor(&message_result);
                return message_result;
            }

            if (!make_shorter_infix(prvni_parametr_vzorec)) {
                FREE_PARAMETRES;
                delete_file(&soubor, title_of_file);
                spatny_vzorecek(&message_result);
                return message_result;
            }   

            if (!infix_to_rpn(prvni_parametr_vzorec, postfix_notace)) {
                FREE_PARAMETRES;
                delete_file(&soubor, title_of_file);
                spatny_vzorecek(&message_result);
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


    /*x = 1.0;

    if (!vypocet_vzorce(&y, &x, postfix_notace)) {
            spatny_vzorecek(&message_result);
            return message_result;

    }*/

    length_of_array = fabs(max_x_limit - min_x_limit) * 10000 + 2;

    if (!prepare_array(&array, length_of_array)) {
        delete_file(&soubor, title_of_file);
        other_error(&message_result);
        return message_result;

    }

    x = min_x_limit;

    if (are_equal(x, -0.0)) {
            x = 0.0;
        }

        if (!vypocet_vzorce(&y, &x, postfix_notace)) {
            delete_array(&array, length_of_array);
            delete_file(&soubor, title_of_file);
            spatny_vzorecek(&message_result);
            return message_result;

        }

        if (isnan(y)) {
            delete_array(&array, length_of_array);
            delete_file(&soubor, title_of_file);
            nan_number(&message_result);
            return message_result;

        }


        if (i < length_of_array) {
           array[i][0] = x;
           array[i][1] = y; 
        }
        
        ++i;

/*0001*/
    for (x = min_x_limit; x <= max_x_limit; x = x + 0.0001) {        

        if (are_equal(x, -0.0)) {
            x = 0.0;
        }

        if (!vypocet_vzorce(&y, &x, postfix_notace)) {
            delete_array(&array, length_of_array);
            delete_file(&soubor, title_of_file);
            spatny_vzorecek(&message_result);
            return message_result;

        }

        if (isnan(y)) {
            delete_array(&array, length_of_array);
            delete_file(&soubor, title_of_file);
            nan_number(&message_result);
            return message_result;

        }


        if (i < length_of_array) {
           array[i][0] = x;
           array[i][1] = y; 
        }
        
        ++i;
 
    }

    x = max_x_limit;

    if (are_equal(x, -0.0)) {
            x = 0.0;
        }

        if (!vypocet_vzorce(&y, &x, postfix_notace)) {
            delete_array(&array, length_of_array);
            delete_file(&soubor, title_of_file);
            spatny_vzorecek(&message_result);
            return message_result;

        }

        if (isnan(y)) {
            delete_array(&array, length_of_array);
            delete_file(&soubor, title_of_file);
            nan_number(&message_result);
            return message_result;

        }


        if (i < length_of_array) {
           array[i][0] = x;
           array[i][1] = y; 
        }
        
        ++i;
    

    if (!draw_graph(title_of_file, array, length_of_array, min_x_limit, max_x_limit, min_y_limit, max_y_limit)) {
        delete_array(&array, length_of_array);
        delete_file(&soubor, title_of_file);
        other_error(&message_result);
        return message_result;
    }


    printf("Limity: %f:%f:%f:%f\n", min_x_limit, max_x_limit, min_y_limit, max_y_limit);
    printf("%s\n", postfix_notace);
    printf("Výsledek: %f\n", y);    


    /*printf("Hodnoty v poli:\n");
    for ( i = 0; i < length_of_array; i++) {
        for ( j = 0; j < 2; j++) {
            printf("array[%d][%d] = %.2f\n", i, j, array[i][j]);
        }
    }*/











    free_memory(&title_of_file);
    delete_array(&array, length_of_array);

    spravne(&message_result);

    return message_result;

}

