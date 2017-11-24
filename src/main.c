#include <stdlib.h>
#include <stdio.h>
#include "cons.h"

int main(void) {
    cons_test();

    FILE *file = fopen("src/main.c", "r");
    Cons *cons = cons_from_file(file);

    printf("%s\n", cons_to_string(cons));

    printf("All tests pass :)\n");

    return 0;
}
