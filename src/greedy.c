#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

int compare_smiths_rule(const void *a, const void *b);
int compare_release_times(const void *a, const void *b);

// Greedy Approximation Algorithm using Smith's Rule with dynamic arrivals
// * NOTE: it'd be nice to "trace" it or like, provide a high-level simulation with a small test case on how the algo solves
void greedy_solver(Task tasks[], int n) {
    Task **unscheduled = malloc(n * sizeof(Task *)); // Separate of pointers to keep the original tasks[] memory order intact
    for (int i = 0; i < n; i++) { // Create own "timeline" so we can properly index
        unscheduled[i] = &tasks[i];
    }
    // Pre-sort all (unscheduled) tasks by *release time* 
    // (lets us use that index pointer instead of scanning the whole array repeatedly to know who is next)
    qsort(unscheduled, n, sizeof(Task *), compare_release_times);
        //YAP:
            // qsort parameters: first elem to sort, number of elems to process, size of elem, comparison logic
            // (compar logic that returns a negative integer if the first element is smaller, zero if equal, and a positive integer if larger)

    Task **ready_pool = malloc(n * sizeof(Task *));
    int ready_count = 0;
    
    int current_time = 0;
    int next_arrival_index = 0;
    int scheduled_count = 0;

    // ===================================================================
    // ===================================================================

    // ! Main loop that runs until all tasks are scheduled
    while (scheduled_count < n) {
        // * Feed **newly** arrived tasks into the Ready Pool
        while (next_arrival_index < n) {
            // Create a temporary pointer to the "candidate" task
            Task *candidate = unscheduled[next_arrival_index];
            
            if (candidate->release_time <= current_time) { 
            // If the candidate's release time is within the current_time, we move it to ready pool
                ready_pool[ready_count] = candidate;
                ready_count++;
                next_arrival_index++;
            } else {
            // Since unscheduled is sorted by release_time, if this one hasn't arrived, none after it have either
                break; 
            }
        }
        
        if (ready_count > 0) {
            // * Sort the currently available tasks (ready pool) using Smith's Rule heuristic (basta sorting happens here)
                // WE DIAGNOSE BASED ON HEURISTIC. NOT JUST ARRIVAL.
            qsort(ready_pool, ready_count, sizeof(Task *), compare_smiths_rule);
            
            // Pick the highest priority task (index 0)
            Task *selected_task = ready_pool[0];
            
            // Schedule it and advance the simulated clock
            selected_task->start_time = current_time; // Fill in data of task structure
            selected_task->completion_time = current_time + selected_task->processing_time;  // Fill in data of task structure
            current_time = selected_task->completion_time; // Update algo state
            scheduled_count++;
            
            // Replace the scheduled task with the last task in the pool
                // qsort will correctly reposition this swapped task on the next iteration
            ready_pool[0] = ready_pool[ready_count - 1]; // Moving all elements to the left will be very slow and bad for scaling
            ready_count--; // So it's better to swap-and-shrink, then let qsort relocate that "swap"
            
            // yap: lowk basic lang toh.. as in cpu scheduling logic with a heuristic lang talagaaa
        } else {
            // Idle time when no tasks ready means we fastforward the clock to the next arrival
            if (next_arrival_index < n) {
                current_time = unscheduled[next_arrival_index]->release_time;
            }
        }
    }

    free(unscheduled);
    free(ready_pool);
}

// Sort descending by (Weight / Processing Time)
int compare_smiths_rule(const void *a, const void *b) {
    Task *taskA = *(Task **)a;
    Task *taskB = *(Task **)b;
    
    double ratioA = (double)taskA->weight / taskA->processing_time;
    double ratioB = (double)taskB->weight / taskB->processing_time;
    
    if (ratioA < ratioB) return 1;
    if (ratioA > ratioB) return -1;
    return 0;
}

// Sort ascending by earliest arrival of release time
int compare_release_times(const void *a, const void *b) {
    Task *taskA = *(Task **)a;
    Task *taskB = *(Task **)b;
    return taskA->release_time - taskB->release_time;
}