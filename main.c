#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include "funzioni.h"

#define MAX_LNGTH       1024
#define TRUE            1
#define FALSE           0
#define default_nwords  40
#define exe             4

int main()
{
    OUTPUT *final_w=NULL, *current_pointer=NULL, *last_pointer = NULL, *control=NULL;
    FILE *fboard=NULL, *fdict=NULL, *output=NULL;
    int *array_x=NULL, *array_y=NULL;
    int nwords=0, len=0, find_word=0, inserted=0, limit_words=0, name_len=0, len_board=0, found=0, final_score=0;
    int v=0, i=0, j=0, x=0, y=0;
    int matrixPnt[4][4];
    int matrixBns[4][4];
    char pntboard[4][4];
    char bonusboard[4][4];
    char word[MAX_LNGTH+1];
    char cboard[4][4];
    char *name_board=NULL, *name_dict=NULL;

    printf("Input board file name: ");
    name_board = (char*)malloc(20*sizeof(char));
    if(name_board == NULL)
    {
        printf("\nMemory allocation error\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    scanf("%s", name_board);
    len_board = strlen(name_board);
    name_board = (char*) realloc(name_board, len_board + 1);
    if(name_board == NULL)
    {
        printf("\nMemory allocation error\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    fboard=fopen(name_board,"r");
    if(fboard==NULL)
    {
        printf("\nError opening file %s\n","board.txt");
        system("pause");
        exit(EXIT_FAILURE);
    }

    printf("Input dictionary file name: ");
    name_dict = (char*)malloc(20*sizeof(char));
    if(name_dict == NULL)
    {
        printf("\nMemory allocation error\n");
        system("pause");
        exit(EXIT_FAILURE);
    }
    scanf("%s", name_dict);
    len_board = strlen(name_dict);
    name_dict = (char*) realloc(name_dict, len_board + 1);
    if(name_dict == NULL)
    {
        printf("\nMemory allocation error\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    fdict = fopen(name_dict,"r");
    if(fdict == NULL)
    {
        printf("Uploaded file was not found. It uses the default file.\n");
        system("pause");
        fdict = fopen("dict.txt","r");
    }
    else
    {
        for(i=0; i<4; i++)
            fscanf(fboard, "%c%c%c%c\n", &cboard[i][0], &cboard[i][1], &cboard[i][2], &cboard[i][3]);

        for(i=0; i<4; i++)
            fscanf(fboard, "%c%c%c%c\n", &pntboard[i][0], &pntboard[i][1], &pntboard[i][2], &pntboard[i][3]);

        for(i = 0; i < 4; i++)
        {
            for(j = 0; j<4 ; j++)
            {
                matrixPnt[i][j] = ((int)pntboard[i][j])-((int)('0'));
            }
        }

        for(i=0; i<4; i++)
            fscanf(fboard, "%c%c%c%c\n", &bonusboard[i][0], &bonusboard[i][1], &bonusboard[i][2], &bonusboard[i][3]);

        for(i = 0; i < 4; i++)
        {
            for(j = 0; j<4 ; j++)
            {
                matrixBns[i][j] = ((int)bonusboard[i][j])-((int)('0'));
            }
        }
    }

    printf("Input words to be found (default type 0): ");
    scanf("%d", &nwords);
    if(nwords == 0)
        nwords = default_nwords;

    if(fdict==NULL)
    {
        printf("\nError opening file: %s\n","dict.txt");
        system("pause");
        exit(EXIT_FAILURE);
    }
    else
    {
        while( fgets(word, 1024, fdict)!= NULL )
        {
            v = isalpha(word[0]); /*commento dict*/
            if(v > 0)
            {
                len=0;
                while((word[len] != '/') && (word[len] != '\n'))
                {
                    if(word[len] == '\'') /*apostrofo*/
                    {
                        len=TRUE;
                        word[len] = '\n';
                    }
                    else
                    len++;
                }
                word[len] = '\0';
                len = strlen(word);
                if( (len <= 16) && (len > 1) )
                {
                    accent_c(word);
                    array_x = (int*) malloc(len*sizeof(int));
                    if(array_x == NULL)
                    {
                        printf("\nMemory allocation error\n");
                        system("pause");
                        exit(EXIT_FAILURE);
                    }

                    array_y = (int*) malloc(len*sizeof(int));
                    if(array_y == NULL)
                    {
                        printf("\nMemory allocation error\n");
                        system("pause");
                        exit(EXIT_FAILURE);
                    }

                    for(i=0; i<len; i++)
                    {
                        array_x[i] = 0;
                        array_y[i] = 0;
                        word[i] = toupper(word[i]);
                    }

                    control = controller(word, cboard, array_x, array_y, matrixPnt, matrixBns, len);

                    if(control != NULL)
                    {
                        find_word++;

                        control->array_x = (int*) malloc(len*sizeof(int));
                        if( (control->array_x) == NULL)
                        {
                            printf("\nMemory allocation error\n");
                            system("pause");
                            exit(EXIT_FAILURE);
                        }

                        control->array_y = (int*) malloc(len*sizeof(int));
                        if( (control->array_y) == NULL)
                        {
                            printf("\nMemory allocation error\n");
                            system("pause");
                            exit(EXIT_FAILURE);
                        }

                        for(i=0;i<len;i++)
                        {
                            control->array_x[i] = array_x[i];
                            control->array_y[i] = array_y[i];
                        }

                        if(final_w == NULL)
                        {
                            control->next = NULL;
                            final_w = control;
                        }
                        else
                        {
                            control->next = NULL;
                            current_pointer = final_w;
                            last_pointer = final_w;
                            inserted = FALSE;
                            while(current_pointer != NULL && inserted == FALSE)
                            {
                                if(current_pointer->pnt < control->pnt)
                                {
                                    if(current_pointer == last_pointer)
                                    {
                                        control->next = final_w;
                                        final_w = control;
                                        inserted = TRUE;
                                    }
                                    else
                                    {
                                        control->next = current_pointer;
                                        last_pointer->next = control;
                                        inserted = TRUE;
                                    }
                                }
                                last_pointer = current_pointer;
                                current_pointer = current_pointer->next;
                            }
                            if(inserted == FALSE)
                            {
                                last_pointer->next = control;
                            }
                        }
                    }
                }
            }
        }
    }

    current_pointer = final_w;

    name_len = (strlen(name_board)) - exe;
    name_board[name_len] = '\0';

    output = fopen(strcat(name_board, "_results.txt"), "w");

    final_score = 0;
    while( (current_pointer != NULL) && (limit_words < nwords) )
    {
        fprintf(output, "%s %d \n", current_pointer->word, current_pointer->pnt);
        final_score = final_score + current_pointer->pnt;
        for(i=0; i<4; i++)
        {
            for(j=0; j<4; j++)
            {
                found = FALSE;
                len = strlen(current_pointer->word);

                for(v=0;v<len;v++)
                {
                    x = current_pointer->array_x[v];
                    y = current_pointer->array_y[v];
                    if((y == i) && (x == j))
                    {
                        found = TRUE;
                    }
                }
                if(found == FALSE)
                {
                    fprintf(output, "%c", tolower(cboard[i][j]));
                }
                else
                {
                    fprintf(output, "%c", cboard[i][j]);
                }
            }
            fprintf(output, "\n");
        }
        fprintf(output, "\n");
        current_pointer = current_pointer->next;
        limit_words++;
    }
    fprintf(output, "\n");
    fprintf(output, "Final Score: %d\n", final_score);
    fprintf(output, "Total words: %d", find_word);

    if(limit_words == nwords)
    {
        free(name_dict);
        free(array_x);
        free(array_y);
        free(control);
        while(current_pointer != NULL)
        {
            last_pointer =current_pointer;
            current_pointer =current_pointer->next;
            free(last_pointer);
        }
    }

    fclose(fboard);
    fclose(fdict);

    system("pause");
    return 0;
}
