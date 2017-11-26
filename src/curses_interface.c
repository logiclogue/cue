#include <ncurses.h>
#include "curses_interface.h"
#include "editor.h"
#include "cons.h"

#define KEY_LEFT 4
#define KEY_RIGHT 5
#define KEY_UP 3
#define KEY_DOWN 2
#define KEY_BACKSPACE 127

void curses_interface_init(void) {
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    init_pair(1, COLOR_BLACK, COLOR_GREEN);
}

Editor curses_interface_draw(Editor editor) {
    char c;
    const char escape_code = 27;

    while ((c = getch()) != escape_code) {
        refresh();

        editor = curses_interface_dispatch(c, editor);

        curses_interface_draw_text(editor);
        curses_interface_draw_cursor(editor);
    }

    return editor;
}

void curses_interface_draw_text(Editor editor) {
    mvprintw(0, 0, "%s", cons_to_string(editor.cons));
    mvprintw(0, 0, "%d", cons_get_memory_usage());
}

Editor curses_interface_dispatch(char c, Editor editor) {
    if (c == KEY_LEFT) {
        return editor_new(cursor_left(editor.cursor), editor.cons);
    } else if (c == KEY_RIGHT) {
        return editor_new(cursor_right(editor.cursor), editor.cons);
    } else if (c == KEY_UP) {
        return editor_new(cursor_up(editor.cursor), editor.cons);
    } else if (c == KEY_DOWN) {
        return editor_new(cursor_down(editor.cursor), editor.cons);
    } else if (c == KEY_BACKSPACE) {
        return editor_backspace(editor);
    }

    return editor_insert_char(c, editor);
}

void curses_interface_draw_cursor(Editor editor) {
    attron(A_BOLD);
    attron(COLOR_PAIR(1));

    mvprintw(editor.cursor.line, editor.cursor.column, "");

    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));
}

void curses_interface_end(void) {
    endwin();
}
