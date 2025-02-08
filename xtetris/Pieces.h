/**
* @file Pieces.h
* @author Albert Alibeaj
* @brief Libreria che definisce la struttura dei tetramini
 * e le funzioni per la loro gestione
*/

#ifndef XTETRIS2_PIECES_H
#define XTETRIS2_PIECES_H

#include <stdlib.h>

#define DEFAULT_TET_QUANTITY 20     /**< quantità iniziale per ogni tetramino (singleplayer) */
#define TET_TYPES 7                 /**< tipi di tetramino distiniti */

/** Tipo tet_t
*   Struttura di un tetramino
*/
typedef struct Tetramino
{
    int value;          /**< il valore all'interno del campo (utile per usare colori diversi) */
    int shape_len;      /**< dimensione del lato dell'array forma */
    int rot_number;     /**< numero di possibili rotazioni distinte */
    int quantity;       /**< la quantità di quel tetramino durante la partita */
    int *base_shape;    /**< array che contiene il tetramino alla forma iniziale */
    int *shape;         /**< array che contiene il tetramino alla forma corrente */

} tet_t;


/**
* Inizializza i tetramini.
 * Alloca gli array e imposta i valori iniziali
 * @param tets array di tetramini da riempire al termine della funzione
 * @param multiplayer se TRUE le quantità sono raddoppiate
*/
void tets_init(tet_t tets[TET_TYPES], int multiplayer);


/**
* Libera la memoria allocata dai tetramini
 * @param tets array di tetramini da deallocare
*/
void tets_free(tet_t tets[TET_TYPES]);


/**
 * Calcola lo spazio occupato in larghezza da un tetramino
 * @param tet tetramino di cui calcolare la larghezza
 * @return larghezza effettiva nella forma corrente
*/
int tet_width(tet_t tet);


#endif /*XTETRIS2_PIECES_H*/
