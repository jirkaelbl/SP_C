#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "parser.h"
#include "stack.h"

#define MAX_LENGTH 256

void accept_argument (char **parametr, char *argument) {

    *parametr = malloc(MAX_LENGTH * sizeof(char));
    if (*parametr == NULL) {
        printf("Chyba: Alokace paměti selhala.\n");
        exit(1);
    }

    strncpy(*parametr, argument, MAX_LENGTH);


}

static int je_cislo(const char *str) {

    char *endptr;

    if(!str) {
        return 0;
    }
    
    strtod(str, &endptr);

    return *endptr == '\0';
}

int nacti_limity(char *argument, double *max_x, double *min_x, double *max_y, double *min_y) {

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

int nacti_limity_defaultne(double *max_x, double *min_x, double *max_y, double *min_y) {

    if (!max_x || !min_x || !max_y || !min_y) {
        return 0;
    }

    *max_x = 10.0;
    *min_x = 10.0;
    *max_y = 10.0;
    *min_y = 10.0;

    return 1;
}

static int priorita(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '_') return 3;
    if (op == '^') return 4;
    return 0;
}

static int je_operator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '_';
}

static int make_shorter_infix(char *infix) {
    char shorter_infix[MAX_LENGTH];
    size_t i = 0, a = 0, b = 0, c = 0;
    int j = 0;
    int counter = 0;
    int uzaver_E = 0;
    int cislo_pred = 0, tecka = 0, cislo_po = 0;
    char digits_after_dot_in_E_expresion[MAX_LENGTH];
    char digits_before_E_in_expresion[MAX_LENGTH];

    if (!infix) {
        
        return 0;
    }

    if (!bracket_control(infix)) {
        return 0;
    }

    while (infix[i] != '\0') {
        if (infix[i] == ' ') {
            i++;
            continue;
        }

        shorter_infix[j++] = infix[i++];
    }
    
    shorter_infix[j] = '\0';

    strcpy(infix, shorter_infix);


    do {
        counter = 0;
        i = 0;
        j = 0;

        shorter_infix[0] = '\0';

        while (infix[i] != '\0') {
            
            if ((infix[i] == '+' && infix[i + 1] == '+') || (infix[i] == '-' && infix[i + 1] == '-')) {

                shorter_infix[j++] = '+';
                counter++;
                i += 2;

            } else if ((infix[i] == '+' && infix[i + 1] == '-') || (infix[i] == '-' && infix[i + 1] == '+')) {

                shorter_infix[j++] = '-';
                counter++;
                i += 2;

            } else if (infix[i] == '+' && (je_operator(infix[i-1]) || je_operator(infix[i+1]))) {

                shorter_infix[j++] = ' ';
                counter++;
                ++i;

            } else if (infix[i] == ' ') {
                i++;
            } else {

                shorter_infix[j++] = infix[i++];

            }
        }

        shorter_infix[j] = '\0';

        
        strcpy(infix, shorter_infix);

    } while (counter > 0);

    

    shorter_infix[j] = '\0';

    strcpy(infix, shorter_infix);

    do {
        counter = 0;
        i = 0;
        j = 0;

        shorter_infix[0] = '\0';

        while (infix[i] != '\0') {
            
            if (infix[i] == 'E') {

                uzaver_E = 1;

                a = i + 1;

                

                
                if (infix[a] != '+' && infix[a] != '-' && !isdigit(infix[a])) {

                    return 0;

                }

                if (infix[a] == '+' || infix[a] == '-') {

                    uzaver_E = 2;
                }
                
                while (infix[a] != '\0' && !je_operator(infix[a])) {

                    /*if (!isdigit(infix[a]) && infix[a] != '+' && infix[a] != '-') {

                        return 0;

                    }*/


                    ++a;

                }


                a = 0;
                cislo_pred = 0;
                tecka = 0;
                cislo_po = 0;

                if (i != 0 && !je_operator(infix[i-1])) {

                    j = j - 1;
                    a = j;
                    while (!je_operator(shorter_infix[j])) {

                        if (shorter_infix[j] == ')'){

                            return 0;

                        }

                        if (j != 0) {
                            --j;
                        } else {
                            break;
                        }
                    }

                    if (je_operator(shorter_infix[j])) {

                        j = j + 1;

                    }
                            

                    b = j;
                    c = 0;
                    digits_before_E_in_expresion[c++] = '(';


                    while ((size_t)j <= a) {


                    digits_before_E_in_expresion[c++] = shorter_infix[j++];

                    }

                    digits_before_E_in_expresion[c++] = '\0';
                    c = 0;

                    j = b;
                        
                    /*shorter_infix[j++] = '(';*/

                    while (digits_before_E_in_expresion[c] != '\0') {

                        shorter_infix[j++] = digits_before_E_in_expresion[c++];
                    }




                    a = i - 1;


                    while (!je_operator(infix[a]) && a != 0){
                        --a;
                    }


                    while (a < i) {
                        if (isdigit(infix[a]) && tecka == 0) {

                            ++cislo_pred;

                        } else if (infix[a] == '.') {

                            ++tecka;

                        } else if (isdigit(infix[a]) && tecka != 0) {

                            ++cislo_po;
                        }

                        ++a;
                    }


                    if ((cislo_pred != 0 && tecka != 0 && cislo_po != 0) || (cislo_pred != 0 && tecka == 0 && cislo_po == 0)) {


                    } else if (cislo_pred != 0 && tecka != 0 && cislo_po == 0) {
                    
                        shorter_infix[j++] = '0';

                    } else if (cislo_pred == 0 && tecka != 0 && cislo_po == 0) {
                    
                        shorter_infix[j-1] = '0';

                    } else if (cislo_pred == 0 && tecka != 0 && cislo_po != 0) {

                        j = j - 1;
                        a = j;
                        while (!je_operator(shorter_infix[j])) {

                            if (j != 0 && shorter_infix[j] != '(') {
                                --j;
                            } else {
                                break;
                            }
                        }

                        if (je_operator(shorter_infix[j])) {

                            j = j + 1;

                        }
                        

                        b = j;
                        c = 0;
                        while ((size_t)j <= a) {

                            if (shorter_infix[j] == '(') {

                                digits_after_dot_in_E_expresion[c++] = shorter_infix[j++];
                                digits_after_dot_in_E_expresion[c++] = '0';
                                continue;
                           }

                           digits_after_dot_in_E_expresion[c++] = shorter_infix[j++];

                        }

                        digits_after_dot_in_E_expresion[c++] = '\0';
                        c = 0;

                        j = b;
                    
                        /*shorter_infix[j++] = '0';*/

                        while (digits_after_dot_in_E_expresion[c] != '\0') {

                            shorter_infix[j++] = digits_after_dot_in_E_expresion[c++];
                        }

                    } 
                } else {

                    shorter_infix[j++] = '(';
                    shorter_infix[j++] = '1';

                }

                
                shorter_infix[j++] = '*';
                shorter_infix[j++] = '1';
                shorter_infix[j++] = '0';
                shorter_infix[j++] = '^';
                counter++;
                ++i;

            } else if (infix[i] == ' ') {
                i++;
            } else {

                if (uzaver_E == 2) {
                    
                    if (infix[i] == '+'){
                        uzaver_E = 1;
                        ++i;
                        continue;
                    }

                    shorter_infix[j++] = infix[i++];
                    uzaver_E = 1;
                    
                } else if (uzaver_E == 1 && (je_operator(infix[i+1]) || infix[i+1] == '\0' || infix[i+1] == ')')) {
                    
                    shorter_infix[j++] = infix[i++];
                    shorter_infix[j++] = ')';
                    uzaver_E = 0;

                } else {

                    if (uzaver_E == 1 && (!isdigit(infix[i]) || infix[i] == ')')) {
                        return 0;
                    }

                    shorter_infix[j++] = infix[i++];
  
                }

            }
        }

        shorter_infix[j] = '\0';

        
        strcpy(infix, shorter_infix);

    } while (counter > 0);




    return 1;
}

int infix_to_rpn(char *infix, char *postfix) {

    struct stack *s = stack_alloc(MAX_LENGTH, sizeof(char));
    size_t i = 0, j = 0;
    char top;
    char unar_minus = '_';

    int length = 0;
    
    if (!s) {
        return 0;
    }

    if (!infix || !postfix) {
        stack_dealloc(&s);
        return 0;
    }

    printf("%s\n", infix);

    if (!make_shorter_infix(infix)) {
        stack_dealloc(&s);
        return 0;
    }

    printf("%s\n", infix);

    length = strlen(infix);

    if (je_operator(infix[length - 1]) || (!isdigit(infix[0]) && infix[0] != '+' && infix[0] != '-' && infix[0] != '(' && infix[0] != ')')) {
        stack_dealloc(&s);
        return 0;
    }

    while (infix[i] != '\0') {

        /*ošetření případného opakování **, // nebo ^^*/
        if((infix[i] == '*' && infix[i+1] == '*') || (infix[i] == '/' && infix[i+1] == '/')
         || (infix[i] == '^' && infix[i+1] == '^') || (infix[i] == '.' && infix[i+1] == '.')
          || (infix[i] == 'E' && infix[i+1] == 'E')) {
            stack_dealloc(&s);
            return 0;
        }

        /* v této větvi řeším unární mínus */
        if (infix[i] == '-' && (i == 0 || infix[i - 1] == '(' || je_operator(infix[i - 1]))) {


            if (isdigit(infix[i+1])) {
                stack_push(s, &unar_minus); 
            } else if (infix[i+1] == '(') {
                stack_push(s, &unar_minus);
            }
                        
            
            i++;

        } else if (isdigit(infix[i])) {

            while (isdigit(infix[i]) || infix[i] == '.') {

                /* Ošetření desetinných čísel */
                if ( (!isdigit(infix[i-1]) && infix[i] == '.' && isdigit(infix[i+1])) || (isdigit(infix[i-1]) && infix[i] == '.' && !isdigit(infix[i+1])) ) {
                    stack_dealloc(&s);
                    return 0;
                }

                postfix[j++] = infix[i++];

            }

            postfix[j++] = ' ';

        } else if (je_operator(infix[i])) {
                /*printf("%c a %ld\n",infix[i], i);*/
                while (s->sp > 0) {
                stack_pop(s, &top);
                if (priorita(top) >= priorita(infix[i])) {
                    postfix[j++] = top;
                    postfix[j++] = ' ';

                } else {
                    stack_push(s, &top);
                    break;
                }
            }
           
            stack_push(s, &infix[i]);
            i++;

        } else if (infix[i] == '(') {

            stack_push(s, &infix[i]);

            i++;

        } else if (infix[i] == ')') {

            while (stack_pop(s, &top) && top != '(') {
                postfix[j++] = top;
                postfix[j++] = ' ';

                
            }

            if (top != '(') {
                
                /*neuzavrena zavorka*/
                stack_dealloc(&s);
                return 0;
            }
            i++;

        } else if (infix[i] == ' ') {
            
            i++;

        } else {

            /* neplatny znak */
            stack_dealloc(&s);
            return 0; 

        }
    }

    
    while (s->sp > 0) {
        stack_pop(s, &top);
        if (top == '(') {
            
            /*neni uzavřena závorka*/
            stack_dealloc(&s);
            return 0;
        }
        postfix[j++] = top;
        postfix[j++] = ' ';

    }

    postfix[j] = '\0';

    stack_dealloc(&s);

    return 1;
}

