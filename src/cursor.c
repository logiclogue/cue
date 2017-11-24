#include <assert.h>
#include "cursor.h"

struct CursorTag {
    int line;
    int column;
};

Cursor cursor_new(int line, int column) {
    return (Cursor) {
        line = line,
        column = column
    };
}

Cursor cursor_right(Cursor self) {
    return cursor_new(self.line, self.column + 1);
}

Cursor cursor_left(Cursor self) {
    return cursor_new(self.line, self.column - 1);
}

Cursor cursor_up(Cursor self) {
    return cursor_new(self.line - 1, self.column);
}

Cursor cursor_down(Cursor self) {
    return cursor_new(self.line + 1, self.column);
}

void cursor_test(void) {
    Cursor cursor = cursor_new(42, 21);

    assert(cursor.line == 42);
    assert(cursor.column == 21);
    assert(cursor_right(cursor).column == 22);
    assert(cursor_left(cursor).column == 20);
    assert(cursor_up(cursor).line == 41);
    assert(cursor_down(cursor).line == 43);
}
