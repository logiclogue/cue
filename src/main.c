#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "cons.h"
#include "cons_line.h"
#include "cursor.h"

void curses_test(void) {
    initscr();

    printw("TESTING");
    raw();
    noecho();

    refresh();

    char c;

    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);

    while ((c = getch()) != 'J') {
        attron(A_BOLD);
        attron(COLOR_PAIR(1));
        mvprintw(10, 10, "%c", c);
        attroff(A_BOLD);
        attroff(COLOR_PAIR(1));
    }

    endwin();
}

int main(void) {
    cons_test();
    cons_line_test();
    cursor_test();

    printf("All tests pass :)\n");

    getc(stdin);

    FILE *file = fopen("src/main.c", "r");
    Cons *cons = cons_from_file(file);

    fclose(file);

    printf("%s\n", cons_to_string(cons));

    curses_test();

    return 0;
}
