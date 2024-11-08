#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>

#define SAMPLE_COUNT 500000  
#define PROCESS_COUNT 4      
void calculate_samples(int hist[], int sample_count) {
    int counter;

    srand(time(NULL) ^ (getpid()));  

    for (int i = 0; i < sample_count; i++) {
        counter = 0;
        for (int j = 0; j < 12; j++) {
            int rand_num = rand() % 100;
            if (rand_num >= 49)
                counter++;
            else
                counter--;
        }
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
            exit(0);
        }
    }

    for (int i = 0; i < PROCESS_COUNT; i++) {
        waitpid(pids[i], NULL, 0);
    }

    for (int i = 0; i < 25; i++) {
        printf("hist[%d] = %d\n", i - 12, hist[i]);
    }

    return 0;
}
