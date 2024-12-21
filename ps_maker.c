#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>

#include "ps_maker.h"

static double scatter_count(double a, double b) {

    return fabs(a - b);;
}

static int create_postscript_header(FILE *file, const char *title, const char *author, double min_x_limit, double max_x_limit, double min_y_limit, double max_y_limit) {

    time_t now;
    struct tm *tm_info;
    char date[20];

    int sizer;

    if (!file) {
        return 0;
    }

    time(&now);
    tm_info = localtime(&now);
    strftime(date, 20, "%Y-%m-%d", tm_info);

    
    fprintf(file, "%%!PS\n");
    fprintf(file, "%% Title: %s\n", title);
    fprintf(file, "%% Author: %s\n", author);
    fprintf(file, "%% CreationDate: %s\n", date);
    fprintf(file, "%% Limits: min_x = %f, max_x = %f, min_y = %f, max_y = %f\n", min_x_limit, max_x_limit, min_y_limit, max_y_limit);
    fprintf(file, "%% EndComments\n\n\n");

    /*fprintf(file, "/min_x %f\n", min_x_limit);
    fprintf(file, "/max_x %f\n", max_x_limit);
    fprintf(file, "/min_y %f\n", min_y_limit);
    fprintf(file, "/max_y %f\n\n", max_y_limit);*/

    fprintf(file, "/min_x_axis %f\n", floor(min_x_limit));
    fprintf(file, "/max_x_axis %f\n", ceil(max_x_limit));
    fprintf(file, "/min_y_axis %f\n", floor(min_y_limit));
    fprintf(file, "/max_y_axis %f\n\n", ceil(max_y_limit));

    if (((scatter_count(ceil(max_x_limit), floor(min_x_limit))) > 57) || ((scatter_count(ceil(max_y_limit), floor(min_y_limit))) > 39.5)) {
        
        sizer = 20;

    } else {
        
        sizer = 40;

    }

    fprintf(file, "<< /PageSize [%f %f] >> setpagedevice\n\n", ((scatter_count(ceil(max_x_limit), floor(min_x_limit))) * sizer + 120), ((scatter_count(ceil(max_y_limit), floor(min_y_limit))) * sizer + 120));
    fprintf(file, "/width %f def\n", ((scatter_count(ceil(max_x_limit), floor(min_x_limit))) * sizer + 120));
    fprintf(file, "/height %f def\n\n", ((scatter_count(ceil(max_y_limit), floor(min_y_limit))) * sizer + 120));

    fprintf(file, "/sizer %d def\n", sizer);
    fprintf(file, "/scatter_x %f def\n", scatter_count(ceil(max_x_limit), floor(min_x_limit)));
    fprintf(file, "/scatter_y %f def\n\n", scatter_count(ceil(max_y_limit), floor(min_y_limit)));

    fprintf(file, "2 setlinewidth\n\n");
    fprintf(file, "/Helvetica findfont\n");
    fprintf(file, "16 scalefont setfont\n\n");

    fprintf(file, "newpath\n\n");

    fprintf(file, "60 height 60 sub moveto\n");
    fprintf(file, "width 60 sub height 60 sub lineto\n");

    fprintf(file, "width 60 sub height 60 sub moveto\n");
    fprintf(file, "width 60 sub 60 lineto\n");

    fprintf(file, "width 60 sub 60 moveto\n");
    fprintf(file, "60 60 lineto\n");

    fprintf(file, "60 60 moveto\n");
    fprintf(file, "60 height 60 sub lineto\n\n");

    fprintf(file, "0 1 scatter_x {\n\n");
    fprintf(file, "/i exch def\n");
    fprintf(file, "/min_x_axis_again %d def\n\n", (int) floor(min_x_limit));
    fprintf(file, "i sizer mul 60 add height 60 sub moveto\n");
    fprintf(file, "i sizer mul 60 add height 66 sub lineto\n\n");
    fprintf(file, "i sizer mul 60 add 60 moveto\n");
    fprintf(file, "i sizer mul 60 add 66 lineto\n\n");

    fprintf(file, "i sizer mul 60 add 4 sub 40 moveto\n");
    fprintf(file, "/min_x_value min_x_axis_again i add def\n");
    fprintf(file, "min_x_value 20 string cvs show\n\n");

    fprintf(file, "} for\n");

    fprintf(file, "0 1 scatter_y {\n\n");
    fprintf(file, "/i exch def\n");
    fprintf(file, "/min_y_axis_again %d def\n\n", (int) floor(min_y_limit));
    fprintf(file, "60 i sizer mul 60 add moveto\n");
    fprintf(file, "66 i sizer mul 60 add lineto\n\n");
    fprintf(file, "width 60 sub i sizer mul 60 add moveto\n");
    fprintf(file, "width 66 sub i sizer mul 60 add lineto\n\n");

    fprintf(file, "36 i sizer mul 60 add 4 sub moveto\n");
    fprintf(file, "/min_y_value min_y_axis_again i add def\n");
    fprintf(file, "min_y_value 20 string cvs show\n\n");

    fprintf(file, "} for\n");

    fprintf(file, "stroke\n\n");

    if (max_y_limit > 0 && min_y_limit < 0) {

        fprintf(file, "[20 10 5 15] 0 setdash\n\n");

        fprintf(file, "60 height height 120 sub %f mul 60 add sub moveto\n", ((ceil(max_y_limit) - 0)/(ceil(max_y_limit) - floor(min_y_limit))));
        fprintf(file, "width 60 sub height height 120 sub %f mul 60 add sub lineto\n\n", ((ceil(max_y_limit) - 0) / (ceil(max_y_limit) - floor(min_y_limit))));

        fprintf(file, "stroke\n\n");

    }

    if (max_x_limit > 0 && min_x_limit < 0) {

        fprintf(file, "[20 10 5 15] 0 setdash\n\n");

        fprintf(file, "width width 120 sub %f mul 60 add sub 60 moveto\n", ((ceil(max_x_limit) - 0)/(ceil(max_x_limit) - floor(min_x_limit))));
        fprintf(file, "width width 120 sub %f mul 60 add sub height 60 sub lineto\n\n", ((ceil(max_x_limit) - 0) / (ceil(max_x_limit) - floor(min_x_limit))));

        fprintf(file, "stroke\n\n");

    }

    





    fprintf(file, "width 2 div 8 sub 10 moveto\n");
    fprintf(file, "(x) show\n");
    fprintf(file, "0 height 2 div 8 sub moveto\n");
    fprintf(file, "(f(x)) show\n\n");

    /*fprintf(file, "showpage\n");*/



    return 1;
}


int vytvor_soubor(FILE **soubor, char *argument, double min_x_limit, double max_x_limit, double min_y_limit, double max_y_limit) {

    char cely_nazev[100];
    char *nazev_jmeno;
    char *nazev_pripona;
    char *token;
    int count = 0;


    /*Zde není ověřena existence *soubor, ta bude ze začátku vždy NULL, protoře soubor ještě nebyl vytvořen*/
    if (!soubor || !argument) {
        printf("Chyba při vytváření souboru!\n");
        return 0;
    }

    token = strtok(argument, ".");
    if (token != NULL) {
        nazev_jmeno = token;
        count++;
    } else {
        return 0;
    }

    token = strtok(NULL, ".");
    if (token != NULL && strcmp(token, "ps") == 0) {
        nazev_pripona = token;
        count++;
    } else {
        return 0;
    }

    if (strtok(NULL, ".") != NULL) {
        return 0;
    }

    sprintf(cely_nazev, "%s.%s", nazev_jmeno, nazev_pripona);

    *soubor = fopen(cely_nazev, "w");

    if (!create_postscript_header(*soubor, "Inserted graph of the generated function", "Jiří Elbl", min_x_limit, max_x_limit, min_y_limit, max_y_limit)) {
        return 0;
    }

    fclose(*soubor);

    return count == 2;
}

int draw_graph(const char *filename, double **array, int length_of_array, double min_x_limit, double max_x_limit, double min_y_limit, double max_y_limit) {

    int i, bound_switcher = 0;
    FILE *file;
    char move_to[256] = "";

    if (!filename || !array) {
        return 0;
    }

    file = fopen(filename, "a");
    if (!file) {
        return 0;
    }
    
    fprintf(file, "255 255 0 setrgbcolor\n");
    fprintf(file, "[] 0 setdash\n\n");

    fprintf(file, "width width 120 sub %f mul 60 add sub height height 120 sub %f mul 60 add sub translate\n",((ceil(max_x_limit) - 0)/(ceil(max_x_limit) - floor(min_x_limit))), ((ceil(max_y_limit) - 0)/(ceil(max_y_limit) - floor(min_y_limit))));

    for (i = 0; i < length_of_array; i++) {

        if (!array[i] || array[i][1] > max_y_limit || array[i][1] < min_y_limit) {

            continue;

        } else {

            sprintf(move_to, "sizer %f mul sizer %f mul moveto\n", array[i][0], array[i][1]);
            break;

        }

    }

    for (i = 0; i < length_of_array; ++i) {
        if (!array[i] || array[i][1] > max_y_limit || array[i][1] < min_y_limit) {
            bound_switcher = 1;
            continue;
        }

        if (bound_switcher == 1) {
            sprintf(move_to, "sizer %f mul sizer %f mul moveto\n", array[i][0], array[i][1]);
            bound_switcher = 0;
            continue;
        }

        fprintf(file, move_to);
        fprintf(file, "sizer %f mul sizer %f mul lineto\n", array[i][0], array[i][1]);
        sprintf(move_to, "sizer %f mul sizer %f mul moveto\n", array[i][0], array[i][1]);

    }

    fprintf(file, "stroke\n\n");


    fprintf(file, "showpage\n");

    fclose(file);

    return 1;
}

int delete_file(FILE **soubor, char *title) {

    if (!soubor || !*soubor) {
        return 0;
    }

    printf("%s\n", title);

    if (remove(title) != 0) {

        printf("neúspěšně neodstraněno.\n");
        return 0;

    }

    return 1;

}