#include <assert.h>
#include "editor.h"
#include "cursor.h"
#include "cons.h"

Editor editor_new(Cursor cursor, Cons *cons) {
    return (Editor) {
        cursor = cursor,
        cons = cons
    };
}

void editor_test() {
    Cursor cursor = cursor_new(42, 21);
    Editor editor = editor_new(cursor, cons_empty());

    assert(cons_is_empty(editor.cons));
    assert(editor.cursor.line == cursor.line);
    assert(editor.cursor.column == cursor.column);
}
