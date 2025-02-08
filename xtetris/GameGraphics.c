/**
* @file GameGraphics.c
* @author Albert Alibeaj
* @brief File di implementazione delle funzioni grafiche utilizzate per la partita
*/

#include "GameGraphics.h"
#include <math.h>
#include <string.h>
#include <ncurses.h>

#include "Player.h"

#define COLOR_ORANGE 8              /**< identificativo del colore arancione che è stato ridefinito */
#define COLOR_INV    9              /**< identificativo del colore da usare per le righe invertite (multiplayer) */

char* char_empty_field = "   ";     /**< codifica cella del campo vuota */
char* char_value_field = "[#]";     /**< codifica cella del campo piena */
char* char_value_invalid = "[X]";   /**< codifica cella fuori dal campo */

WINDOW *main_window;                /**< finestra che contiene la sottofinestre per la grafica della partita */
WINDOW *field_window;               /**< sottofinestra che contiene la grafica del campo 1  */
WINDOW *score_window;               /**< sottofinestra che contiene la grafica del punteggio 1 */
WINDOW *tet_window;                 /**< sottofinestra che contiene la grafica dei tetramini */
WINDOW *info_window;                /**< sottofinestra che contiene la grafica del box informazioni */

WINDOW *second_field_window;        /**< sottofinestra che contiene la grafica del campo 2 (multiplayer) */
WINDOW *second_score_window;        /**< sottofinestra che contiene la grafica del punteggio 2 (multiplayer) */
WINDOW *turn_window;                /**< sottofinestra che contiene la grafica della freccia che indica il turno (multiplayer) */

WINDOW *game_over_window;           /**< finestra che contiene la grafica della schermata di game over */

/**
* Inizializza variabili contenenti i colori da utiilizzare nel terminale
*/
void init_colors();

/**
* Stampa il campo in una finestra specifica (parte della schermata intera)
 * @param field campo da stampare
 * @param win finestra su cui stampare il campo
*/
void print_field(int field[FIELD_ROWS][FIELD_COLS], WINDOW *win);

/**
* Stampa il punteggio in una finestra specifica (parte della schermata intera)
 * @param value punteggio da stampare
 * @param win finestra su cui stampare il punteggio
*/
void print_score(int value, WINDOW *win);

/**
* Stampa il testo in una finestra con a capo automatico e senza spezzare le parole
 * @param info testo da stampare
 * @param win finestra su cui stampare la stringa
 * @param y_start riga della finestra da cui iniziare la stampa
 * @param x_start colonna della finestra da cui iniziare la stampa
 * @param n_rows numero di righe utilizzabili per la stampa
 * @param n_cols numero di colonne ultizzabili per la stampa
*/
void print_text_helper(char* info, WINDOW *win, int y_start, int x_start, int n_rows, int n_cols);

/*SinglePlayer*/
void single_graphics_init()
{
    int fw_h = VALID_ROWS + 2 + 1, fw_w = FIELD_COLS * 3 + 2;
    int sw_h = 3, sw_w = 5;
    int tw_h = 5 + 2, tw_w = 5 * 3 + 2;
    int iw_h = 5, iw_w = 30;

    main_window = newwin(0, 0, 5, 5);

    field_window = derwin(main_window, fw_h, fw_w, 0, 0);
    mvwaddch(field_window, 1, 0, '+');                      /*Angolo alto sinistra*/
    mvwhline(field_window, 1, 1, '-', fw_w - 2);            /*Bordo superiore*/
    mvwaddch(field_window, 1, fw_w - 1, '+');               /*Angolo alto destra*/
    mvwvline(field_window, 2, fw_w - 1, '/', fw_h - 2);     /*Bordo destro*/
    mvwaddch(field_window, fw_h - 1, fw_w - 1, '+');        /*Angolo basso destra*/
    mvwhline(field_window, fw_h - 1, 1, '-', fw_w - 2);     /*Bordo inferiore*/
    mvwaddch(field_window, fw_h - 1, 0, '+');               /*Angolo basso sinistra*/
    mvwvline(field_window, 2, 0, '\\', (fw_h - 2) - 1);     /*Bordo sinistro*/

    score_window = derwin(main_window, sw_h, sw_w, 0, fw_w + 2);
    box(score_window, '|', '-');

    tet_window = derwin(main_window, tw_h, tw_w, sw_h + 2, fw_w + 2);
    box(tet_window, '|', '-');

    info_window = derwin(main_window, iw_h, iw_w, sw_h + tw_h + 4, fw_w + 2);
    box(info_window, '|', '-');

    init_colors();
}

/*MultiPlayer*/
void multi_graphics_init()
{
    int fw_h = VALID_ROWS + 2 + 1, fw_w = FIELD_COLS * 3 + 2;
    int sw_h = 3, sw_w = 5;
    int tw_h = 5 + 2, tw_w = 5 * 3 + 2;
    int iw_h = 5, iw_w = 30;

    main_window = newwin(0, 0, 6, 6);

    field_window = derwin(main_window, fw_h, fw_w, 0, 0);
    mvwaddch(field_window, 1, 0, '+');                      /*Angolo alto sinistra*/
    mvwhline(field_window, 1, 1, '-', fw_w - 2);            /*Bordo superiore*/
    mvwaddch(field_window, 1, fw_w - 1, '+');               /*Angolo alto destra*/
    mvwvline(field_window, 2, fw_w - 1, '/', fw_h - 2);     /*Bordo destro*/
    mvwaddch(field_window, fw_h - 1, fw_w - 1, '+');        /*Angolo basso destra*/
    mvwhline(field_window, fw_h - 1, 1, '-', fw_w - 2);     /*Bordo inferiore*/
    mvwaddch(field_window, fw_h - 1, 0, '+');               /*Angolo basso sinistra*/
    mvwvline(field_window, 2, 0, '\\', (fw_h - 2) - 1);     /*Bordo sinistro*/

    score_window = derwin(main_window, sw_h, sw_w, 0, fw_w + 3);
    box(score_window, '|', '-');

    tet_window = derwin(main_window, tw_h, tw_w, sw_h + 2, fw_w + 9);
    box(tet_window, '|', '-');

    info_window = derwin(main_window, iw_h, iw_w, sw_h + tw_h + 4, fw_w + 3);
    box(info_window, '|', '-');

    second_score_window = derwin(main_window, sw_h, sw_w, 0, fw_w + sw_w + tw_w + 6);
    box(second_score_window, '|', '-');

    second_field_window = derwin(main_window, fw_h, fw_w, 0, fw_w + sw_w + tw_w + sw_w + 9);
    mvwaddch(second_field_window, 1, 0, '+');                   /*Angolo alto sinistra*/
    mvwhline(second_field_window, 1, 1, '-', fw_w - 2);         /*Bordo superiore*/
    mvwaddch(second_field_window, 1, fw_w - 1, '+');            /*Angolo alto destra*/
    mvwvline(second_field_window, 2, fw_w - 1, '/', fw_h - 2);  /*Bordo destro*/
    mvwaddch(second_field_window, fw_h - 1, fw_w - 1, '+');     /*Angolo basso destra*/
    mvwhline(second_field_window, fw_h - 1, 1, '-', fw_w - 2);  /*Bordo inferiore*/
    mvwaddch(second_field_window, fw_h - 1, 0, '+');            /*Angolo basso sinistra*/
    mvwvline(second_field_window, 2, 0, '\\', (fw_h - 2) - 1);  /*Bordo sinistro*/

    turn_window = derwin(main_window, 4, 17, 0, fw_w + sw_w + 6);

    init_colors();

}

void init_colors()
{
    init_color(COLOR_ORANGE, 1000, 560, 0);
    init_color(COLOR_RED, 929, 82, 196);
    init_color(COLOR_YELLOW, 921, 905, 74);
    init_color(COLOR_BLUE, 74, 156, 921);
    init_color(COLOR_INV, 74, 921, 737);

    init_pair(1, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_ORANGE, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    init_pair(6, COLOR_GREEN, COLOR_BLACK);
    init_pair(7, COLOR_RED, COLOR_BLACK);
    init_pair(8, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_INV, COLOR_BLACK);
}

/*Comuni*/
void print_text_helper(char* info, WINDOW *win, int y_start, int x_start, int n_rows, int n_cols)
{
    int i, curs_i;
    int r = y_start;
    int len = strlen(info);

    wmove(win, r, x_start);

    curs_i = 0;
    for(i = 0; i < len && i < n_cols * n_rows - 1; i++)
    {
        int newline = 0;

        if (curs_i > 0 && curs_i % n_cols == 0)
            newline = 1;

        if (!newline && info[i] == ' ')
        {
            int sublen = 0;
            int sub_i = i + 1;
            while (info[sub_i] != ' ' && sub_i != len)
            {
                sublen++;
                sub_i++;
            }

            if (sublen < n_cols && curs_i + sublen >= n_cols)
            {
                newline = 1;
            }
        }

        if (newline)
        {
            wmove(win, ++r, x_start);
            curs_i = 0;
        }

        if (curs_i > 0 || info[i] != ' ')
        {
            waddch(win, info[i]);
            curs_i++;
        }
    }
}

void print_field(int field[FIELD_ROWS][FIELD_COLS], WINDOW* win)
{
    int i, j;

    wmove(win, 0, 1);
    for(i = INVALID_ROWS - 1; i < FIELD_ROWS; i++)
    {
        char* char_value;
        if(i == INVALID_ROWS - 1)
        {
            char_value = malloc(strlen(char_value_invalid) + 1);
            strcpy(char_value, char_value_invalid);
            wmove(win, 0, 1);
        }
        else
        {
            char_value = malloc(strlen(char_value_field) + 1);
            strcpy(char_value, char_value_field);
            wmove(win, i - INVALID_ROWS + 2, 1);
        }

        for(j = 0; j < FIELD_COLS; j++)
        {
            int val = field[i][j];

            wattron(win, COLOR_PAIR(val));
            wprintw(win, "%s", val ? char_value : char_empty_field);
            wattroff(win, COLOR_PAIR(val));
        }

        free(char_value);
    }

    refresh();
    wrefresh(win);
}

void print_tet(tet_t tet)
{
    int i, j;
    int qdigits;

    /*wclear(tet_window);*/
    for(i = 0; i < 4; i++)
    {
        wmove(tet_window, i + 1, 1);
        for(j = 0; j < 4; j++)
        {
            wprintw(tet_window, "%s", char_empty_field);
        }
    }
    wmove(tet_window, 5, 5 * 3 - 1 - (log10(DEFAULT_TET_QUANTITY) + 1));
    for(i = 0; i < log10(DEFAULT_TET_QUANTITY) + 1; i++)
        wprintw(tet_window, " ");

    for(i = 0; i < tet.shape_len; i++)
    {
        wmove(tet_window, i + 1, 1);
        for(j = 0; j < tet.shape_len; j++)
        {
            int val = tet.shape[i * tet.shape_len + j];

            wattron(tet_window, COLOR_PAIR(val));
            wprintw(tet_window, "%s", val ? char_value_field : char_empty_field);
            wattroff(tet_window, COLOR_PAIR(val));
        }
    }

    qdigits = tet.quantity > 0 ? log10(tet.quantity) + 1 : 1;
    mvwprintw(tet_window, 5, 5 * 3 - qdigits, "%d", tet.quantity);

    refresh();
    wrefresh(tet_window);

}

void print_score(int value, WINDOW *win)
{
    int digits = value > 0 ? (log10(value)) + 1 : 1;
    mvwprintw(win, 1, 5 - 1 - digits, "%d", value);

    refresh();
    wrefresh(win);
}

void print_info(char* info)
{
    int i, r;

    /*Ripulisce il testo precedente*/
    r = 1;
    wmove(info_window, 1, 1);
    for(i = 0; i < (30 - 2) * (5 - 2); i++)
    {
        if(i > 0 && i % 28 == 0)
            wmove(info_window, ++r, 1);
        waddch(info_window, ' ');
    }

    /*scrive il testo nuovo*/
    print_text_helper(info, info_window, 1, 1, 5 - 2, 30 - 2);

    refresh();
    wrefresh(info_window);
}

void print_game_over(char* info)
{
    game_over_window = newwin(15, 60, 7, 27);
    mvwprintw(game_over_window, 0, 0,
                                      "   _____                         ____                 \n"
                                      "  / ____|                       / __ \\                \n"
                                      " | |  __  __ _ _ __ ___   ___  | |  | |_   _____ _ __ \n"
                                      " | | |_ |/ _` | '_ ` _ \\ / _ \\ | |  | \\ \\ / / _ \\ '__|\n"
                                      " | |__| | (_| | | | | | |  __/ | |__| |\\ V /  __/ |   \n"
                                      "  \\_____|\\__,_|_| |_| |_|\\___|  \\____/  \\_/ \\___|_|   \n"
                                      "                                                      ");

    mvwhline(game_over_window, 8, 7, '=', 40);
    mvwhline(game_over_window, 14, 7, '=', 40);

    print_text_helper(info, game_over_window, 9, 8, 7 - 2 - 1, 40 - 2);

    mvwprintw(game_over_window, 13, 8, "Premi qualsiasi tasto per uscire");

    refresh();
    wrefresh(game_over_window);
}

void single_graphics_free()
{
    delwin(field_window);
    delwin(score_window);
    delwin(tet_window);
    delwin(info_window);
    delwin(main_window);
}

void multi_graphics_free()
{
    delwin(field_window);
    delwin(score_window);
    delwin(second_field_window);
    delwin(second_score_window);
    delwin(tet_window);
    delwin(info_window);
    delwin(turn_window);
    delwin(main_window);
}


void game_over_graphics_free()
{
    delwin(game_over_window);
}


/*Funzioni che nascondono la parte grafica*/
void print_player_field(int field[FIELD_ROWS][FIELD_COLS], int player)
{
    if(player == player_one())
        print_field(field, field_window);
    if(player == player_two())
        print_field(field, second_field_window);
}
void print_player_score(int score, int player)
{
    if(player == player_one())
        print_score(score, score_window);
    if(player == player_two())
        print_score(score, second_score_window);
}

void print_turn(int direction_sx)
{
    wclear(turn_window);
    if(direction_sx)
    {
        mvwprintw(turn_window, 0, 0,
                                     "  ___      \n"
                                     " / /_____  \n"
                                     "|  _____] \n"
                                     " \\_\\_    \n");
    }
    else
    {
        mvwprintw(turn_window, 0, 0,
                                     "       ___   \n"
                                     "   _____\\ \\  \n"
                                     "   [_____  |  \n"
                                     "       _/_/  \n");
    }

    refresh();
    wrefresh(turn_window);
}

void clear_all()
{
    clear();
}
int get_input()
{
    return getch();
}


