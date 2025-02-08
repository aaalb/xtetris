/**
* @file Field.c
* @author Albert Alibeaj
* @brief File di implementazione della funzione per l'inizializzazione del campo utilizzata per la partita
*/

#include "Field.h"

void field_init(int field[FIELD_ROWS][FIELD_COLS])
{
    int i, j;

    /*field = (int*)malloc(FIELD_ROWS * FIELD_COLS * sizeof(int));*/
    for(i = 0; i < FIELD_ROWS; i++)
        for(j = 0; j < FIELD_COLS; j++)
            field[i][j] = 0;
}
