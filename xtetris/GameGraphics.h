/**
* @file GameGraphics.h
* @author Albert Alibeaj
* @brief Libreria che si occupa della parte grafica
 * del programma, in particolare stampa campi, tetramini, punteggi e messaggi
*/

#ifndef XTETRIS2_GRAPHICS_H
#define XTETRIS2_GRAPHICS_H

#include "Field.h"
#include "Pieces.h"

#define KEY_DOWN (258)      /**< valore del tasto freccia giù */
#define KEY_UP (259)        /**< valore del tasto freccia su */
#define KEY_LEFT (260)      /**< valore del tasto freccia sinistra */
#define KEY_RIGHT (261)     /**< valore del tasto freccia destra */
#define KEY_ENTER (10)      /**< valore del tasto INVIO */
#define KEY_BACKSPACE (127) /**< valore del tasto BACKSPACE */



/**
* Alloca la memoria per la grafica di una partita singleplayer
*/
void single_graphics_init();

/**
* Alloca la memoria per la grafica di una partita multiplayer
*/
void multi_graphics_init();


/**
* Stampa a video un tetramino, nel suo riquadro
 * e con la forma (rotazione) corrente
 * @param tet il tetramino da stampare
*/
void print_tet(tet_t tet);

/**
* Stampa una stringa nel riquadro informazioni,
 * con a capo automatico e senza spezzare le parole
 * @param info stringa da stampare
*/
void print_info(char* info);

/**
* Stampa il campo di un giocatore nel suo riquadro.
 * Distingue i tetramini e usa colri diversi per ciascuno
 * @param field campo da stampare
 * @param player giocatore per il quale stampare il campo
*/
void print_player_field(int field[FIELD_ROWS][FIELD_COLS], int player);

/**
* Stampa il punteggio di un giocatore nel suo riquadro.
 * @param score valore da stampare
 * @param player giocatore per il quale stampare il punteggio
*/
void print_player_score(int score, int player);

/**
* Stampa una freccia che indica di chi è il turno.
 * @param direction_sx se TRUE la freccia punta a sinistra, altrimenti a destra
*/
void print_turn(int direction_sx);

/**
* Stampa la schermata di game over, con una stringa di specificazione,
 * con a capo automatico e senza spezzare le parole
 * @param info stringa da stampare
*/
void print_game_over(char* info);

/**
* Libera la memoria allocata per la grafica di una partita singleplayer
*/
void single_graphics_free();

/**
* Libera la memoria allocata per la grafica di una partita multiplayer
*/
void multi_graphics_free();

/**
* Libera la memoria allocata per la grafica del game over
*/
void game_over_graphics_free();

/**
* Cancella tutta la grafica dalla schermata
*/
void clear_all();

/**
* Attende l'input da tastiera dell'utente
 * @return valore del tasto premuto
*/
int get_input();

#endif /*XTETRIS2_GRAPHICS_H*/
