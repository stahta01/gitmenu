#include <stdio.h>
#include <curses.h>

// based on https://github.com/cpressey/ncurses_programs/blob/master/basics/simple_key.c

const int TERMINAL_WIDTH=80;
const int TERMINAL_HEIGHT=24;

const int WIDTH=50;
const int HEIGHT=9;
const int MENU_TOP_OFFSET=1;
const int MENU_LEFT_OFFSET=2;

const int START_X = (TERMINAL_WIDTH - WIDTH) / 2;
const int START_Y = (TERMINAL_HEIGHT - HEIGHT) / 2;

const char *choices[] =
{
    "git push --help",
    "git push",
    "git push origin",
    "git pull --rebase",
    "git pull --rebase && git push",
    "git checkout master && ... && git push origin",
    "Exit",
};
int const n_choices = sizeof(choices) / sizeof(char *);
void print_menu(WINDOW *menu_win, const int highlight);

int main()
{
    WINDOW *menu_win;
    int highlight = n_choices;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();

    menu_win = newwin(HEIGHT, WIDTH, START_Y, START_X);
    keypad(menu_win, TRUE);
    mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
    refresh();
    print_menu(menu_win, highlight);
    while(1)
    {
        c = wgetch(menu_win);
        switch(c)
        {
        case KEY_UP:
            if(highlight == 1)
                highlight = n_choices;
            else
                --highlight;
            break;
        case KEY_DOWN:
            if(highlight == n_choices)
                highlight = 1;
            else
                ++highlight;
            break;
        case '\n':
            choice = highlight;
            break;
        default:
            refresh();
            break;
        }
        print_menu(menu_win, highlight);
        if(choice != 0)
            break;
    }
    clrtoeol();
    refresh();
    endwin();
    if (choice >= n_choices)
    {
        return 0;
    }
    else
    {
        return choice;
    }
}

void print_menu(WINDOW *menu_win, const int highlight)
{
    int y = MENU_TOP_OFFSET;

    box(menu_win, 0, 0);
    for(int i = 0; i < n_choices; ++i)
    {
        if(highlight == i + 1)
        {
            /* High light the present choice */
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, MENU_LEFT_OFFSET, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        }
        else
            mvwprintw(menu_win, y, MENU_LEFT_OFFSET, "%s", choices[i]);
        ++y;
    }
    wrefresh(menu_win);
}
