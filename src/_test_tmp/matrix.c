/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

#define WIDTH 120    // Width of the terminal
#define HEIGHT 48   // Height of the terminal
#define SPEED 200000 // Speed of the effect
#define STAY_PROB 8  // Probability that a character will stay

char screen[HEIGHT][WIDTH + 1]; // Screen buffer

// Function to set terminal to raw mode
void set_raw_mode() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO); // Disable buffering and echo
    tcsetattr(0, TCSANOW, &term);
}

// Function to reset terminal to original settings
void reset_terminal_mode() {
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(0, TCSANOW, &term);
}

// Function to initialize the screen buffer
void init_screen() {
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            screen[i][j] = ' ';
        }
        screen[i][WIDTH] = '\0'; // Null-terminate each row for easy printing
    }
}

// Function to update the screen buffer
void update_screen() {
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if ((rand() % 15) == 0) {
                screen[i][j] = 'a' + rand() % 26; // Set a new character
            } else if ((rand() % STAY_PROB) != 0) {
                screen[i][j] = ' '; // Clear the character with a probability
            }
        }
    }
}

int main() {
    set_raw_mode();
    srand(time(NULL)); // Seed for random number generation
    init_screen();

    while (1) {
        update_screen();

        // Clear the screen
        system("clear");

        // Set text color to green
        printf("\033[0;32m");

        // Print the screen buffer
        int i;
        for (i = 0; i < HEIGHT; i++) {
            printf("%s\n", screen[i]);
        }

        // Reset text color
        printf("\033[0m");

        usleep(SPEED); // Control the speed of the effect
    }

    reset_terminal_mode();
    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WIDTH 80    // Width of the terminal
#define HEIGHT 24   // Height of the terminal
#define SPEED 100000 // Speed of the effect
#define STAY_PROB 5  // Probability that a character will stay

char screen[HEIGHT][WIDTH]; // Screen buffer

// Function to initialize the screen buffer
void init_screen() {
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            screen[i][j] = ' ';
        }
    }
}

// Function to update the screen buffer
void update_screen() {
    int i, j;
    for (i = 0; i < HEIGHT; i++) {
        for (j = 0; j < WIDTH; j++) {
            if ((rand() % 15) == 0) {
                screen[i][j] = 'a' + rand() % 26; // Set a new character
            } else if ((rand() % STAY_PROB) != 0) {
                screen[i][j] = ' '; // Clear the character with a probability
            }
        }
    }
}

int main() {
    srand(time(NULL)); // Seed for random number generation
    init_screen();

    while (1) {
        update_screen();

        // Clear the screen
        system("clear");

        // Set text color to green
        printf("\033[0;32m");

        // Print the screen buffer character by character
        int i, j;
        for (i = 0; i < HEIGHT; i++) {
            for (j = 0; j < WIDTH; j++) {
                putchar(screen[i][j]);
            }
            putchar('\n');
        }

        // Reset text color
        printf("\033[0m");

        usleep(SPEED); // Control the speed of the effect
    }

    return 0;
}