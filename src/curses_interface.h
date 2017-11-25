#ifndef CURSES_INTERFACE_H
#define CURSES_INTERFACE_H

#include "editor.h"

void curses_interface_init(void);
void curses_interface_draw(Editor editor);
void curses_interface_end(void);

#endif
