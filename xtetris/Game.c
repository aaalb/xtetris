/**
* @file Game.c
* @author Albert Alibeaj
* @brief File di implementazione delle funzioni utilizzate per la partita
*/


#include <stdio.h>
#include "Game.h"
#include "GameGraphics.h"
#include "Player.h"

/** Macro che identifica che la partita è stata persa dopo una mossa */
#define MATCH_LOST (-1)
/** Macro che identifica che la partita è stata terminata per tornare al menu */
#define BACK_TO_MENU (-2)
/** Macro che identifica che una mossa è stata annullata e non ci sono state modifiche */
#define RETRY_TURN (-3)

/**
* Controlla se ci sono ancora tetramini disponibili da usare
 * @param tets array di tetramini da controllare
 * @return 1 se ci sono ancora tetramini utilizzabili, 0 altrimenti
*/
int tets_available(tet_t tets[TET_TYPES]);

/**
* Tramite input da tastiera, fa scegliere il tetramino stampandolo
 * @param tets array di tetramini da cui scegliere
 * @return indice del tetramino all'interno dell'array
*/
int choose_tet(tet_t tets[TET_TYPES]);

/**
* Tramite input da tastiera, fa scegliere la rotazione del tetramino stampandola
 * @param tet tetramino da ruotare
 * @return numero di rotazioni verso destra a partire dalla forma base
*/
int choose_rot(tet_t *tet);

/**
* Tramite input da tastiera, fa scegliere la colonna del campo stampando un'anteprima
 * @param field campo su cui scegliere la colonna
 * @param tet tetramino da inserire
 * @param rot numero rotazioni verso destra dalla forma base
 * @param player giocatore a cui appartiene il campo
 * @return numero di colonna scelto
*/
int choose_col(int field[FIELD_ROWS][FIELD_COLS], tet_t *tet, int rot, int player);

/**
* Inverte le ultime righe del campo
 * @param field campo su cui inveritire le righe
 * @param rows numero di righe a partire dal basso da invertire
*/
void xor_rows(int field[FIELD_ROWS][FIELD_COLS], int rows);

/**
* Attende l'input dell'utente per confermare l'uscita dalla partita
 * @return valore del tasto premuto
*/
int confirm_exit();

/**
* Turno completo di un giocatore. Sceglta di tetramino, rotazione, colonna e inserimento
 * @param field campo su cui inserire il tetramino
 * @param tets array da cui scegliere il tetramino
 * @param player giocatore a cui attribuire il turno
 * @param p_score punteggio del giocatore, aggiornato a ogni turno
 * @return valore positivo se ci sono ancora tetramini utilizzabili, valore negativo se si ha perso, bisogna uscire o ripetre il turno
*/
int turn(int field[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES], int player, int *p_score);

/**
* Turno completo del computer. Scelta casuale di tetramino, rotazione, colonna e inserimento
 * @param field campo su cui inserire il tetramino
 * @param tets array da cui scegliere il tetramino
 * @param player giocatore a cui attribuire il turno
 * @param p_score punteggio del giocatore, aggiornato a ogni turno
 * @return valore positivo se ci sono ancora tetramini utilizzabili, valore negativo se si ha perso, bisogna uscire o ripetre il turno
*/
int com_turn(int field[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES], int player, int *p_score);


/******************* Singleplayer ****************************/
/**
* Inizializza campo, tetramini e grafica per una partita singleplayer
 * @param field array da usare come campo di gioco
 * @param tets array di tetramini da inizializzare
*/
void single_init(int field[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES])
{
    field_init(field);
    tets_init(tets, 0);

    single_graphics_init();
}

void single_start_game(int field[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES])
{
    int p_res = 0;
    int score = 0;
    char *end_msg = (char*)malloc(sizeof (char) * 30);

    single_init(field, tets);

    do
    {
        p_res = turn(field, tets, player_one(), &score);
        clear_all();
    }
    while(p_res > 0 || p_res == RETRY_TURN);


    if(p_res == 0)
        sprintf(end_msg, "Hai vinto! Punteggio: %d", score);
    else if(p_res == MATCH_LOST)
        sprintf(end_msg, "Hai perso :( Punteggio: %d", score);
    else
        sprintf(end_msg, "Sei uscito dalla partita");

    print_game_over(end_msg);
    free(end_msg);
}

void single_end_game(tet_t tets[TET_TYPES])
{
    tets_free(tets);
    single_graphics_free();

    get_input();
    game_over_graphics_free();
}

/******************* Multiplayer *************************/
/**
* Inizializza campi, tetramini e grafica per una partita multiplayer
 * @param f1 array da usare come campo per il giocatore 1
 * @param f2 array da usare come campo per il giocatore 2
 * @param tets array di tetramini da inizializzare
*/
void multi_init(int f1[FIELD_ROWS][FIELD_COLS], int f2[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES])
{
    field_init(f1);
    field_init(f2);
    tets_init(tets, 1);

    multi_graphics_init();
}

void multi_start_game(int f1[FIELD_ROWS][FIELD_COLS], int f2[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES], int com)
{
    int p1_res, p2_res;
    int p1_score = 0, p2_score = 0;
    char *p2_name = com ? "COM" : "Giocatore 2";
    char *end_msg;

    multi_init(f1, f2, tets);
    do
    {
        int p1_score_prec = p1_score;
        int p2_score_prec = p2_score;

        print_player_field(f2, player_two());
        print_player_score(p2_score, player_two());

        if(!com) print_turn(1);

        do
            p1_res = turn(f1, tets, player_one(), &p1_score);
        while(p1_res == RETRY_TURN);

        if(p1_res != BACK_TO_MENU)
        {
            /*Se si tolgono 3 o più righe si invertono quelle dell'avversario*/
            if(p1_score - p1_score_prec == 6)
                xor_rows(f2, 3);
            if(p1_score - p1_score_prec == 12)
                xor_rows(f2, 4);


            print_player_field(f1, player_one());
            print_player_score(p1_score, player_one());

            if(!com) print_turn(0);
            do
                if(!com)
                    p2_res = turn(f2, tets, player_two(), &p2_score);
                else
                    p2_res = com_turn(f2, tets, player_two(), &p2_score);
            while(p2_res == RETRY_TURN);

            /*Ancora, controllo per invertire le righe dell'avversario*/
            if(p2_score - p2_score_prec == 6)
                xor_rows(f1, 3);
            if(p2_score - p2_score_prec == 12)
                xor_rows(f1, 4);
        }

        clear_all();
    }
    while(p1_res > 0 && p2_res > 0);

    /*Partita finita: Controllo risultati*/

    /*In caso di pareggio, vale il punteggio più alto*/
    end_msg = (char*)malloc(sizeof(char) * 80);
    if(p1_res == 1 && p2_res == 0)
    {
        if(p1_score > p2_score)
            sprintf(end_msg, com ? "Pezzi terminati. Hai vinto! (%d a %d)" : "Pezzi terminati. Vince Giocatore 1! (%d a %d)", p1_score, p2_score);
        else if(p2_score > p1_score)
            sprintf(end_msg, "Pezzi terminati. Vince %s! (%d a %d)", p2_name, p1_score, p2_score);
        else
            sprintf(end_msg, "Pezzi terminati. Pareggio :( (%d a %d)", p1_score, p2_score);
    }

    /*Caso vittoria giocatore 1*/
    if(p2_res == MATCH_LOST && p1_res >= 0)
        sprintf(end_msg, com ? "Hai vinto! (%d a %d)" : "Vince Giocatore 1! (%d a %d)", p1_score, p2_score);

    /*Caso vittoria giocatore 2*/
    if(p1_res == MATCH_LOST && p2_res >= 0)
        sprintf(end_msg, "Vince %s! (%d a %d)", p2_name, p1_score, p2_score);

    /*Entrambi i giocatori hanno perso allo stesso turno*/
    if(p1_res == MATCH_LOST && p2_res == MATCH_LOST)
        sprintf(end_msg, "Tutti hanno perso allo stesso momento. Pareggio :(");

    if(p1_res == BACK_TO_MENU)
        sprintf(end_msg, com ? "Sei uscito dalla partita" : "Giocatore 1 esce dalla partita");

    if(p2_res == BACK_TO_MENU)
        sprintf(end_msg, "%s esce dalla partita", p2_name);

    print_game_over(end_msg);
    free(end_msg);

}

void multi_end_game(tet_t tets[TET_TYPES])
{
    tets_free(tets);
    multi_graphics_free();

    get_input();
    game_over_graphics_free();
}

/**************** Funzioni private: implementazione ************************/
int turn(int field[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES], int player, int *p_score)
{
    int id, col, rot;
    int turn_score;

    /*Mostra il campo*/
    print_player_field(field, player);
    print_player_score(*p_score, player);

    /*Selezione della mossa*/
    id = choose_tet(tets);
    if(id != BACK_TO_MENU && id != RETRY_TURN)
    {
        rot = choose_rot(&tets[id]);
        if(rot != RETRY_TURN)
        {
            col = choose_col(field, &tets[id], rot, player);
            if(col != RETRY_TURN)
            {
                /* Inserimento ed elaborazione punteggio */
                turn_score = insert(field, &tets[id], col, rot);

                if(turn_score >= 0)
                    *p_score += turn_score;
                else
                    return MATCH_LOST;

                return tets_available(tets);
            }
            else
                return RETRY_TURN;
        }
        else
            return RETRY_TURN;
    }
    else
    if(id == BACK_TO_MENU)
        return confirm_exit();
    else
        return RETRY_TURN;
}

int com_turn(int field[FIELD_ROWS][FIELD_COLS], tet_t tets[TET_TYPES], int player, int *p_score)
{
    int id, col, rot;
    int turn_score;
    int tet_choice = 0;

    /*Mostra il campo*/
    print_player_field(field, player);
    print_player_score(*p_score, player);

    print_tet(tets[tet_choice]);

    /*Selezione della mossa*/
    do
        id = rand() % TET_TYPES;
    while(tets[id].quantity <= 0);

    rot = rand() % tets[id].rot_number;
    col = rand() % FIELD_COLS;

    /* Inserimento ed elaborazione punteggio */
    turn_score = insert(field, &tets[id], col, rot);

    if(turn_score >= 0)
        *p_score += turn_score;
    else
        return MATCH_LOST;

    return tets_available(tets);
}

int choose_tet(tet_t tets[TET_TYPES])
{
    int id = 0, tet_choice = 0;

    print_info("Usa le frecce per scegliere un tetramino o Backspace per uscire");
    while(tets[id].quantity <= 0)
    {
        if(id == TET_TYPES - 1) id = -1;
        id++;
    }
    print_tet(tets[id]);

    tet_choice = get_input();
    while(tet_choice != KEY_ENTER && tet_choice != KEY_BACKSPACE)
    {
        if(tet_choice == KEY_DOWN || tet_choice == KEY_LEFT)
        {
            do
            {
                if(id == TET_TYPES - 1) id = -1;
                id++;
            }
            while(tets[id].quantity <= 0);
        }
        else if(tet_choice == KEY_UP || tet_choice == KEY_RIGHT)
        {
            do
            {
                if (id == 0) id = TET_TYPES;
                id--;
            }
            while(tets[id].quantity <= 0);
        }
        print_tet(tets[id]);

        if(tets[id].quantity > 0)
            print_info("Usa le frecce per scegliere un tetramino o Backspace per uscire");
        else
            print_info("Non puoi piu' usare questo tetramino");

        tet_choice = get_input();
    }

    if(tet_choice == KEY_ENTER) /*Tasto invio*/
    {
        if(tets[id].quantity > 0)
            return id;
        else
            return RETRY_TURN;
    }
    else
        return BACK_TO_MENU;
}

int choose_rot(tet_t *tet)
{
    int rot_choice = 0, rot = 0;

    if(tet->rot_number <= 1) return 0;

    print_info("Usa le frecce per scegliere la rotazione o Backspace per annullare");
    rot_choice = get_input();
    while(rot_choice != KEY_ENTER && rot_choice != KEY_BACKSPACE)
    {
        if(rot_choice == KEY_UP || rot_choice == KEY_RIGHT)
        {
            if(rot == tet->rot_number - 1) rot = -1;
            rot++;
            rotate_dx(tet, 1);
        }
        else if(rot_choice == KEY_DOWN || rot_choice == KEY_LEFT)
        {
            if(rot == 0) rot = tet->rot_number;
            rot--;
            rotate_sx(tet, 1);
        }
        print_tet(*tet);

        rot_choice = get_input();
    }

    if(rot_choice == KEY_ENTER)
        return rot;
    else
    {
        reset_shape(tet);
        return RETRY_TURN;
    }
}

int choose_col(int field[FIELD_ROWS][FIELD_COLS], tet_t *tet, int rot, int player)
{
    int col = 0, col_choice = 0;

    print_info("Usa le frecce per scegliere la colonna o Backspace per annullare");
    do
    {
        int i, j, preview_score;
        int bkp_value;

        int preview_field[FIELD_ROWS][FIELD_COLS];
        for(i = 0; i < FIELD_ROWS; i++)
            for(j = 0; j < FIELD_COLS; j++)
                preview_field[i][j] = field[i][j];

        if(col_choice == KEY_RIGHT)
        {
            if(col == FIELD_COLS - tet_width(*tet)) col = -1;
            col++;
        }
        else if(col_choice == KEY_LEFT)
        {
            if(col == 0) col = FIELD_COLS - tet_width(*tet) + 1;
            col--;
        }

        bkp_value = tet->value;
        tet->value = 8;

        preview_score = insert(preview_field, tet, col, rot);

        tet->quantity++;
        tet->value = bkp_value;
        rotate_dx(tet, rot);

        print_player_field(preview_field, player);

        if(preview_score < 0)
            print_info("Con questa mossa perderai la partita");
        else
            print_info("Usa le frecce per scegliere la colonna o Backspace per annullare");

        col_choice = get_input();
    }
    while(col_choice != KEY_ENTER && col_choice != KEY_BACKSPACE);

    if(col_choice == KEY_ENTER)
        return col;
    else
    {
        reset_shape(tet);
        return RETRY_TURN;
    }
}

int tets_available(tet_t tets[TET_TYPES])
{
    int i;
    for(i = 0; i < TET_TYPES; i++)
    {
        if(tets[i].quantity)
            return 1;
    }
    return 0;
}

void xor_rows(int field[FIELD_ROWS][FIELD_COLS], int rows)
{
    int r, c;
    for(r = FIELD_ROWS - 1; r > FIELD_ROWS - 1 - rows; r--)
        for(c = 0; c < FIELD_COLS; c++)
            field[r][c] = field[r][c] ? 0 : TET_TYPES + 2;
}

int confirm_exit()
{
    int input;
    print_info("Premi ancora Backspace per uscire o un altro tasto per annullare");
    input = get_input();

    return input == KEY_BACKSPACE ? BACK_TO_MENU : RETRY_TURN;
}

