#ifndef CONS_LINE_H
#define CONS_LINE_H

#include <stdbool.h>
#include "cons.h"

Cons *cons_line(Cons *cons, int line);
bool cons_line_is_newline(char c);
int cons_line_count(Cons *cons);
int cons_line_current(int pos, Cons *cons);
int cons_line_column_to_pos(int line, int column, Cons *cons);
void cons_line_test(void);

#endif
