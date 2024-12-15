#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

// Shared variable and semaphore
int shared = 1; // Shared variable
sem_t s; // Semaphore variable

// Thread function declarations
void *fun1();
void *fun2();

int main() {
    // Initialize semaphore (initial value = 1)
    sem_init(&s, 0, 1);

    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final value of the shared variable
    printf("Final value of shared is %d\n", shared);

    return 0;
}

void *fun1() {
    int x;

    // Enter critical section
    sem_wait(&s);

    // Read and increment the value
    x = shared;
    printf("Thread1 reads the value as %d\n", x);
    x++;
    printf("Local updation by Thread1: %d\n", x);

    sleep(1); // Simulate some delay

    shared = x;
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);

    // Exit critical section
    sem_post(&s);

    return NULL;
}

void *fun2() {
    int y;

    // Enter critical section
    sem_wait(&s);

    // Read and decrement the value
    y = shared;
    printf("Thread2 reads the value as %d\n", y);
    y--;
    printf("Local updation by Thread2: %d\n", y);

    sleep(1); // Simulate some delay

    shared = y;
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);

    // Exit critical section
    sem_post(&s);

    return NULL;
}
