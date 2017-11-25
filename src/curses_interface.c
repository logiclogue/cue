#include <ncurses.h>
#include "curses_interface.h"
#include "editor.h"
#include "cons.h"

void curses_interface_init(void) {
    initscr();
    keypad(stdscr, TRUE);
}

Editor curses_interface_draw(Editor editor) {
    char c;
    const char escape_code = 27;

    while ((c = getch()) != escape_code) {
        clear();

        editor = curses_interface_dispatch(c, editor);

        printw("%s", cons_to_string(editor.cons));
    }

    return editor;
}

Editor curses_interface_dispatch(char c, Editor editor) {
    printw("\n\n%d\n\n", c);
    if (c == 4) {
        return editor_new(cursor_left(editor.cursor), editor.cons);
    } else if (c == 5) {
        return editor_new(cursor_right(editor.cursor), editor.cons);
    } else if (c == 3) {
        return editor_new(cursor_up(editor.cursor), editor.cons);
    } else if (c == 2) {
        return editor_new(cursor_down(editor.cursor), editor.cons);
    }

    return editor_insert_char(c, editor);
}

void curses_interface_end(void) {
    endwin();
}
