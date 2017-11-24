#ifndef CURSOR_H
#define CURSOR_H

struct CursorTag;
typedef struct CursorTag Cursor;

Cursor Cursor_new(int line, int column);
Cursor Cursor_right(Cursor self);
Cursor Cursor_left(Cursor self);
Cursor Cursor_up(Cursor self);
Cursor Cursor_down(Cursor self);
void Cursor_test(void);

#endif
