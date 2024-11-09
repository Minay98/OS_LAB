#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
<<<<<<< HEAD
#include <string.h>

#define SAMPLE_COUNT 50000  // Total number of samples
#define PROCESS_COUNT 4     // Number of child processes

// Function to calculate samples in each child process
void calculate_samples(int pipe_fd, int sample_count) {
    int counter;
    int local_hist[25] = {0};  // Local histogram array for each process

    srand(time(NULL) ^ getpid());  // Set random seed using process ID

    // Generate samples
=======

#define SAMPLE_COUNT 500000  
#define PROCESS_COUNT 4 
void printHistogram(int* hist) {
    int i, j;
    for (i = 0; i < 25; i++) {
        printf("hist[%d]: ", i - 12);
        for (j = 0; j < hist[i]; j++) {
            printf("*");
        }
        printf("\n");
    }
}

void calculate_samples(int hist[], int sample_count) {
    int counter;

    srand(time(NULL) ^ (getpid()));  

>>>>>>> 8764bd890221d060a92b105a571390452eed8592
    for (int i = 0; i < sample_count; i++) {
        counter = 0;
        for (int j = 0; j < 12; j++) {
            int rand_num = rand() % 100;
            if (rand_num >= 49)
                counter++;
            else
                counter--;
        }
<<<<<<< HEAD
        local_hist[counter + 12]++;  // Update local histogram
    }

    // Print local histogram for debugging purposes
    printf("local_hist in child %d:\n", getpid());
    for (int i = 0; i < 25; i++) {
        printf("%d ", local_hist[i]);
    }
    printf("\n");

    // Send local_hist array to the parent process through the pipe
    write(pipe_fd, local_hist, 25 * sizeof(int));
}



int main() {
    int hist[25] = {0};  // Final histogram array in parent process
    int sample_count_per_process = SAMPLE_COUNT / PROCESS_COUNT;  // Samples per process
    pid_t pids[PROCESS_COUNT];
    int pipes[PROCESS_COUNT][2];

    // Create pipes for each child process
    for (int i = 0; i < PROCESS_COUNT; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    // Create child processes
    for (int i = 0; i < PROCESS_COUNT; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            // Child process code
            close(pipes[i][0]);  // Close read end in child process
            calculate_samples(pipes[i][1], sample_count_per_process);  // Perform calculation and send results to parent
            close(pipes[i][1]);  // Close write end after sending data
=======
        hist[counter + 12]++;
    }
}

int main() {
    int hist[25] = {0};
    int sample_count_per_process = SAMPLE_COUNT / PROCESS_COUNT;
    pid_t pids[PROCESS_COUNT];

    for (int i = 0; i < PROCESS_COUNT; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            calculate_samples(hist, sample_count_per_process);
>>>>>>> 8764bd890221d060a92b105a571390452eed8592
            exit(0);
        }
    }

<<<<<<< HEAD
    // Collect results from each child process in the parent process
    for (int i = 0; i < PROCESS_COUNT; i++) {
        int local_hist[25] = {0};
        close(pipes[i][1]);  // Close write end in parent process

        // Read data from child process through pipe
        read(pipes[i][0], local_hist, 25 * sizeof(int));
        close(pipes[i][0]);  // Close read end after reading

        // Merge local histogram with the main histogram
        for (int j = 0; j < 25; j++) {
            hist[j] += local_hist[j];
        }
    }

    // Display the final histogram
    printf("Final hist:\n");
    for (int i = 0; i < 25; i++) {
        printf("hist[%d] = %d\n", i - 12, hist[i]);
    }
    
    return 0;
}

// To plot the histogram using gnuplot, use the following command:
// gnuplot -p -e "set style data histograms; plot 'histogram_data.txt' using 2:xtic(1) with boxes"
=======
    for (int i = 0; i < PROCESS_COUNT; i++) {
        waitpid(pids[i], NULL, 0);
    }

    for (int i = 0; i < 25; i++) {
        printf("hist[%d] = %d\n", i - 12, hist[i]);
    }
    printHistogram(hist);

    return 0;
}
>>>>>>> 8764bd890221d060a92b105a571390452eed8592
