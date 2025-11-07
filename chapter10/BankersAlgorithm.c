#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define NUMBER_OF_RESOURCES 5
#define NUMBER_OF_CUSTOMERS 5

int available[NUMBER_OF_RESOURCES];
int maximum[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int allocation[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];
int need[NUMBER_OF_CUSTOMERS][NUMBER_OF_RESOURCES];

pthread_mutex_t lock;

// Initialize the data structures
void initialize() {
    srand(time(NULL));
    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
            allocation[i][j] = 0;
            maximum[i][j] = rand() % (available[j] + 1);
            need[i][j] = maximum[i][j];
        }
    }
}

// Safety algorithm
bool is_safe() {
    int work[NUMBER_OF_RESOURCES];
    bool finish[NUMBER_OF_CUSTOMERS] = { false };

    memcpy(work, available, sizeof(available));

    for (int count = 0; count < NUMBER_OF_CUSTOMERS; count++) {
        for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
            if (!finish[i]) {
                bool can_allocate = true;
                for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < NUMBER_OF_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                }
            }
        }
    }

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        if (!finish[i]) return false;
    }
    return true;
}

int request_resources(int customer_num, int request[]) {
    pthread_mutex_lock(&lock);

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (request[i] > need[customer_num][i]) {
            pthread_mutex_unlock(&lock);
            return -1; // Request exceeds need
        }
        if (request[i] > available[i]) {
            pthread_mutex_unlock(&lock);
            return -1; // Not enough resources available
        }
    }

    // Pretend to allocate
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[customer_num][i] += request[i];
        need[customer_num][i] -= request[i];
    }

    if (is_safe()) {
        pthread_mutex_unlock(&lock);
        return 0;
    } else {
        // Rollback
        for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
            available[i] += request[i];
            allocation[customer_num][i] -= request[i];
            need[customer_num][i] += request[i];
        }
        pthread_mutex_unlock(&lock);
        return -1;
    }
}

int release_resources(int customer_num, int release[]) {
    pthread_mutex_lock(&lock);
    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        if (release[i] > allocation[customer_num][i])
            release[i] = allocation[customer_num][i];
        available[i] += release[i];
        allocation[customer_num][i] -= release[i];
        need[customer_num][i] += release[i];
    }
    pthread_mutex_unlock(&lock);
    return 0;
}

void* customer_thread(void* arg) {
    int id = *(int*)arg;
    int request[NUMBER_OF_RESOURCES];

    while (1) {
        for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
            request[i] = rand() % (need[id][i] + 1);
        }
        if (request_resources(id, request) == 0) {
            printf("Customer %d request granted\n", id);
            sleep(1);
            release_resources(id, request);
            printf("Customer %d released resources\n", id);
        }
        sleep(rand() % 3 + 1);
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != NUMBER_OF_RESOURCES + 1) {
        printf("Usage: %s <r1> <r2> <r3> <r4> <r5>\n", argv[0]);
        return EXIT_FAILURE;
    }

    for (int i = 0; i < NUMBER_OF_RESOURCES; i++) {
        available[i] = strtol(argv[i + 1], NULL, 10);
    }

    initialize();
    pthread_mutex_init(&lock, NULL);

    pthread_t threads[NUMBER_OF_CUSTOMERS];
    int ids[NUMBER_OF_CUSTOMERS];

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, customer_thread, &ids[i]);
    }

    for (int i = 0; i < NUMBER_OF_CUSTOMERS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock);
    return 0;
}
