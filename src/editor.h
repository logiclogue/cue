#ifndef EDITOR_H
#define EDITOR_H

#include "cursor.h"
#include "cons.h"
#include "cursor.h"

typedef struct EditorTag Editor;

struct EditorTag {
    Cursor cursor;
    Cons *cons;
};

Editor editor_new(Cursor cursor, Cons *cons);
Editor editor_insert_char(char c, Editor editor);
void editor_test(void);

#endif