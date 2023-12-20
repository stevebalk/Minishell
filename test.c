#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void run_command(char **command) {
    execvp(command[0], command);
    perror("execvp");
    exit(EXIT_FAILURE);
}

void execute_pipeline(char ***commands, int num_commands) {
    pid_t child_pid;
    int input_fd = STDIN_FILENO;  // Initially, input comes from stdin

    for (int i = 0; i < num_commands; i++) {
        int pipefd[2];

        if (i < num_commands - 1) {
            if (pipe(pipefd) == -1) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        if ((child_pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) {  // Child process
            if (dup2(input_fd, STDIN_FILENO) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }

            if (i < num_commands - 1) {
                dup2(pipefd[1], STDOUT_FILENO);
                close(pipefd[1]);
            }

            run_command(commands[i]);
            exit(EXIT_SUCCESS);  // This line is reached only in case of execvp failure
        } else {  // Parent process
            if (i < num_commands - 1) {
				if (i > 0)
                	close(input_fd);
                input_fd = pipefd[0];
                // close(pipefd[0]);
                close(pipefd[1]);
            }
			else if (i >= num_commands - 1)
			{
				close(input_fd);
				// close(pipefd[0]);
				// close(pipefd[1]);
			}
        }
    }

    // Close the last command's pipe in the parent process
    // close(input_fd);

    // Wait for all child processes to finish
    for (int i = 0; i < num_commands; ++i) {
        if (wait(NULL) == -1) {
            perror("wait");
            exit(EXIT_FAILURE);
        }
    }
}

int main() {
    ((printf("HEllo "), printf("World\n")), printf(" Lol"));
}
