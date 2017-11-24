#include <assert.h>
#include "cons_line.h"

Cons *cons_line(Cons *cons, int line) {
    if (cons_is_empty(cons)) {
        return cons_empty();
    } else if (cons_line_is_newline(cons->car) && line == 0) {
        return cons_empty();
    } else if (cons_line_is_newline(cons->car)) {
        return cons_line(cons->cdr, line - 1);
    } else if (line == 0) {
        return cons_new(cons->car, cons_line(cons->cdr, line));
    }

    return cons_line(cons->cdr, line);
}

bool cons_line_is_newline(char c) {
    return c == 0x0A || c == 0x0B || c == 0x0C || c == 0x0D || c == 0x85;
}

void cons_line_test(void) {
    Cons *cons = cons_from_string("first\nsecond\nthird");
    Cons *first = cons_line(cons, 0);
    Cons *expected_first = cons_from_string("first");
    Cons *second = cons_line(cons, 1);
    Cons *expected_second = cons_from_string("second");
    Cons *third = cons_line(cons, 2);
    Cons *expected_third = cons_from_string("third");
    Cons *fourth = cons_line(cons, 3);

    assert(cons_equal(first, expected_first));
    assert(cons_equal(second, expected_second));
    assert(cons_equal(third, expected_third));
    assert(cons_equal(fourth, cons_empty()));

    cons_destroy(cons);
    cons_destroy(first);
    cons_destroy(expected_first);
    cons_destroy(second);
    cons_destroy(expected_second);
    cons_destroy(third);
    cons_destroy(expected_third);
}