#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

#define SAMPLE_COUNT 500000  // Total number of samples
#define PROCESS_COUNT 4      // Number of processes

// Function for child processes to generate samples and send the results back to the parent
void calculate_samples(int pipe_fd, int sample_count) {
    int counter;
    int local_hist[25] = {0};  // Local histogram for each child process

    srand(time(NULL) ^ getpid());  // Seed random number generator uniquely for each process

    // Generate samples
    for (int i = 0; i < sample_count; i++) {
        counter = 0;
        // Perform 12 trials and update the counter
        for (int j = 0; j < 12; j++) {
            int rand_num = rand() % 100;  // Generate a random number between 0 and 99
            if (rand_num >= 49)
                counter++;    // Increment if the random number is 49 or higher
            else
                counter--;    // Decrement otherwise
        }
        local_hist[counter + 12]++;  // Update local histogram with adjusted index
    }

    // Write the local histogram to the pipe for the parent process to read
    write(pipe_fd, local_hist, 25 * sizeof(int));
}

int main() {
    int hist[25] = {0};  // Combined histogram in the parent process
    int sample_count_per_process = SAMPLE_COUNT / PROCESS_COUNT;  // Samples per process
    pid_t pids[PROCESS_COUNT];
    int pipes[PROCESS_COUNT][2];  // Array of pipes, one for each process

    // Create pipes for communication between parent and child processes
    for (int i = 0; i < PROCESS_COUNT; i++) {
        if (pipe(pipes[i]) == -1) {  // Check for pipe creation failure
            perror("pipe");
            exit(1);
        }
    }

    // Fork child processes
    for (int i = 0; i < PROCESS_COUNT; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {  // Child process block
            close(pipes[i][0]);  // Close read end in child process
            calculate_samples(pipes[i][1], sample_count_per_process);  // Generate samples
            close(pipes[i][1]);  // Close write end after sending data
            exit(0);
        }
    }

    // Parent process block: collecting results from child processes
    for (int i = 0; i < PROCESS_COUNT; i++) {
        int local_hist[25] = {0};  // Temporary histogram to receive data from each child
        close(pipes[i][1]);  // Close write end in the parent process

        // Read the local histogram data from the child process through the pipe
        read(pipes[i][0], local_hist, 25 * sizeof(int));
        close(pipes[i][0]);  // Close read end after reading data

        // Aggregate the results from each child into the main histogram
        for (int j = 0; j < 25; j++) {
            hist[j] += local_hist[j];
        }
    }

    // Display the final combined histogram
    for (int i = 0; i < 25; i++) {
        printf("hist[%d] = %d\n", i - 12, hist[i]);  // Print histogram with adjusted index range (-12 to +12)
    }

    return 0;
}
