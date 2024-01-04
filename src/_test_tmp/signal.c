#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

volatile sig_atomic_t exit_flag = 0;

void signal_handler(int signal) {
    printf("\nCaught signal %d\n", signal);
    exit_flag = 1;  // Set the flag to exit the main loop
}

int main() {
    struct sigaction sa;
    sigset_t blocked_signals;

    // Setup the signal set to block SIGTERM
    sigemptyset(&blocked_signals);
    sigaddset(&blocked_signals, SIGTERM);

    // Setup the sigaction struct
    sa.sa_handler = signal_handler;
    sa.sa_mask = blocked_signals;
    sa.sa_flags = 0;

    // Set the signal handler for SIGINT
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return 1;
    }

    // Main program loop
    while (!exit_flag) {
        printf("Running... Press Ctrl+C to trigger SIGINT and exit\n");
        sleep(1);
    }

    printf("Exiting program\n");
    return 0;
}
