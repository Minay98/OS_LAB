
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

int turn = 0; // 0 = A, 1 = B, 2 = C

typedef struct {
    char letter;
    int id;        // 0, 1, 2 for A, B, C
    int repeats;   // how many times each thread should print
} thread_arg_t;

void *printer(void *arg) {
    thread_arg_t *t = (thread_arg_t*)arg;

    for (int i = 0; i < t->repeats; i++) {
        pthread_mutex_lock(&mtx);

        // TODO: Wait until it's this thread's turn
        // while (???) {
        //     pthread_cond_wait(&cond, &mtx);
        // }

        // TODO: Print the letter
        // putchar(...);

        // TODO: Update turn to the next thread
        // turn = ???

        // TODO: Wake up the other threads
        // pthread_cond_???

        pthread_mutex_unlock(&mtx);
    }

    return NULL;
}

int main() {
    int repeats = 10; // each letter will be printed 'repeats' times
    pthread_t th[3];
    thread_arg_t args[3] = {
        {'A', 0, repeats},
        {'B', 1, repeats},
        {'C', 2, repeats}
    };

    // TODO: Create 3 threads using pthread_create
    // pthread_create(&th[...], NULL, printer, &args[...]);

    // TODO: Wait for all threads to finish using pthread_join
    // pthread_join(...);

    printf("\nDone!\n");
    return 0;
}
