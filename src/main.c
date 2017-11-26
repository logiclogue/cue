#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>
#include "cons.h"
#include "cons_line.h"
#include "cursor.h"
#include "editor.h"
#include "curses_interface.h"

void test(void) {
    cons_test();
    cons_line_test();
    cursor_test();
    editor_test();

    printf("All tests pass :)\n");
}

void start(const char file_name[]) {
    FILE *file = fopen(file_name, "r");
    Cons *cons = cons_empty();

    if (file != NULL) {
        cons = cons_from_file(file);
    }

    Editor editor = editor_new(cursor_new(0, 0), cons);

    if (file != NULL) {
        fclose(file);
    }

    curses_interface_init();
    editor = curses_interface_start(editor);
    curses_interface_end();

    file = fopen(file_name, "w+");

    fflush(file);
    fputs(cons_to_string(editor.cons), file);

    fclose(file);
}

int main(int n, char **argv) {
    if (n == 1) {
        test();
    } else if (n == 2) {
        start(argv[1]);
    }

    return 0;
}
