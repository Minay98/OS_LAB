#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLE_COUNT 500000  

int main() {
    int hist[25] = {0};
    int counter;

    srand(time(NULL));  
    for (int i = 0; i < SAMPLE_COUNT; i++) {
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

    for (int i = 0; i < 25; i++) {
        printf("hist[%d] = %d\n", i - 12, hist[i]);
    }

    return 0;
}
