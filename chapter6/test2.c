
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    uint64_t samples;   // number of random points this thread will generate
    unsigned int seed;  // random seed (different for each thread)
    uint64_t inside;    // number of points inside the circle
} thread_arg_t;

void *worker(void *arg) {
    thread_arg_t *w = (thread_arg_t*)arg;
    uint64_t inside_local = 0;
    unsigned int seed = w->seed;

    for (uint64_t i = 0; i < w->samples; i++) {
        // TODO: Generate x and y in range [0, 1)
        // double x = ...
        // double y = ...

        // TODO: Check if the point is inside the quarter circle
        // if (???) inside_local++;
    }

    // TODO: Save local result into struct
    // w->inside = ???

    return NULL;
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s <total_samples> <num_threads>\n", argv[0]);
        return 1;
    }

    uint64_t total_samples = strtoull(argv[1], NULL, 10);
    int num_threads = atoi(argv[2]);

    pthread_t th[num_threads];
    thread_arg_t args[num_threads];

    uint64_t base = total_samples / num_threads;
    uint64_t rem  = total_samples % num_threads;

    unsigned int base_seed = time(NULL);

    for (int i = 0; i < num_threads; i++) {
        args[i].samples = base + (i < rem ? 1 : 0);
        args[i].seed = base_seed ^ (i * 1234567);
        args[i].inside = 0;

        // TODO: Create a thread for each worker
        // pthread_create(&th[i], NULL, worker, ???);
    }

    uint64_t total_inside = 0;

    for (int i = 0; i < num_threads; i++) {
        // TODO: Wait for each thread to finish
        // pthread_join(th[i], ???);

        // TODO: Accumulate the inside counts
        // total_inside += ???;
    }

    double pi_est = 4.0 * (double)total_inside / (double)total_samples;
    printf("PI ≈ %.10f\n", pi_est);

    return 0;
}
