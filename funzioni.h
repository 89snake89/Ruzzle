#ifndef FUNZIONI_H_INCLUDED
#define FUNZIONI_H_INCLUDED

typedef struct lista_parole
{
    char *word;
    int pnt;
    int *array_x;
    int *array_y;
    struct lista_parole *next;

} OUTPUT;

void accent_c(char word[]);
OUTPUT* controller(char word[], char cboard[4][4], int array_x[], int array_y[], int matrixPnt[4][4], int matrixBns[4][4], int len);
int re_controller(char word[], char cboard[4][4], int y, int x, int i_w, int array_x[], int array_y[]);
int score(int array_x[], int array_y[], int pntboard[4][4], int bonusboard[4][4], int len);

#endif /* FUNZIONI_H_INCLUDED */
