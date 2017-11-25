#include <ncurses.h>
#include "curses_interface.h"
#include "editor.h"
#include "cons.h"

void curses_interface_init(void) {
    initscr();
}

void curses_interface_draw(Editor editor) {
    char current_char;
    const char escape_code = 27;

    while ((current_char = getch()) != escape_code) {
        clear();

        editor = editor_insert_char(current_char, editor);

        printw("%s", cons_to_string(editor.cons));
    }
}

void curses_interface_end(void) {
    endwin();
}
