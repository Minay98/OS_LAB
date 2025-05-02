#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *fun1();
void *fun2();

int shared = 1; // Shared variable between threads

int main()
{
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

    x = shared; // Read the value of the shared variable
    printf("Thread1 reads the value as %d\n", x);

    x++; // Increment the local copy
    printf("Local updation by Thread1: %d\n", x);

    sleep(1); // Simulate delay

    shared = x; // Write the updated value back to shared
    printf("Value of shared variable updated by Thread1 is: %d\n", shared);

    pthread_exit(NULL);
}

void *fun2()
{
    int y;

    y = shared; // Read the value of the shared variable
    printf("Thread2 reads the value as %d\n", y);

    y--; // Decrement the local copy
    printf("Local updation by Thread2: %d\n", y);

    sleep(1); // Simulate delay

    shared = y; // Write the updated value back to shared
    printf("Value of shared variable updated by Thread2 is: %d\n", shared);

    pthread_exit(NULL);
}
