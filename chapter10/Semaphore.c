#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>

// Function prototypes
void *fun1();
void *fun2();

int shared = 1; // Shared variable
sem_t s;        // Semaphore variable

int main()
{
    // Initialize the semaphore with value 1, allowing only one thread at a time
    sem_init(&s, 0, 1);

    pthread_t thread1, thread2;

    // Create two threads
    pthread_create(&thread1, NULL, fun1, NULL);
    pthread_create(&thread2, NULL, fun2, NULL);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Print the final value of the shared variable
    printf("Final value of shared is %d\n", shared);

    return 0;
}

void *fun1()
{
    int x;

    sem_wait(&s); // Enter critical section

    x = shared; // Read the shared variable
    printf("Thread1 reads the value as %d\n", x);

    x++; // Increment the local copy
    printf("Local updation by Thread1: %d\n", x);

    sleep(1); // Simulate some processing delay

    shared = x; // Update the shared variable
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);

    sem_post(&s); // Leave critical section

    pthread_exit(NULL);
}

void *fun2()
{
    int y;

    sem_wait(&s); // Enter critical section

    y = shared; // Read the shared variable
    printf("Thread2 reads the value as %d\n", y);

    y--; // Decrement the local copy
    printf("Local updation by Thread2: %d\n", y);

    sleep(1); // Simulate some processing delay

    shared = y; // Update the shared variable
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);

    sem_post(&s); // Leave critical section

    pthread_exit(NULL);
}
