#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int main() {
    char *input;

    // Read input using readline
    input = readline("Enter something: ");

    // Check if input is not NULL
    if (input) {
        printf("You entered: %s\n", input);
        free(input); // Free the memory allocated by readline
    }

    return 0;
}

// gcc -o readline_example rl_test.c -lreadline
