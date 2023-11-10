#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <stdlib.h>

char *command_list[] = {
    "help",
    "exit",
    "ls",
    "cd",
    // Add more commands here
    NULL
};

char *command_generator(const char *text, int state) {
    static int list_index, len;
    char *name;

    if (!state) {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = command_list[list_index++])) {
        if (strncmp(name, text, len) == 0) {
            return strdup(name);
        }
    }

    return NULL;
}

char **my_completion(const char *text, int start, int end) {
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, command_generator);
}

int main() {
    rl_attempted_completion_function = my_completion;

    char *input;
    while ((input = readline("Shell Hell> ")) != NULL) {
        if (input && *input) add_history(input);

        // Process input
        // ...

        free(input);
    }

    return 0;
}
