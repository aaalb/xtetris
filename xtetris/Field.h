/**
* @file Field.h
* @author Albert Alibeaj
* @brief Libreria che definisce le dimensioni del campo
 * e lo inizializza vuoto
*/

#ifndef XTETRIS2_FIELD_H
#define XTETRIS2_FIELD_H

 /** Le righe sopra il campo giocabile*/
#define INVALID_ROWS (4)
 /** Le righe del campo visibili e giocabili*/
#define VALID_ROWS (15)
 /** Totale delle righe del campo*/
#define FIELD_ROWS (INVALID_ROWS + VALID_ROWS)
 /** Colonne del campo*/
#define FIELD_COLS (10)

/**
* Inizializza un campo di gioco vuoto
 * @param field array di interi che si vuole usare come campo
*/
void field_init(int field[FIELD_ROWS][FIELD_COLS]);

#endif /*XTETRIS2_FIELD_H*/
