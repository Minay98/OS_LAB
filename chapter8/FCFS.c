#include <stdio.h>

struct Process {
    int id;            // Process ID
    int service_time;  // Burst time
    int wait_time;     // Waiting time
    int execution_time; // Execution time
};

int main() {
    int n, i;

    // Get the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    float avg_wait_time = 0, avg_execution_time = 0;

    // Input the service time for each process
    printf("Enter the service time for each process:\n");
    for (i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Process %d service time: ", i + 1);
        scanf("%d", &processes[i].service_time);
    }

    // Calculate wait times and execution times
    processes[0].wait_time = 0; // First process has zero wait time
    for (i = 1; i < n; i++) {
        processes[i].wait_time = processes[i - 1].wait_time + processes[i - 1].service_time;
    }

    for (i = 0; i < n; i++) {
        processes[i].execution_time = processes[i].wait_time + processes[i].service_time;
    }

    // Calculate average wait time and average execution time
    for (i = 0; i < n; i++) {
        avg_wait_time += processes[i].wait_time;
        avg_execution_time += processes[i].execution_time;
    }
    avg_wait_time /= n;
    avg_execution_time /= n;

    // Display the results
    printf("\nFCFS Scheduling Results:\n");
    printf("Process | Service Time | Wait Time | Execution Time\n");
    for (i = 0; i < n; i++) {
        printf("   %d    |      %d       |     %d     |       %d\n",
               processes[i].id, processes[i].service_time, processes[i].wait_time, processes[i].execution_time);
    }

    printf("\nAverage Wait Time: %.2f\n", avg_wait_time);
    printf("Average Execution Time: %.2f\n", avg_execution_time);

    return 0;
}
