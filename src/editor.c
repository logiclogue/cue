#include <assert.h>
#include "editor.h"
#include "cursor.h"
#include "cons.h"
#include "cons_line.h"

Editor editor_new(Cursor cursor, Cons *cons) {
    return (Editor) {
        cursor = cursor,
        cons = cons
    };
}

Editor editor_insert_char(char c, Editor editor) {
    int pos = 42;
    Cons *new_cons = cons_insert_char(c, pos, editor.cons);
    Cursor new_cursor = cursor_right(editor.cursor);

    return editor_new(new_cursor, new_cons);
}

void editor_test() {
    Cursor cursor = cursor_new(1, 2);
    Cons *cons = cons_from_string("jordan\nteting");
    Editor editor = editor_new(cursor, cons);

    assert(editor.cons == cons);
    assert(editor.cursor.line == cursor.line);
    assert(editor.cursor.column == cursor.column);

    Editor new_editor = editor_insert_char('s', editor);

    assert(cons_equal(
        new_editor.cons,
        cons_from_string("jordan\ntesting")));
    assert(new_editor.cursor.column == editor.cursor.column + 1);
}
