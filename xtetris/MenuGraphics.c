/**
* @file MenuGraphics.c
* @author Albert Alibeaj
* @brief File di implementazione delle funzioni grafiche utilizzate per la partita
*/

#include "MenuGraphics.h"

#include <stdlib.h>
#include <menu.h>
#include <ncurses.h>

WINDOW *main_menu_win;              /**< finestra che contiene la grafica del menu iniziale  */
WINDOW *title_win;                  /**< finestra che contiene la grafica del nome X-Tetris */
WINDOW *author_win;                 /**< finestra che contiene la grafica del nome dell'autore */


/* Inizializza il terminale */
void all_graphics_init()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, 1);
    start_color();
}

void all_graphics_term()
{
    endwin();
}

/* Menu iniziale */
int print_start_menu()
{
    int menu_items_count = 4;
    char *menu_texts[] = { "SinglePlayer", "MultiPlayer", "MultiPlayer", "Esci"};
    char *menu_desc[] = {"", "Player vs Player", "Player vs COM", ""};
    ITEM **menu_items = (ITEM**)malloc(sizeof (ITEM*) * menu_items_count + 1);
    MENU *main_menu;

    int i, c;
    int selected = -1;

    clear();

    title_win = newwin(8, 40, 7, 27);
    mvwprintw(title_win, 0, 0, "   _  __    ______     __       _     \n"
                               "  | |/ /   /_  __/__  / /______(_)____\n"
                               "  |   /_____/ / / _ \\/ __/ ___/ / ___/\n"
                               " /   /_____/ / /  __/ /_/ /  / (__  ) \n"
                               "/_/|_|    /_/  \\___/\\__/_/  /_/____/  \n"
                               "                                      ");

    for(i = 0; i < menu_items_count; i++)
        menu_items[i] = new_item(menu_texts[i], menu_desc[i]);
    menu_items[i] = NULL;

    main_menu = new_menu(menu_items);

    main_menu_win = newwin(8, 40, 15, 25);
    keypad(main_menu_win, 1);
    set_menu_win(main_menu, main_menu_win);
    set_menu_sub(main_menu, derwin(main_menu_win, 5, 38, 3, 1));
    set_menu_mark(main_menu, "-  ");

    box(main_menu_win, '|', '=');
    mvwprintw(main_menu_win, 1, 8, "The X-Tetris Experience");

    author_win = newwin(1, 20, 25, 25);
    mvwprintw(author_win, 0, 0, "2022 Albert Alibeaj");

    refresh();

    /* Post the menu */
    post_menu(main_menu);
    wrefresh(main_menu_win);
    wrefresh(title_win);
    wrefresh(author_win);

    while(selected < 0)
    {
        c = getch();
        switch(c)
        {	case KEY_DOWN:
                menu_driver(main_menu, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(main_menu, REQ_UP_ITEM);
                break;
            case 10:
                selected = item_index(current_item(main_menu));
                break;
            default:
                break;
        }
        wrefresh(main_menu_win);
    }

    /* Unpost and free all the memory taken up */
    unpost_menu(main_menu);
    free_menu(main_menu);
    for(i = 0; i < menu_items_count + 1; i++)
        free_item(menu_items[i]);

    clear();

    return selected;
}

void main_graphics_free()
{
    delwin(main_menu_win);
    delwin(title_win);
    delwin(author_win);
}
