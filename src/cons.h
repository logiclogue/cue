#ifndef CONS_H
#define CONS_H

#include <stdbool.h>
#include <stdio.h>

typedef struct _Cons Cons;

struct _Cons {
    char car;
    Cons *cdr;
};

Cons *cons_new(char value, Cons *cons);
Cons *cons_empty(void);
Cons *cons_from_string(char *s);
Cons *cons_from_int(int i);
Cons *cons_from_bool(bool b);
Cons *cons_from_file(FILE *f);
void cons_destroy(Cons *cons);
char *cons_to_string(Cons *cons);
int cons_to_int(Cons *cons);
bool cons_to_bool(Cons *cons);
char cons_head(Cons *cons);
Cons *cons_tail(Cons *cons);
char cons_item(int i, Cons *cons);
char cons_last(Cons *cons);
Cons *cons_init(Cons *cons);
Cons *cons_take(int n, Cons *cons);
Cons *cons_drop(int n, Cons *cons);
int cons_length(Cons *cons);
bool cons_equal(Cons *cons_a, Cons *cons_b);
Cons *cons_add(Cons *cons_a, Cons *cons_b);
Cons *cons_trim(Cons *cons);
bool cons_is_white_space(char c);
void cons_test(void);
Cons *cons_list(int n, Cons *cons);
bool cons_is_empty(Cons *cons);
bool cons_all(bool (*f)(char c), Cons *cons);
Cons *cons_insert_char(int i, char c, Cons *cons);

#endif
