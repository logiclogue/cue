#ifndef CURSES_INTERFACE_H
#define CURSES_INTERFACE_H

#include "editor.h"

void curses_interface_init(void);
Editor curses_interface_draw(Editor editor);
void curses_interface_end(void);
Editor curses_interface_dispatch(char c, Editor editor);
void curses_interface_draw_cursor(Editor editor);

#endif
