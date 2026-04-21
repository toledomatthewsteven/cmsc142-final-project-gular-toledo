#include <stdio.h>
#include "tasks.h"

// Calculates the sum of w_j * C_j for a given schedule
long long calculate_cost(Task tasks[], int n) {
    long long total_cost = 0;
    for (int i = 0; i < n; i++) {
        total_cost += (long long)tasks[i].weight * tasks[i].completion_time;
    }
    return total_cost;
}

// TODO: Implement CSV reading logic to populate the tasks array
int read_csv_to_array(const char* filename, Task tasks[], int max_tasks) {
    // Placeholder for CSV parsing logic
    return 0; // Return number of tasks read
}