/**
* @file Game.h
* @author Albert Alibeaj
* @brief Libreria per iniziare e terminare una parita,
 * sia singleplayer che multiplayer
*/

#ifndef XTETRIS2_GAME_H
#define XTETRIS2_GAME_H

#include "Moves.h"

/**
* Prepara e inizia una partita singleplayer
 * e la prosegue finchè non termina
 * @param field array che si vuole usare come campo
 * @param tets array dei tetramini da usare durante la partita
*/
void single_start_game(int field[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES]);

/**
* Libera le risorse occupate durante la partita singleplayer
 * e attende un input da tastiera prima di proseguire
 * @param tets array dei tetramini da deallocare
*/
void single_end_game(tet_t tets[TET_TYPES]);


/**
* Prepara e inizia una partita multiplayer
 * e la prosegue finchè non termina
 * @param f1 array che si vuole usare come campo del giocatore 1
 * @param f2 array che si vuole usare come campo del giocatore 2
 * @param tets array dei tetramini da usare durante la partita
 * @param com se TRUE, il giocatore 2 è il computer
*/
void multi_start_game(int f1[FIELD_ROWS][FIELD_COLS], int f2[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES], int com);

/**
* Libera le risorse occupate durante la partita multiplayer
 * e attende un input da tastiera prima di proseguire
 * @param tets array dei tetramini da deallocare
*/
void multi_end_game(tet_t tets[TET_TYPES]);

#endif /*XTETRIS2_GAME_H*/
