#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tasks.h"

// Calculates the sum of w_j * C_j for a given schedule
long long calculate_cost(Task tasks[], int n) {
    long long total_cost = 0;
    for (int i = 0; i < n; i++) {
        total_cost += (long long)tasks[i].weight * tasks[i].completion_time;
    }
    return total_cost;
}

// Reads tasks from a CSV file and populates the tasks array
int read_csv_to_array(const char* filename, Task tasks[], int max_tasks) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file %s\n", filename);
        return -1; 
    }

    char line[256];
    int count = 0;

    // Read and discard the first line (the header row: id,release_time,weight,processing_time)
    if (fgets(line, sizeof(line), file) == NULL) {
        printf("Error: File %s is empty\n", filename);
        fclose(file);
        return 0;
    }

    // Read the remaining lines until we hit the end of the file or max_tasks
    while (fgets(line, sizeof(line), file) != NULL && count < max_tasks) {
        int id, r_j, w_j, p_j;
        
        // Parse the comma-separated integers
        if (sscanf(line, "%d,%d,%d,%d", &id, &r_j, &w_j, &p_j) == 4) {
            tasks[count].id = id;
            tasks[count].release_time = r_j; 
            tasks[count].weight = w_j; 
            tasks[count].processing_time = p_j;
            
            // Initialize calculated fields safely
            tasks[count].start_time = 0;
            tasks[count].completion_time = 0;
            
            count++;
        } else {
            printf("Warning: Malformed data on line %d in %s\n", count + 2, filename);
        }
    }

    fclose(file);
    return count; // Return the actual number of tasks successfully read
}