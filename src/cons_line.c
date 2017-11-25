#include <assert.h>
#include "cons_line.h"

Cons *cons_line(Cons *cons, int line) {
    if (cons_is_empty(cons)) {
        return cons_empty();
    } else if (cons_line_is_newline(cons->car) && line == 0) {
        return cons_new(cons->car, cons_empty());
    } else if (cons_line_is_newline(cons->car)) {
        return cons_line(cons->cdr, line - 1);
    } else if (line == 0) {
        return cons_new(cons->car, cons_line(cons->cdr, line));
    }

    return cons_line(cons->cdr, line);
}

static int _cons_line_count(int n, Cons *cons) {
    if (cons_is_empty(cons)) {
        return n + 1;
    } else if (cons_line_is_newline(cons->car)) {
        return _cons_line_count(n + 1, cons->cdr);
    }

    return _cons_line_count(n, cons->cdr);
}

int cons_line_count(Cons *cons) {
    return _cons_line_count(0, cons);
}

bool cons_line_is_newline(char c) {
    return c == 0x0A || c == 0x0B || c == 0x0C || c == 0x0D || c == 0x85;
}

static int _cons_line_current(int line, int pos, Cons *cons) {
    if (cons_is_empty(cons)) {
        return line;
    } else if (pos <= 0) {
        return line;
    } else if (cons_line_is_newline(cons->car)) {
        return _cons_line_current(line + 1, pos - 1, cons->cdr);
    }

    return _cons_line_current(line, pos - 1, cons->cdr);
}

int cons_line_current(int pos, Cons *cons) {
    return _cons_line_current(0, pos, cons);
}

int cons_line_column_to_pos(int line, int column, Cons *cons) {
    Cons *current_line = cons_line(cons, line);
    int length = cons_length(current_line);
    int lines = cons_line_count(cons);
    
    if (line >= lines && line > 0) {
        return cons_line_column_to_pos(line - 1, column, cons);
    } else if (column >= length && column > 0) {
        return cons_line_column_to_pos(line, column - 1, cons);
    } else if (column < 0) {
        return cons_line_column_to_pos(line, length - 1, cons);
    } else if (line == 0) {
        return column;
    } else if (column == 0) {
        return 1 + cons_line_column_to_pos(line - 1, column - 1, cons);
    }

    return 1 + cons_line_column_to_pos(line, column - 1, cons);
}

void cons_line_test(void) {
    Cons *cons = cons_from_string("first\nsecond\nthird");
    Cons *first = cons_line(cons, 0);
    Cons *expected_first = cons_from_string("first\n");
    Cons *second = cons_line(cons, 1);
    Cons *expected_second = cons_from_string("second\n");
    Cons *third = cons_line(cons, 2);
    Cons *expected_third = cons_from_string("third");
    Cons *fourth = cons_line(cons, 3);

    assert(cons_equal(first, expected_first));
    assert(cons_equal(second, expected_second));
    assert(cons_equal(third, expected_third));
    assert(cons_equal(fourth, cons_empty()));
    assert(cons_line_count(cons) == 3);
    assert(cons_line_count(cons_from_string("")) == 1);
    assert(cons_line_current(0, cons) == 0);
    assert(cons_line_current(1, cons) == 0);
    assert(cons_line_current(6, cons) == 1);
    assert(cons_line_current(100, cons) == 2);
    assert(cons_line_current(5, cons) == 0);
    assert(cons_line_column_to_pos(0, 0, cons) == 0);
    assert(cons_line_column_to_pos(0, 1, cons) == 1);
    assert(cons_line_column_to_pos(1, 0, cons) == 6);
    assert(cons_line_column_to_pos(2, 4, cons) == 17);
    assert(cons_line_column_to_pos(2, 5, cons) == 17);
    assert(cons_line_column_to_pos(3, 5, cons) == 17);

    cons_destroy(cons);
    cons_destroy(first);
    cons_destroy(expected_first);
    cons_destroy(second);
    cons_destroy(expected_second);
    cons_destroy(third);
    cons_destroy(expected_third);
}
