#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "funzioni.h"

#define TRUE 1
#define FALSE 0

void accent_c(char word[])
{
    int i=0;

    while(word[i] != '\0')
    {
        switch(word[i])
        {
        case 'à':
            word[i] = 'a';
            break;
        case 'è':
            word[i] = 'e';
            break;
        case 'é':
            word[i] = 'e';
            break;
        case 'ì':
            word[i] = 'i';
            break;
        case 'ò':
            word[i] = 'o';
            break;
        case 'ù':
            word[i] = 'u';
            break;
        }
        i++;
    }
    return;
}

OUTPUT* controller(char word[], char cboard[4][4], int array_x[], int array_y[], int matrixPnt[4][4], int matrixBns[4][4], int len)
{
    int y=0, x=0, score_temp=0, i=0, j=0, control=FALSE;
    int *temp_array_x=NULL, *temp_array_y=NULL;
    char copyboard[4][4];

    OUTPUT *lista_score=NULL;

    temp_array_x = (int*) malloc(len*sizeof(int));
    if(temp_array_x == NULL)
    {
        printf("\nMemory allocation error\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    temp_array_y = (int*) malloc(len*sizeof(int));
    if(temp_array_y == NULL)
    {
        printf("\nMemory allocation error\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    for(y=0; y<4; y++)
    {
        for(x=0; x<4; x++)
        {
            if( (cboard[y][x]) == (word[0]) )
            {
                temp_array_x[0] = x;
                temp_array_y[0] = y;
                for(i=0; i<4; i++)
                {
                    for(j=0; j<4; j++)
                    {
                        copyboard[i][j] = cboard[i][j];
                    }
                }
                copyboard[y][x] = '0';

                control = re_controller(word, copyboard, y, x, 0, temp_array_x, temp_array_y);

                copyboard[y][x] = word[0];

                if(control == TRUE)
                {
                    if(lista_score != NULL)
                    {
                        score_temp = score(temp_array_x, temp_array_y, matrixPnt, matrixBns, strlen(word));

                        if(lista_score->pnt < score_temp)
                        {
                            lista_score->word = (char*) malloc((len+1)*sizeof(char));
                            if( (lista_score->word) == NULL)
                            {
                                printf("\nMemory allocation error\n");
                                system("pause");
                                exit(EXIT_FAILURE);
                            }
                            strcpy(lista_score->word,word);

                            lista_score->pnt = score_temp;
                            lista_score->next = NULL;
                        }
                    }
                    else
                    {
                        lista_score = malloc(sizeof(OUTPUT));
                        lista_score->word = (char*) malloc((len+1)*sizeof(char));
                        if( (lista_score->word) == NULL)
                        {
                            printf("\nMemory allocation error\n");
                            system("pause");
                            exit(EXIT_FAILURE);
                        }

                        strcpy(lista_score->word, word);
                        lista_score->pnt = score(temp_array_x, temp_array_y, matrixPnt, matrixBns, strlen(word));
                        lista_score->next = NULL;
                    }
                    for(i=0; i<len; i++)
                    {
                        array_x[i] = temp_array_x[i];
                        array_y[i] = temp_array_y[i];
                    }
                }
            }
        }
    }
    free(temp_array_x);
    free(temp_array_y);

    return lista_score;
}

int re_controller(char word[], char cboard[4][4], int y, int x, int i_w, int array_x[], int array_y[])
{
    int control=FALSE;
    i_w++;

    if( (word[i_w] == '\n') || (word[i_w] == '\0') )
    {
        char *find_word = (char*) malloc(sizeof(char));
        if(find_word == NULL)
        {
            printf("\nMemory allocation error\n");
            system("pause");
            exit(EXIT_FAILURE);
        }

        strcpy(find_word, word);
        return TRUE;
    }
    else
    {
        if( (cboard[y][x+1] == word[i_w]) && ((x+1) < 4) ) /*destra*/
        {
            cboard[y][x+1] = '0';
            array_y[i_w] = y;
            array_x[i_w] = x+1;
            control = re_controller(word, cboard, y, x+1, i_w, array_x, array_y);
            cboard[y][x] = word[i_w];
            if(control != TRUE)
            {
                array_y[i_w] = 0;
                array_x[i_w] = 0;
            }
        }
        else if( (cboard[y+1][x+1] == word[i_w]) && ((y+1) < 4) && ((x+1) < 4) ) /*giudx*/
        {
            cboard[y+1][x+1] = '0';
            array_y[i_w] = y+1;
            array_x[i_w] = x+1;
            control = re_controller(word, cboard, y+1, x+1, i_w, array_x, array_y);
            cboard[y][x] = word[i_w];
            if(control != TRUE)
            {
                array_y[i_w] = 0;
                array_x[i_w] = 0;
            }
        }
        else if( (cboard[y+1][x] == word[i_w]) && ((y+1) < 4) ) /*giu*/
        {
            cboard[y+1][x] = '0';
            array_y[i_w] = y+1;
            array_x[i_w] = x;
            control = re_controller(word, cboard, y+1, x, i_w, array_x, array_y);
            cboard[y][x] = word[i_w];
            if(control != TRUE)
            {
                array_y[i_w] = 0;
                array_x[i_w] = 0;
            }
        }
        else if( (cboard[y+1][x-1] == word[i_w]) && ((y+1) < 4) && ((x-1) > -1) ) /*giusx*/
        {
            cboard[y+1][x-1] = '0';
            array_y[i_w] = y+1;
            array_x[i_w] = x-1;
            control = re_controller(word, cboard, y+1, x-1, i_w, array_x, array_y);
            cboard[y][x] = word[i_w];
            if(control != TRUE)
            {
                array_y[i_w] = 0;
                array_x[i_w] = 0;
            }
        }
        else if( (cboard[y][x-1] == word[i_w]) && ((x-1) > -1) ) /*sinistra*/
        {
            cboard[y][x-1] = '0';
            array_y[i_w] = y;
            array_x[i_w] = x-1;
            control = re_controller(word, cboard, y, x-1, i_w, array_x, array_y);
            cboard[y][x] = word[i_w];
            if(control != TRUE)
            {
                array_y[i_w] = 0;
                array_x[i_w] = 0;
            }
        }
        else if( (cboard[y-1][x-1] == word[i_w]) && ((y-1) > -1) && ((x-1) > -1) ) /*susx*/
        {
            cboard[y-1][x-1] = '0';
            array_y[i_w] = y-1;
            array_x[i_w] = x-1;
            control = re_controller(word, cboard, y-1, x-1, i_w, array_x, array_y);
            cboard[y][x] = word[i_w];
            if(control != TRUE)
            {
                array_y[i_w] = 0;
                array_x[i_w] = 0;
            }
        }
        else if( (cboard[y-1][x] == word[i_w]) && ((y-1) > -1) ) /*su*/
        {
            cboard[y-1][x] = '0';
            array_y[i_w] = y-1;
            array_x[i_w] = x;
            control = re_controller(word, cboard, y-1, x, i_w, array_x, array_y);
            cboard[y][x] = word[i_w];
            if(control != TRUE)
            {
                array_y[i_w] = 0;
                array_x[i_w] = 0;
            }
        }
        else if( (cboard[y-1][x+1] == word[i_w]) && ((y-1) > -1) && ((x+1) < 4) ) /*sudx*/
        {
            cboard[y-1][x+1] = '0';
            array_y[i_w] = y-1;
            array_x[i_w] = x+1;
            control = re_controller(word, cboard, y-1, x+1, i_w, array_x, array_y);
            cboard[y][x] = word[i_w];
            if(control != TRUE)
            {
                array_y[i_w] = 0;
                array_x[i_w] = 0;
            }
        }
        return control;
    }
}

int score(int array_x[], int array_y[], int pntboard[4][4], int bonusboard[4][4], int len)   /*calcola il punteggio di ogni parola*/
{
    int pnt_len=0, var=0, i=0, y=0, x=0, pnt_char=0, bonus=0, flag_dw=0, flag_tw=0, final_score=0;

    if(len > 4)
    {
        var = len - 4;
        pnt_len = var * 5;
    }

    /*char score + bonus*/
    for(i=0; i<len; i++)
    {
        y = array_y[i];
        x = array_x[i];
        bonus = 1;
        /*Bonus for letters*/
        if(bonusboard[y][x] == 1)
        {
            bonus = 2;
        }
        if(bonusboard[y][x] == 2)
        {
            bonus = 3;
        }
        /*Bonus for word*/
        if(bonusboard[y][x] == 3)
        {
            flag_dw++;
        }
        if(bonusboard[y][x] == 4)
        {
            flag_tw++;
        }
        pnt_char = pnt_char + (pntboard[y][x] * bonus) ;
    }

    final_score = (pnt_char  * (pow(2,flag_dw)) * (pow(3,flag_tw)) + pnt_len);
    return final_score;

}
