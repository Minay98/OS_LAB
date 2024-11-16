#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

typedef struct {
    int *a;
    int *b;
    int start;
    int end;
} ThreadData;

void *prefix_sum_partial(void *arg) {
    ThreadData *data = (ThreadData *)arg;
    data->b[data->start] = data->a[data->start];
    for (int i = data->start + 1; i <= data->end; i++) {
        data->b[i] = data->b[i - 1] + data->a[i];
    }
    return NULL;
}

void merge_chunks(int b[], int mid, int end) {
    int adjust_value = b[mid];
    for (int i = mid + 1; i <= end; i++) {
        b[i] += adjust_value;
    }
}

int main() {
    int n = 500000; 
    int a[n], b[n];
    for (int i = 0; i < n; i++) {
        a[i] = 1; 
    }

    pthread_t thread1, thread2;
    ThreadData data1, data2;

    int mid = n / 2 - 1;

    data1 = (ThreadData){a, b, 0, mid};
    data2 = (ThreadData){a, b, mid + 1, n - 1};

    clock_t start, end;

    start = clock();
    pthread_create(&thread1, NULL, prefix_sum_partial, &data1);
    pthread_create(&thread2, NULL, prefix_sum_partial, &data2);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // ادغام تکه‌ها
    merge_chunks(b, mid, n - 1);
    end = clock();

    printf("executin time: %lf s\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}
