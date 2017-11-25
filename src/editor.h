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
void editor_test(void);

#endif
