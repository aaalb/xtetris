/**
* @file main.c
* @author Albert Alibeaj
 *@brief Programma principale, che sarà lanciato
 *
* @mainpage Programma principale
* @section intro_sec Introduzione
*
 * X-Tetris è una particolare versione del Tetris in cui si ha una quantità limitata
 * di pezzi da scegliere. Puoi scegliere il pezzo che preferisci, sempre che il
 * pezzo sia disponibile.
 * Puoi giocare da solo, con un amico o contro il computer. Usa le frecce per muoverti
 * e il tasto INVIO per confermare
*
* @section install_sec Installazione
 * Segui queste istruzioni per iniziare a giocare a X-Tetris
 *
* @subsection step1 Step 1: Installa gcc o clang
 * Se sei su Ubuntu puoi usare i comandi
 *   <br><code>sudo apt update</code>
 *   <br><code>sudo apt install build-essential</code>
 *
 * Se invece la tua macchina ha sistema operativo macOS usa il comando
 *  <br><code>xcode-select --install</code>
 *
* @subsection step2 Step 2: Installa ncurses
 * Per visualizzare la grafica del programma è necessaria la libreria
 * ncurses, che permette di lavorare in modo più avanzato con la
 * grafica del terminale.
 *
 * Se sei su Ubuntu puoi usare il comando
 *   <br><code>sudo apt-get install libncurses5-dev libncursesw5-dev</code>
 *
 * Su macOS ncurses si può installare tramite homebrew dal seguente comando
 *  <br><code>brew install ncurses</code>
 *
 * @subsection step3 Step 3: Compila il programma
 * Per compilare velocemente il programma, si può aprire il progetto
 * con CLion e usare CMake per produrre l'eseguibile, tramite il file
 * CMakeLists.txt che si occupa della compilazione e del linking.
 * Per compilare invece da terminale, basta digitare il seguente comando
 *
 * <code>gcc -ansi -pedantic-errors -Wall -O3
 *  -L{ncurses_lib_path}
 *  main.c Field.c Pieces.c Moves.c Game.c GameGraphics.c MenuGraphics.c Player.c
 *  -lmenu -lncurses -oxtetris</code>
 *
 *  dove {ncurses_lib_path} è il percorso delle librerie da linkare (menu e ncurses).
 *  Cambia a seconda dell'installazione. Un esempio è <code>/opt/homebrew/opt/ncurses/lib</code>
 *
 * @subsection final Installazione terminata
 * Ora il programma è pronto per essere lanciato. Digita <code>./xtetris</code> da terminale per iniziare.
*/


#include <stdio.h>
#include <time.h>
#include "Game.h"
#include "MenuGraphics.h"

/**
 * Programma principale, richiama il menu iniziale
 * e a seconda di cosa si sceglie, fa iniziare un certo tipo
 * di partita. Il processo si ripete ciclicamente finchè non si esce.
 * @return 0 se il programma termina correttamente
*/
int main() {
    const int SINGLEPLAYER_MODE = 0;
    const int MULTIPLAYER_MODE = 1;
    const int PLAYER_VS_COM_MODE = 2;
    const int EXIT_GAME = 3;
    int mode;

    all_graphics_init();
    srand((unsigned int)time(NULL));

    do
    {
        mode = print_start_menu();

        if(mode == SINGLEPLAYER_MODE)
        {
            int field[FIELD_ROWS][FIELD_COLS];
            tet_t tets[TET_TYPES];

            main_graphics_free();

            single_start_game(field, tets);
            single_end_game(tets);
        }
        if(mode == MULTIPLAYER_MODE)
        {
            int p1_field[FIELD_ROWS][FIELD_COLS];
            int p2_field[FIELD_ROWS][FIELD_COLS];
            tet_t tets[TET_TYPES];


            main_graphics_free();

            multi_start_game(p1_field, p2_field, tets, 0);
            multi_end_game(tets);
        }
        if(mode == PLAYER_VS_COM_MODE)
        {
            int p_field[FIELD_ROWS][FIELD_COLS];
            int com_field[FIELD_ROWS][FIELD_COLS];
            tet_t tets[TET_TYPES];

            main_graphics_free();

            multi_start_game(p_field, com_field, tets, 1);
            multi_end_game(tets);
        }

    } while (mode != EXIT_GAME);

    all_graphics_term();

    return 0;
}
