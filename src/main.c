#include <stdlib.h>
#include <stdio.h>
#include "cons.h"

int main(void) {
    cons_test();

    FILE *file = fopen("src/main.c", "r");
    char current_char;

    while (current_char != EOF) {
        current_char = fgetc(file);

        printf("%c", current_char);
    }

    printf("All tests pass :)\n");

    return 0;
}
