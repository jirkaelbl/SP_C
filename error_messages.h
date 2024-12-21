#ifndef ERROR_MESSAGES_H
#define ERROR_MESSAGES_H

void spravne(int *message_result);

void nespravne_parametry(int *message_result);

void spatny_vzorecek(int *message_result);

void spatny_vystupni_soubor(int *message_result);

void spatny_rozsah(int *message_result);

void selhalo_defaultni_nacteni_limit(int *message_result);

void nan_number(int *message_result);

void other_error(int *message_result);

#endif