#ifndef CONS_LINE_H
#define CONS_LINE_H

#include <stdbool.h>
#include "cons.h"

Cons *cons_line(Cons *cons, int line);
bool cons_line_is_newline(char c);
void cons_line_test(void);

#endif
