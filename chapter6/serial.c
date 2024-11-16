#include <stdio.h>
#include <time.h> 

void prefix_sum_serial(int a[], int b[], int n) {
    b[0] = a[0];
    for (int i = 1; i < n; i++) {
        b[i] = b[i - 1] + a[i];
    }
}

int main() {
    int n = 500000; 
    int a[n], b[n];

    for (int i = 0; i < n; i++) {
        a[i] = 1; 
    }

    clock_t start, end;

    start = clock();
    prefix_sum_serial(a, b, n);
    end = clock();

    printf("Execution Time: %lf s\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    return 0;
}
