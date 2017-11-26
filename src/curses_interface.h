#ifndef CURSES_INTERFACE_H
#define CURSES_INTERFACE_H

#include "editor.h"

void curses_interface_init(void);
Editor curses_interface_start(Editor editor);
void curses_interface_draw(Editor editor);
void curses_interface_end(void);
Editor curses_interface_dispatch(int c, Editor editor);
void curses_interface_draw_cursor(Editor editor);
void curses_interface_draw_text(Editor editor);
void curses_interface_draw_line(int line, Editor editor);
void curses_interface_draw_bar(Editor editor);

#endif
