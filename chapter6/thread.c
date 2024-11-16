#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define N 10 // Size of the array

// Structure to hold data for each thread
typedef struct {
    int *a;
    int *b;
    int start;
    int end;
} ThreadData;

// Function to calculate prefix sum in parallel
void *prefix_sum_partial(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->b[data->start] = data->a[data->start];
    for (int i = data->start + 1; i <= data->end; i++) {
        data->b[i] = data->b[i - 1] + data->a[i];
    }
    return NULL;
}

// Function to merge the results of two chunks
void merge_chunks(int b[], int mid, int end) {
    int adjust_value = b[mid];
    for (int i = mid + 1; i <= end; i++) {
        b[i] += adjust_value;
    }
}

int main() {
    int a[] = {1, 2, 1, 5, 0, 7, 3, 4, 2, 7}; // Initial array
    int n = sizeof(a) / sizeof(a[0]); // Size of the array
    int b[n]; // Result array

    pthread_t thread1, thread2;
    ThreadData data1, data2;

    // Divide the array into two halves
    int mid = n / 2 - 1;
    data1 = (ThreadData){a, b, 0, mid};
    data2 = (ThreadData){a, b, mid + 1, n - 1};

    clock_t start, end;
    
    // Start measuring time
    start = clock();

    // Create two threads for parallel execution
    pthread_create(&thread1, NULL, prefix_sum_partial, &data1);
    pthread_create(&thread2, NULL, prefix_sum_partial, &data2);

    // Wait for both threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Merge the chunks
    merge_chunks(b, mid, n - 1);

    // End measuring time
    end = clock();

    // Calculate and display execution time
    double execution_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Parallel execution time: %lf seconds\n", execution_time);

    // Display arrays a and b
    printf("Array a: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    printf("Array b: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");

    return 0;
}
