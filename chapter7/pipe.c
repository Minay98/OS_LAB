#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int fd[2]; // File descriptors for the pipe
    pid_t pid;

    // Create a pipe
    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    // Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid > 0) { // Parent process
        close(fd[0]); // Close the read end in the parent
        write(fd[1], "Hello, world!\n", 14); // Write to the write end
        close(fd[1]); // Close the write end
        wait(NULL); // Wait for the child to finish
    } else { // Child process
        close(fd[1]); // Close the write end in the child
        char buffer[100];
        int nbytes = read(fd[0], buffer, 100);
        if (nbytes > 0) {
            write(1, buffer, nbytes); // Write to standard output
        } else {
            perror("read");
        }
        close(fd[0]); // Close the read end
    }

    return 0;
}