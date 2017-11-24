#include <assert.h>
#include "Cursor.h"

struct CursorTag {
    int line;
    int column;
};

Cursor Cursor_new(int line, int column) {
    return (Cursor) {
        line = line,
        column = column
    };
}

Cursor Cursor_right(Cursor self) {
    return Cursor_new(self.line, self.column + 1);
}

Cursor Cursor_left(Cursor self) {
    return Cursor_new(self.line, self.column - 1);
}

Cursor Cursor_up(Cursor self) {
    return Cursor_new(self.line - 1, self.column);
}

Cursor Cursor_down(Cursor self) {
    return Cursor_new(self.line + 1, self.column);
}

void Cursor_test(void) {
    Cursor cursor = Cursor_new(42, 21);

    assert(cursor.line == 42);
    assert(cursor.column == 21);
    assert(Cursor_right(cursor).column == 22);
    assert(Cursor_left(cursor).column == 20);
    assert(Cursor_up(cursor).line == 41);
    assert(Cursor_down(cursor).line == 43);
}
