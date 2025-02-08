/**
* @file Moves.c
* @author Albert Alibeaj
* @brief File di implementazione delle funzioni di gestione di campo e tetramini utilizzate per la partita
*/

#include "Moves.h"

/**
* Sposta il tetramino in basso e a sinistra (toglie le prime colonne e le ultime righe vuote)
 * @param tet tetramino di cui correggere la forma dopo una rotazione
*/
void tet_adjust(tet_t* tet);

/**
* Inserisce un tetramino nel campo in una certa riga e colonna precisa, senza calcolo della caduta
 * @param field campo su cui inserire il tetramino
 * @param tet tetramino da inserire (controlla la forma)
 * @param row riga del campo in cui inserire il tetramino
 * @param col colonna del campo in cui inserire il tetramino
*/
void insert_at_pos(int field[FIELD_ROWS][FIELD_COLS], tet_t tet, int row, int col);

/**
* Controlla le righe del campo modificate e se necessario le elimina
 * @param field campo da controllare e modificare
 * @param row riga da cui iniziare il controllo
 * @param len numero di righe a scendere da controllare
 * @return punteggio ottenuto dopo l'eliminazione delle righe
*/
int getscore(int field[FIELD_ROWS][FIELD_COLS], int row, int len);

/**
* Controlla se una riga del campo è vuota
 * @param field campo da controllare
 * @param row riga da controllare
 * @return 1 se la riga è vuota, 0 altrimenti
*/
int is_empty_row(int field[FIELD_ROWS][FIELD_COLS], int row);

/**
* Ultimo punto solido della forma del tetramino in una certa colonna
 * @param tet tetramino di cui controllare la forma
 * @param col colonna da controllare
 * @return prima riga della forma a partire dal basso che contiene il tetramino nella colonna scelta (-1 se colonna vuota)
*/
int tet_last_solid(tet_t tet, int col)
{
    int r;
    for(r = tet.shape_len - 1; r >= 0; r--)
    {
        if(tet.shape[r * tet.shape_len + col])
            return r;
    }
    return r;
}

int insert(int field[FIELD_ROWS][FIELD_COLS], tet_t* tet, int column, int rotation)
{
    int width;
    int collision = 0, collision_row = FIELD_ROWS - 1;
    int i, insert_row;
    int score;

    reset_shape(tet);
    rotate_dx(tet, rotation);

    width = tet_width(*tet);

    if(FIELD_COLS - column < width)
        column = FIELD_COLS - width;

    for(i = tet->shape_len; i < FIELD_ROWS && !collision; i++)
    {
        int j;
        for(j = 0; j < width && !collision; j++)
        {
            int last_solid_row = tet_last_solid(*tet, j);
            int field_row = i - (tet->shape_len - 1 - last_solid_row);

            int tet_piece = tet->shape[last_solid_row * tet->shape_len + j];
            int field_piece = field[field_row][column + j];

            if(tet_piece && field_piece)
            {
                collision = 1;
                collision_row = i - 1;
            }
        }
    }

    insert_row = collision_row - (tet->shape_len - 1);
    insert_at_pos(field, *tet, insert_row, column);

    tet->quantity--;
    reset_shape(tet);

    score = getscore(field, insert_row, tet->shape_len); /* Rimuove le righe piene */

    /* Viene ritornato un valore positivo solo se la mossa è valida */
    if(is_empty_row(field, INVALID_ROWS - 1))
        return score;
    else
        return -1;
}

void rotate_dx(tet_t* tet, int n)
{
    int count;

    n %= tet->rot_number;
    for(count = 0; count < n; count++)
    {
        int levels = (tet->shape_len + 1) / 2; /* I livelli sono gli strati di ogni matrice (quadrati interni) */
        int top; /* Prima riga e colonna di ogni gruppo */
        for(top = 0; top < levels; top++)
        {
            int reps;
            int sub_group_dim = tet->shape_len - (top * 2);

            /* Ogni ciclo sposta una cella di una sola posizione. Bisogna ripetere in base al livello */

            for(reps = 0; reps < sub_group_dim - 1; reps++)
            {
                int i = top, j = top;
                int bottom = (tet->shape_len - 1) - top; /* Ultima riga e colonna del gruppo */
                int temp = tet->shape[i * tet->shape_len + j];

                for(i = top; i < bottom; i++)
                    tet->shape[i * tet->shape_len + j] = tet->shape[(i + 1) * tet->shape_len + j];

                for(j = top; j < bottom; j++)
                    tet->shape[i * tet->shape_len + j] = tet->shape[i * tet->shape_len + (j + 1)];

                for(; i > top; i--)
                    tet->shape[i * tet->shape_len + j] = tet->shape[(i - 1) * tet->shape_len + j];

                for(; j > top + 1; j--)
                    tet->shape[i * tet->shape_len + j] = tet->shape[i * tet->shape_len + (j - 1)];

                tet->shape[i * tet->shape_len + j] = temp;
            }
        }
    }

    tet_adjust(tet);
}

void rotate_sx(tet_t* tet, int n)
{
    n %= tet->rot_number;
    rotate_dx(tet, tet->rot_number - n);
}

void insert_at_pos(int field[FIELD_ROWS][FIELD_COLS], tet_t tet, int row, int col)
{
    int r;
    for(r = 0; r < tet.shape_len; r++)
    {
        int c;
        for (c = 0; c < tet.shape_len; c++)
        {
            int tet_val = tet.shape[r * tet.shape_len + c];
            if (tet_val)
            {
                field[row + r][col + c] = tet.value;
            }
        }
    }
}

void tet_adjust(tet_t* tet)
{
    /* spostamento a sinistra */
    /* si controlla la prima colonna e se è vuota si shifta la matrice a sinistra e si riparte finchè non è più vuota */
    int i, r, c;
    for(i = 0; i < tet->shape_len; i++)
    {
        int first_col = 0;
        int trimmable = 1;
        for(r = 0; r < tet->shape_len; r++)
        {
            if(tet->shape[r * tet->shape_len + first_col] != 0)
            {
                trimmable = 0;
            }
        }

        if(trimmable)
        {
            for(c = 0; c < tet->shape_len - 1; c++)
            {
                for(r = 0; r < tet->shape_len; r++) {

                    int curr = r * tet->shape_len + c;
                    int succ = curr + 1;

                    tet->shape[curr] = tet->shape[succ];
                    tet->shape[succ] = 0;
                }
            }
        }
    }

    /* spostamento in basso */
    /* si controlla se l'ultima riga è vuota e in tal caso la matrice shifta verso il basso. Si ripete finchè l'ultima riga non è più vuota */
    for(i = 0; i < tet->shape_len; i++)
    {
        int last_row = tet->shape_len - 1;
        int trimmable = 1;
        for(c = 0; c < tet->shape_len; c++)
        {
            if(tet->shape[last_row * tet->shape_len + c] != 0)
            {
                trimmable = 0;
            }
        }

        if(trimmable)
        {
            for(r = tet->shape_len - 1; r > 0; r--)
            {
                for(c = 0; c < tet->shape_len; c++)
                {
                    int curr = r * tet->shape_len + c;
                    int prec = (r - 1) * tet->shape_len + c;

                    tet->shape[curr] = tet->shape[prec];
                    tet->shape[prec] = 0;
                }
            }
        }
    }
}

/**
* Elimina una riga dal campo e fa cadere le righe superiori
 * @param field campo modificare
 * @param row riga da eliminare
*/
void deleterow(int field[FIELD_ROWS][FIELD_COLS], int row)
{
    int i, j;

    for(i = row; i > 0; i--)
        for(j = 0; j < FIELD_COLS; j++)
            field[i][j] = field[i - 1][j];

    for(j = 0; j < FIELD_COLS; j++)
        field[0][j] = 0;
}

int getscore(int field[FIELD_ROWS][FIELD_COLS], int row, int len)
{
   int i, j;
   int score = 0;
   for(i = 0; i < len; i++)
   {
       int filled = 1;
       for(j = 0; j < FIELD_COLS && filled; j++)
       {
           filled = field[row + i][j];
       }

       if(filled) /* riga piena, da eliminare */
       {
           deleterow(field, row + i);
           i--;
           score++;
       }
   }

   switch(score)
   {
       case 0: score = 0; break;
       case 1: score = 1; break;
       case 2: score = 3; break;
       case 3: score = 6; break;
       default: score = 12; break;
   }

   return score;
}

void reset_shape(tet_t* tet)
{
    int i, j;
    for(i = 0; i < tet->shape_len; i++)
        for(j = 0; j < tet->shape_len; j++)
            tet->shape[i * tet->shape_len + j] = tet->base_shape[i * tet->shape_len + j];
}

int is_empty_row(int field[FIELD_ROWS][FIELD_COLS], int row)
{
    int j;

    for(j = 0; j < FIELD_COLS; j++)
        if(field[row][j])
            return 0;

    return 1;
}
