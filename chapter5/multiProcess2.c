#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>

#define SAMPLE_COUNT 500000  
#define PROCESS_COUNT 4      

void calculate_samples(int pipe_fd, int sample_count) {
    int counter;
    int local_hist[25] = {0};

    srand(time(NULL) ^ getpid());  

    for (int i = 0; i < sample_count; i++) {
        counter = 0;
        for (int j = 0; j < 12; j++) {
            int rand_num = rand() % 100;
            if (rand_num >= 49)
                counter++;
            else
                counter--;
        }
        local_hist[counter + 12]++;  
    }

    write(pipe_fd, local_hist, 25 * sizeof(int));
}

int main() {
    int hist[25] = {0};
    int sample_count_per_process = SAMPLE_COUNT / PROCESS_COUNT;
    pid_t pids[PROCESS_COUNT];
    int pipes[PROCESS_COUNT][2];

    for (int i = 0; i < PROCESS_COUNT; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    for (int i = 0; i < PROCESS_COUNT; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            close(pipes[i][0]);  
            calculate_samples(pipes[i][1], sample_count_per_process);  
            close(pipes[i][1]);  
            exit(0);
        }
    }

    for (int i = 0; i < PROCESS_COUNT; i++) {
        int local_hist[25] = {0};
        close(pipes[i][1]);  
        read(pipes[i][0], local_hist, 25 * sizeof(int));
        close(pipes[i][0]);  

        for (int j = 0; j < 25; j++) {
            hist[j] += local_hist[j];
        }
    }

    for (int i = 0; i < 25; i++) {
        printf("hist[%d] = %d\n", i - 12, hist[i]);
    }

    return 0;
}
