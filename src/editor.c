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
    int pos = editor_get_position(editor);
    Cons *new_cons = cons_insert_char(pos, c, editor.cons);
    Cursor new_cursor = cursor_right(editor.cursor);

    return editor_new(new_cursor, new_cons);
}

Editor editor_backspace(Editor editor) {
    int position = editor_get_position(editor);
    Cons *cons = cons_remove_item(position - 1, editor.cons);

    return editor_new(cursor_left(editor.cursor), cons);
}

Editor editor_delete(Editor editor) {
    int position = editor_get_position(editor);
    Cons *cons = cons_remove_item(position, editor.cons);

    return editor_new(editor.cursor, cons);
}

int editor_get_position(Editor editor) {
    return cons_line_column_to_pos(
        editor.cursor.line,
        editor.cursor.column,
        editor.cons);
}

static Editor move_to_position(int position, Cursor cursor, Cons *cons) {
    if (position <= 0 || cons_is_empty(cons)) {
        return editor_new(cursor, cons);
    } else if (cons_line_is_newline(cons->car)) {
        return move_to_position(
            position - 1,
            cursor_new(cursor.line + 1, 0),
            cons->cdr);
    }

    return move_to_position(position - 1, cursor_right(cursor), cons->cdr);
}

Editor editor_move_to_position(int position, Editor editor) {
    Cursor cursor = move_to_position(
        position,
        cursor_new(0, 0),
        editor.cons).cursor;

    return editor_new(cursor, editor.cons);
}

Editor editor_cursor_normalise(Editor editor) {
    if (editor.cursor.column < 0) {
        editor = editor_new(cursor_new(editor.cursor.line, 0), editor.cons);
    }

    int position = editor_get_position(editor);

    return editor_move_to_position(position, editor);
}

Editor editor_newline(Editor editor) {
    int position = editor_get_position(editor);
    Cursor cursor = cursor_new(editor.cursor.line + 1, 0);
    Cons *cons = cons_insert_char(position, '\n', editor.cons);

    return editor_new(cursor, cons);
}

void editor_test() {
    Cursor cursor = cursor_new(1, 2);
    Cons *cons = cons_from_string("jordan\nteting");
    Editor editor = editor_new(cursor, cons);

    assert(editor.cons == cons);
    assert(editor.cursor.line == cursor.line);
    assert(editor.cursor.column == cursor.column);

    Editor new_editor = editor_insert_char('s', editor);

    assert(editor_get_position(editor) == 9);
    assert(cons_equal(
        new_editor.cons,
        cons_from_string("jordan\ntesting")));
    assert(new_editor.cursor.column == editor.cursor.column + 1);

    new_editor = editor_backspace(editor);

    assert(new_editor.cursor.column == editor.cursor.column - 1);
    assert(cons_equal(
        new_editor.cons,
        cons_from_string("jordan\ntting")));

    new_editor = editor_delete(editor);

    assert(new_editor.cursor.column == editor.cursor.column);
    assert(cons_equal(
        new_editor.cons,
        cons_from_string("jordan\nteing")));

    new_editor = editor_move_to_position(0, editor);

    assert(new_editor.cursor.line == 0);
    assert(new_editor.cursor.column == 0);

    new_editor = editor_move_to_position(1, editor);

    assert(new_editor.cursor.line == 0);
    assert(new_editor.cursor.column == 1);

    new_editor = editor_move_to_position(6, editor);

    assert(new_editor.cursor.line == 0);
    assert(new_editor.cursor.column == 6);

    new_editor = editor_move_to_position(7, editor);

    assert(new_editor.cursor.line == 1);
    assert(new_editor.cursor.column == 0);
    assert(editor.cons == new_editor.cons);

    editor = editor_new(cursor_new(0, 100), editor.cons);
    new_editor = editor_cursor_normalise(editor);

    assert(new_editor.cursor.line == 0);
    assert(new_editor.cursor.column == 6);

    editor = editor_new(cursor_new(4, 100), editor.cons);
    new_editor = editor_cursor_normalise(editor);

    assert(new_editor.cursor.line == 1);
    assert(new_editor.cursor.column == 5);

    editor = editor_new(cursor_new(-1, -1), editor.cons);
    new_editor = editor_cursor_normalise(editor);

    assert(new_editor.cursor.line == 0);
    assert(new_editor.cursor.column == 0);

    editor = editor_new(cursor_new(1, 2), editor.cons);
    new_editor = editor_newline(editor);

    assert(new_editor.cursor.line == 2);
    assert(new_editor.cursor.column == 0);
    assert(cons_equal(
        new_editor.cons,
        cons_from_string("jordan\nte\nting")));
}
