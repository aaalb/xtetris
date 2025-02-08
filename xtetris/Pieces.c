/**
* @file Pieces.c
* @author Albert Alibeaj
* @brief File di implementazione delle funzioni per le proprietà dei tetramini utilizzate per la partita
*/

#include "Pieces.h"

/**
* Alloca la memoria per la forma base e la forma corrente di un tetramino e la inizializza
 * @param tet tetramino a cui assegnare forma e forma base
 * @param shape array da copiare nei campi del tetramino
 * @param dim lunghezza dell'array da copiare
*/
void tet_base_shape_set(tet_t* tet, const int* shape, int dim);

void tets_init(tet_t tets[TET_TYPES], int multiplayer)
{
    int quant = DEFAULT_TET_QUANTITY * (multiplayer ? 2 : 1);

    int tet0[] = {0,0,0, 0,1,0, 1,1,1};
    int tet1[] = {0,0,0,0, 0,0,0,0, 0,0,0,0, 1,1,1,1};
    int tet2[] = {0,0,0, 1,0,0, 1,1,1};
    int tet3[] = {0,0,0, 0,0,1, 1,1,1};
    int tet4[] = {1,1, 1,1};
    int tet5[] = {0,0,0,0,1,1,1,1,0};
    int tet6[] = {0,0,0,1,1,0,0,1,1};

    tets[0].value = 1;
    tets[0].shape_len = 3;
    tets[0].rot_number = 4;
    tets[0].quantity = quant;
    tet_base_shape_set(&tets[0], tet0, 9);

    tets[1].value = 2;
    tets[1].shape_len = 4;
    tets[1].rot_number = 2;
    tets[1].quantity = quant;
    tet_base_shape_set(&tets[1], tet1, 16);

    tets[2].value = 3;
    tets[2].shape_len = 3;
    tets[2].rot_number = 4;
    tets[2].quantity = quant;
    tet_base_shape_set(&tets[2], tet2, 9);

    tets[3].value = 4;
    tets[3].shape_len = 3;
    tets[3].rot_number = 4;
    tets[3].quantity = quant;
    tet_base_shape_set(&tets[3], tet3, 9);

    tets[4].value = 5;
    tets[4].shape_len = 2;
    tets[4].rot_number = 1;
    tets[4].quantity = quant;
    tet_base_shape_set(&tets[4], tet4, 4);

    tets[5].value = 6;
    tets[5].shape_len = 3;
    tets[5].rot_number = 2;
    tets[5].quantity = quant;
    tet_base_shape_set(&tets[5], tet5, 9);

    tets[6].value = 7;
    tets[6].shape_len = 3;
    tets[6].rot_number = 2;
    tets[6].quantity = quant;
    tet_base_shape_set(&tets[6], tet6, 9);
}

void tet_base_shape_set(tet_t* tet, const int* shape, int dim)
{
    int i;
    tet->base_shape = (int*)malloc(tet->shape_len * tet->shape_len * sizeof(int));
    tet->shape = (int*)malloc(tet->shape_len * tet->shape_len * sizeof(int));

    for(i = 0; i < dim; i++)
    {
        int val = shape[i] ? tet->value : 0;
        tet->base_shape[i] = val;
        tet->shape[i] = val;
    }
}

void tets_free(tet_t tets[TET_TYPES])
{
    int i;
    for(i = 0; i < TET_TYPES; i++)
    {
        free(tets[i].base_shape);
        free(tets[i].shape);
    }
}

int tet_width(tet_t tet)
{
    int j;
    for (j = tet.shape_len - 1; j >= 0; j--) {
        int i;
        for (i = 0; i < tet.shape_len; i++) {
            if (tet.shape[i * tet.shape_len + j])
                return (j + 1);
        }
    }
    return (j + 1);
}
