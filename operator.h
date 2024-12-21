#ifndef OPERATOR_H
#define OPERATOR_H

typedef double calc_num_type;

int make_num_operation(calc_num_type *y, char *oper_sign, calc_num_type a, calc_num_type b);

calc_num_type sum(calc_num_type a, calc_num_type b);

calc_num_type sub(calc_num_type a, calc_num_type b);

calc_num_type mul(calc_num_type a, calc_num_type b);

calc_num_type divide(calc_num_type a, calc_num_type b);

calc_num_type unar_minus(calc_num_type a);

calc_num_type square(calc_num_type a, calc_num_type b);

calc_num_type absolut_value(calc_num_type a);

calc_num_type exponencial(calc_num_type a);

calc_num_type logaritmus(calc_num_type a);

calc_num_type decadic_logaritmus(calc_num_type a);

calc_num_type sinus(calc_num_type a);

calc_num_type cosinus(calc_num_type a);

calc_num_type tangenz(calc_num_type a);

calc_num_type cyclometric_sinus(calc_num_type a);

calc_num_type cyclometric_cosinus(calc_num_type a);

calc_num_type cyclometric_tangenz(calc_num_type a);

calc_num_type hyperbolic_sinus(calc_num_type a);

calc_num_type hyperbolic_cosinus(calc_num_type a);

calc_num_type hyperbolic_tangenz(calc_num_type a);



#endif