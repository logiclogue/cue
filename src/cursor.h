#ifndef CURSOR_H
#define CURSOR_H

struct CursorTag;
typedef struct CursorTag Cursor;

Cursor cursor_new(int line, int column);
Cursor cursor_right(Cursor self);
Cursor cursor_left(Cursor self);
Cursor cursor_up(Cursor self);
Cursor cursor_down(Cursor self);
void cursor_test(void);

#endif
