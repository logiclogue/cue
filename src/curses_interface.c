#include <ncurses.h>
#include "curses_interface.h"
#include "editor.h"
#include "cons.h"
#include "cons_line.h"

#define KEY_ESCAPE 27
#define KEY_RETURN 10

void curses_interface_init(void) {
    initscr();
    keypad(stdscr, TRUE);
    noecho();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
}

Editor curses_interface_start(Editor editor) {
    int c;

    curses_interface_draw(editor);

    while ((c = getch()) != KEY_ESCAPE) {
        clear();

        editor = curses_interface_dispatch(c, editor);
        editor = editor_cursor_normalise(editor);

        curses_interface_draw(editor);

        refresh();
    }

    return editor;
}

void curses_interface_draw(Editor editor) {
    curses_interface_draw_text(editor);
    curses_interface_draw_bar(editor);
    curses_interface_draw_cursor(editor);
}

void curses_interface_draw_text(Editor editor) {
    mvprintw(0, 0, "%s", cons_to_string(editor.cons));
}

Editor curses_interface_dispatch(int c, Editor editor) {
    if (c == KEY_LEFT) {
        return editor_new(cursor_left(editor.cursor), editor.cons);
    } else if (c == KEY_RIGHT) {
        return editor_new(cursor_right(editor.cursor), editor.cons);
    } else if (c == KEY_UP) {
        return editor_new(cursor_up(editor.cursor), editor.cons);
    } else if (c == KEY_DOWN) {
        return editor_new(cursor_down(editor.cursor), editor.cons);
    } else if (c == KEY_BACKSPACE || c == 127) {
        return editor_backspace(editor);
    } else if (c == KEY_DC) {
        return editor_delete(editor);
    } else if (c == KEY_RETURN) {
        return editor_newline(editor);
    }

    return editor_insert_char(c, editor);

}

void curses_interface_draw_cursor(Editor editor) {
    attron(A_BOLD);
    attron(COLOR_PAIR(1));

    move(editor.cursor.line, editor.cursor.column);

    attroff(A_BOLD);
    attroff(COLOR_PAIR(1));
}

void curses_interface_draw_bar(Editor editor) {
    mvprintw(LINES - 1, 0, "%d %d %d",
        cons_get_memory_usage(),
        editor.cursor.line,
        editor.cursor.column);
}

void curses_interface_end(void) {
    endwin();
}
