#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "operator.h"



int make_num_operation(calc_num_type *y, char *oper_sign, calc_num_type a, calc_num_type b) {

    if (!y || !oper_sign) {
        return EXIT_FAILURE;
    }

   if (strcmp(oper_sign, "+") == 0) {

     *y = sum(a, b);

   } else if (strcmp(oper_sign, "-") == 0) {

     *y = sub(a, b);

   } else if (strcmp(oper_sign, "*") == 0) {

     *y = mul(a, b);
    
   } else if (strcmp(oper_sign, "/") == 0) {

    if (b != 0) {
       *y = divide(a, b); 
    } else {
        return EXIT_FAILURE;
    }
    
   } else if (strcmp(oper_sign, "^") == 0) {

    *y = square(a, b);
    
   } else if (strcmp(oper_sign, "e") == 0) {

    *y = exponencial(a);
    
   } else if (strcmp(oper_sign, "ln") == 0) {

    *y = logaritmus(a);
    
   } else if (strcmp(oper_sign, "log") == 0) {

    *y = decadic_logaritmus(a);
    
   } else if (strcmp(oper_sign, "sin") == 0) {

    *y = sinus(a);
    
   } else if (strcmp(oper_sign, "cos") == 0) {

    *y = cosinus(a);
    
   } else if (strcmp(oper_sign, "tan") == 0) {

    *y = tangenz(a);
    
   } else if (strcmp(oper_sign, "asin") == 0) {

    *y = cyclometric_sinus(a);
    
   } else if (strcmp(oper_sign, "acos") == 0) {

    *y = cyclometric_cosinus(a);
    
   } else if (strcmp(oper_sign, "atan") == 0) {

    *y = cyclometric_tangenz(a);
    
   } else if (strcmp(oper_sign, "sinh") == 0) {

    *y = hyperbolic_sinus(a);
    
   } else if (strcmp(oper_sign, "cosh") == 0) {

    *y = hyperbolic_cosinus(a);
    
   } else if (strcmp(oper_sign, "tanh") == 0) {

    *y = hyperbolic_tangenz(a);
    
   } else if (strcmp(oper_sign, "abs") == 0) {

    *y = absolut_value(a);
    
   } else if (strcmp(oper_sign, "_") == 0) {

    *y = unar_minus(a);
    
   } else {
        printf("Nevalidní operátor či funkce.\n");
        return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;

}

calc_num_type sum(calc_num_type a, calc_num_type b) {

    return a + b;

}

calc_num_type sub(calc_num_type a, calc_num_type b) {

    return a - b;

}

calc_num_type mul(calc_num_type a, calc_num_type b) {

    return a * b;

}

calc_num_type divide(calc_num_type a, calc_num_type b) {

    return a / b;

}

calc_num_type unar_minus(calc_num_type a) {

    return -a;

}

calc_num_type square(calc_num_type a, calc_num_type b) {

    return pow(a, b);

}

calc_num_type absolut_value(calc_num_type a) {

    return fabs(a);

}

calc_num_type exponencial(calc_num_type a) {

    return exp(a);

}

calc_num_type logaritmus(calc_num_type a) {

    return log(a);

}

calc_num_type decadic_logaritmus(calc_num_type a) {

    return log10(a);

}

calc_num_type sinus(calc_num_type a) {

    return sin(a);

}

calc_num_type cosinus(calc_num_type a) {

    return cos(a);

}

calc_num_type tangenz(calc_num_type a) {

    return tan(a);

}

calc_num_type cyclometric_sinus(calc_num_type a) {

    return asin(a);

}

calc_num_type cyclometric_cosinus(calc_num_type a) {

    return acos(a);

}

calc_num_type cyclometric_tangenz(calc_num_type a) {

    return atan(a);

}

calc_num_type hyperbolic_sinus(calc_num_type a) {

    return sinh(a);

}

calc_num_type hyperbolic_cosinus(calc_num_type a) {

    return cosh(a);

}

calc_num_type hyperbolic_tangenz(calc_num_type a) {

    return tanh(a);

}
