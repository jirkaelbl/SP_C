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
        *min_x = (float) strtod(token, NULL);
        count++;
    } else {
        printf("Chyba: min_x není platné číslo.\n");
        return 0;
    }

    token = strtok(NULL, ":");
    if (token != NULL && je_cislo(token)) {
        *max_x = (float) strtod(token, NULL);
        count++;
    } else {
        printf("Chyba: max_x není platné číslo.\n");
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

    token = strtok(NULL, ":");
    if (token != NULL && je_cislo(token)) {
        *max_y = (float) strtod(token, NULL);
        count++;
    } else {
        printf("Chyba: max_y není platné číslo.\n");
        return 0;
    }

    if (strtok(NULL, ":") != NULL) {
        printf("Chyba: argument obsahuje více než 4 hodnoty.\n");
        return 0;
    }

    if ((*min_x >= *max_x) || (*min_y >= *max_y)) {

        return 0;
        
    }

    return count == 4;

}

int nacti_limity_defaultne(double *max_x, double *min_x, double *max_y, double *min_y) {

    if (!max_x || !min_x || !max_y || !min_y) {
        return 0;
    }

    *max_x = 10.0;
    *min_x = -10.0;
    *max_y = 10.0;
    *min_y = -10.0;

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

static int bracket_control(char *infix) {

    size_t start_bracket_counter = 0, end_bracket_counter = 0, i = 0;

    if (!infix) {
        return 0;
    }

    while (infix[i] != '\0') {

        if (infix[i] == '(') {
            ++start_bracket_counter;
        } else if (infix[i] == ')') {
            ++end_bracket_counter;
        }

        ++i;

    }

    if (start_bracket_counter != end_bracket_counter) {
        return 0;
    }

    return 1;

}

static int dot_resolve(char *infix, char *shorter_infix) {
    size_t i = 0, j = 0;

    if (!infix || !shorter_infix) {
        return 0;
    }

    while (infix[i] != '\0') {

        if ((i == 0 && infix[i] == '.' && isdigit(infix[i+1])) || (infix[i] == '.' && !isdigit(infix[i-1]) && isdigit(infix[i+1]))) {
            shorter_infix[j++] = '0';
            shorter_infix[j++] = infix[i++];
            shorter_infix[j++] = infix[i++];
        } else if (infix[i] == '.' && !isdigit(infix[i+1]) && isdigit(infix[i-1])) {
            shorter_infix[j++] = infix[i++];
            shorter_infix[j++] = '0';
        } else if (infix[i] == '.' && !isdigit(infix[i+1]) && !isdigit(infix[i-1])) {
            shorter_infix[j++] = '0';
            shorter_infix[j++] = infix[i++];
            shorter_infix[j++] = '0';
        } else {
            shorter_infix[j++] = infix[i++];
        }

    }

    shorter_infix[j] = '\0';

    strcpy(infix, shorter_infix);

    return 1;
}

static int functions_parser(char *infix, char *shorter_infix) {
    size_t i = 0, j = 0;

    if (!infix) {
        return 0;
    }

    /*abs, asin, acos, atan, cos, cosh, exp, log, ln, sin, sinh, tan, tanh, */

    while (infix[i] != '\0') {

        switch (infix[i]) {
            case 'a':
                if(infix[i+1] == 'b' && infix[i+2] == 's' && infix[i+3] == '(') {
                    i = i + 3; 
                    shorter_infix[j++] = 'a';
                    continue;
                } else if (infix[i+1] == 's' && infix[i+2] == 'i' && infix[i+3] == 'n' && infix[i+4] == '(') {
                    i = i + 4;
                    shorter_infix[j++] = 'm';
                    continue;
                } else if (infix[i+1] == 'c' && infix[i+2] == 'o' && infix[i+3] == 's' && infix[i+4] == '(') {
                    i = i + 4;
                    shorter_infix[j++] = 'n';
                    continue;
                } else if (infix[i+1] == 't' && infix[i+2] == 'a' && infix[i+3] == 'n' && infix[i+4] == '(') {
                    i = i + 4;
                    shorter_infix[j++] = 'b';
                    continue;
                } else {
                    return 0;
                }
                break;
            case 'c':
                if(infix[i+1] == 'o' && infix[i+2] == 's' && infix[i+3] == '(') {
                    i = i + 3;
                    shorter_infix[j++] = 'c'; 
                    continue;
                } else if (infix[i+1] == 'o' && infix[i+2] == 's' && infix[i+3] == 'h' && infix[i+4] == '(') {
                    i = i + 4;
                    shorter_infix[j++] = 'j';
                    continue;
                } else {
                    return 0;
                }
                break;
            case 'e':
                if(infix[i+1] == 'x' && infix[i+2] == 'p' && infix[i+3] == '(') {
                    i = i + 3;
                    shorter_infix[j++] = 'e'; 
                    continue;
                } else {
                    return 0;
                }
                break;
            case 'l':
                if(infix[i+1] == 'o' && infix[i+2] == 'g' && infix[i+3] == '(') {
                    i = i + 3;
                    shorter_infix[j++] = 'g'; 
                    continue;
                } else if (infix[i+1] == 'n' && infix[i+2] == '(') {
                    i = i + 2;
                    shorter_infix[j++] = 'l';
                    continue;
                } else {
                    return 0;
                }
                break; 
            case 's':
                if(infix[i+1] == 'i' && infix[i+2] == 'n' && infix[i+3] == '(') {
                    i = i + 3;
                    shorter_infix[j++] = 's'; 
                    continue;
                } else if (infix[i+1] == 'i' && infix[i+2] == 'n' && infix[i+3] == 'h' && infix[i+4] == '(') {
                    i = i + 4;
                    shorter_infix[j++] = 'h';
                    continue;
                } else {
                    return 0;
                }
                break;
            case 't':
                if(infix[i+1] == 'a' && infix[i+2] == 'n' && infix[i+3] == '(') {
                    i = i + 3;
                    shorter_infix[j++] = 't'; 
                    continue;
                } else if (infix[i+1] == 'a' && infix[i+2] == 'n' && infix[i+3] == 'h' && infix[i+4] == '(') {
                    i = i + 4;
                    shorter_infix[j++] = 'k';
                    continue;
                } else {
                    return 0;
                }
                break;           
            default:
                shorter_infix[j++] = infix[i++];
                break;
        }

    }

    shorter_infix[j] = '\0';

    strcpy(infix, shorter_infix);

    return 1;

}

static int eliminate_empty_space (char *infix, char *shorter_infix) {

    size_t i = 0, j = 0;

    if (!infix || !shorter_infix) {
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
    
    return 1;
}

static int eliminate_excess_of_operators(char *infix, char *shorter_infix) {
    
    size_t i = 0, j = 0;
    int counter = 0;

    if (!infix || !shorter_infix) {
        return 0;
    }

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

    return 1;

}

static int E_expression (char *infix, char *shorter_infix) {

    size_t i = 0, a = 0, b = 0, c = 0;
    int j = 0;
    int counter = 0;
    int uzaver_E = 0;
    int cislo_pred = 0, tecka = 0, cislo_po = 0;
    char digits_after_dot_in_E_expresion[MAX_LENGTH];
    char digits_before_E_in_expresion[MAX_LENGTH];

    if (!infix || !shorter_infix) {
        return 0;
    }

    do {
        counter = 0;
        i = 0;
        j = 0;

        shorter_infix[0] = '\0';

        while (infix[i] != '\0') {
            
            if (infix[i] == 'E') {

                if (infix[0] == '+') {
                    return 0;
                }

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

        shorter_infix[0] = '\0';

    } while (counter > 0);

    return 1;

}

int make_shorter_infix(char *infix) {
    char shorter_infix[MAX_LENGTH];

    if (!infix) {
        return 0;
    }

    if (!bracket_control(infix)) {
        return 0;
    }

    if (!dot_resolve(infix, shorter_infix)) {
        return 0;
    }

    if (!functions_parser(infix, shorter_infix)) {
        return 0;
    }

    if (!eliminate_empty_space(infix, shorter_infix)) {
        return 0;
    }

    if (!eliminate_excess_of_operators(infix, shorter_infix)) {
        return 0;
    }

    if (!E_expression(infix, shorter_infix)) {
        return 0;
    }


    printf("%s\n", infix);




    return 1;
}

int infix_to_rpn(char *infix, char *postfix) {

    struct stack *s = stack_alloc(MAX_LENGTH, sizeof(char));
    struct stack *functions = stack_alloc(MAX_LENGTH, sizeof(char));
    size_t i = 0, j = 0;
    char top;
    char top_function;

    char unar_minus = '_';

    int length = 0, content_of_bracket = 0, start_of_brackets_content = 0;
    
    if (!s && functions) {
        stack_dealloc(&functions);
    } else if (!functions && s) {
        stack_dealloc(&s);
    } else if (!s && !functions) {
        stack_dealloc(&s);
        stack_dealloc(&functions);
    }

    if (!infix || !postfix) {
        stack_dealloc(&s);
        stack_dealloc(&functions);
        return 0;
    }

    printf("%s\n", infix);

    length = strlen(infix);

    if (je_operator(infix[length - 1]) || (!isdigit(infix[0]) && infix[0] != '+' && infix[0] != '-' && infix[0] != '(' && infix[0] != ')'
    && infix[0] != 'a' && infix[0] != 'e' && infix[0] != 'l' && infix[0] != 'g' && infix[0] != 's' && infix[0] != 'c' && infix[0] != 't'
     && infix[0] != 'm' && infix[0] != 'n' && infix[0] != 'b' && infix[0] != 'h' && infix[0] != 'j' && infix[0] != 'k' && infix[0] != 'x')) {
        stack_dealloc(&s);
        stack_dealloc(&functions);
        return 0;
    }


    while (infix[i] != '\0') {

        /*ošetření případného opakování **, // nebo ^^*/
        if((infix[i] == '*' && infix[i+1] == '*') || (infix[i] == '/' && infix[i+1] == '/')
         || (infix[i] == '^' && infix[i+1] == '^') || (infix[i] == '.' && infix[i+1] == '.')
          || (infix[i] == 'E' && infix[i+1] == 'E')) {
            stack_dealloc(&s);
            stack_dealloc(&functions);
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

                /* Ošetření desetinných čísel 
                if ( (!isdigit(infix[i-1]) && infix[i] == '.' && isdigit(infix[i+1])) || (isdigit(infix[i-1]) && infix[i] == '.' && !isdigit(infix[i+1])) ) {
                    stack_dealloc(&s);
                    stack_dealloc(&functions);
                    return 0;
                }*/

                postfix[j++] = infix[i++];

            }

            if (start_of_brackets_content != content_of_bracket) {
                ++content_of_bracket;      
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

            if (i == 0 || je_operator(infix[i-1])) {
                stack_push(functions, &infix[i]);
            }

            if (start_of_brackets_content != content_of_bracket) {
                ++content_of_bracket;      
            }

            ++start_of_brackets_content;
            i++;

        } else if (infix[i] == ')') {

            while (stack_pop(s, &top) && top != '(') {
                postfix[j++] = top;
                postfix[j++] = ' ';
            }
            
            if ((content_of_bracket != start_of_brackets_content) || (je_operator(infix[i-1]))) {
                stack_dealloc(&s);
                stack_dealloc(&functions);
                return 0;
            }

            --content_of_bracket;
            --start_of_brackets_content;

            stack_pop(functions, &top_function);
            if (top_function == '(') {

            } else {
                postfix[j++] = top_function;
                postfix[j++] = ' ';
            }

            if (top != '(') {
                
                /*neuzavrena zavorka*/
                stack_dealloc(&s);
                stack_dealloc(&functions);
                return 0;
            }
            i++;

        } else if (infix[i] == 'a' || infix[i] == 'e' || infix[i] == 'l' || infix[i] == 'g' || infix[i] == 's' || infix[i] == 'c'
         || infix[i] == 't' || infix[i] == 'm' || infix[i] == 'n' || infix[i] == 'b' || infix[i] == 'h' || infix[i] == 'j' || infix[i] == 'k') {

            stack_push(functions, &infix[i]);

            if (start_of_brackets_content != content_of_bracket) {
                ++content_of_bracket;      
            }

            i++;

        } else if (infix[i] == ' ') {
            
            i++;

        } else if (infix[i] == 'x') {
            
            postfix[j++] = infix[i++];
            postfix[j++] = ' ';

            if (start_of_brackets_content != content_of_bracket) {
                ++content_of_bracket;      
            }

        } else {

            /* neplatny znak */
            stack_dealloc(&s);
            stack_dealloc(&functions);
            return 0; 

        }
    }

    
    while (s->sp > 0) {
        stack_pop(s, &top);
        if (top == '(') {
            
            /*neni uzavřena závorka*/
            stack_dealloc(&s);
            stack_dealloc(&functions);
            return 0;
        }
        postfix[j++] = top;
        postfix[j++] = ' ';

    }

    postfix[j] = '\0';

    stack_dealloc(&s);
    stack_dealloc(&functions);

    return 1;
}

