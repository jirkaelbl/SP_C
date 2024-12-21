#ifndef PS_MAKER_H
#define PS_MAKER_H

int vytvor_soubor(FILE **soubor, char *argument, double min_x_limit, double max_x_limit, double min_y_limit, double max_y_limit);

int draw_graph(const char *filename, double **array, int length_of_array, double min_x_limit, double max_x_limit, double min_y_limit, double max_y_limit);

int delete_file(FILE **soubor, char *title);

#endif