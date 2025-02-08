/**
* @file Moves.h
* @author Albert Alibeaj
* @brief Libreria che implementa i movimenti dei tetramini
 * all'interno del campo, come l'inserimento e la rotazione
 *
*/

#ifndef XTETRIS2_MOVES_H
#define XTETRIS2_MOVES_H

#include "Field.h"
#include "Pieces.h"

/**
* Inserisce un tetramino all'interno del campo di gioco
 * @param field array di interi in cui inserire il tetramino
 * @param tet il tetramino da inserire
 * @param column colonna in cui inserire il tetramino
 * @param rotation numero di rotazioni verso destra a partire dalla forma base
 * @return punti guadagnati dall'inserimento
*/
int insert(int field[FIELD_ROWS][FIELD_COLS], tet_t* tet, int column, int rotation);


/**
* Ruota un tetramino a destra (90°) a partire dalla forma corrente
 * @param tet tetramino di cui ruotare il campo shape
 * @param n numero di rotazioni a destra
*/
void rotate_dx(tet_t* tet, int n);

/**
* Ruota un tetramino a sinistra (90°) a partire dalla forma corrente
 * @param tet tetramino di cui ruotare il campo shape
 * @param n numero di rotazioni a sinistra
*/
void rotate_sx(tet_t* tet, int n);


/**
* Riporta la forma corrente di un tetramino alla forma base ruotandolo
 * @param tet array di cui ripristinare la forma iniziale
*/
void reset_shape(tet_t* tet);

#endif /*XTETRIS2_MOVES_H*/
