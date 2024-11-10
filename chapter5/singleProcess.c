#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SAMPLE_COUNT 500000  // Number of samples to generate
// Function to save the final histogram to a file
void saveHistogramToFile(int* hist, int size) {
    FILE *file = fopen("histogram_data.txt", "w");
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d %d\n", i - 12, hist[i]);  // Save interval and frequency
    }
    fclose(file);
}
int main() {
    int hist[25] = {0};  // Array to store the histogram data
    int counter;

    srand(time(NULL));  // Initialize random seed with current time
    for (int i = 0; i < SAMPLE_COUNT; i++) {
        counter = 0;
        
        // Perform 12 random trials to adjust the counter value
        for (int j = 0; j < 12; j++) {
            int rand_num = rand() % 100;  // Generate a random number between 0 and 99
            if (rand_num >= 49)
                counter++;   // Increment counter if random number is 49 or above
            else
                counter--;   // Decrement counter if random number is below 49
        }

        // Update the histogram based on the resulting counter value
        hist[counter + 12]++;  // Shift index by 12 to avoid negative indices
    }

    // Print the histogram results
    for (int i = 0; i < 25; i++) {
        printf("hist[%d] = %d\n", i - 12, hist[i]);  // Display histogram with adjusted indices
    }
    // Save the final histogram to a file for plotting with gnuplot
    saveHistogramToFile(hist, 25);
    return 0;
}
