/**
* @file MenuGraphics.h
* @author Albert Alibeaj
* @brief Libreria che si occupa della parte grafica
 * del programma, in particolare prepara il terminale e stampa il menu
*/
#ifndef XTETRIS_MENUGRAPHICS_H
#define XTETRIS_MENUGRAPHICS_H

/**
* Prepara il terminale per la visualizzazione
 * della grafica e l'input da tastiera
*/
void all_graphics_init();

/**
* Ripristina il terminale allo stato precedente
*/
void all_graphics_term();

/**
* Alloca e stampa il menu iniziale e permette la scelta di un'opzione
 * @return indice dell'opzione selezionata
*/
int print_start_menu();

/**
* Libera la memoria allocata per la grafica del menu iniziale
*/
void main_graphics_free();
#endif /*XTETRIS_MENUGRAPHICS_H*/
