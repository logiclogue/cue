#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "cons.h"
#include "cons_line.h"
#include "cursor.h"
#include "editor.h"
#include "curses_interface.h"

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

void test(void) {
    cons_test();
    cons_line_test();
    cursor_test();
    editor_test();

    printf("All tests pass :)\n");
}

void start(const char file_name[]) {
    FILE *file = fopen(file_name, "r");

    Cons *cons = cons_from_file(file);
    Cursor cursor = cursor_new(0, 0);
    Editor editor = editor_new(cursor, cons);

    curses_interface_init();
    curses_interface_draw(editor);
    curses_interface_end();

    fclose(file);
}

int main(int n, char **argv) {
    if (n == 1) {
        test();
    } else if (n == 2) {
        start(argv[1]);
    }

    return 0;
}
