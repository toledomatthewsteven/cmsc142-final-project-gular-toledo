#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "tasks.h"

#define MAX_TASKS 10005 

void run_scenario(const char* filename, int algo_choice);

int main() {
    int algo_choice = 0;
    int file_choice = 0;

    while (1) {
        printf("\n====================================================\n");
        printf("CMSC 142 TESTING HUB: Minimum Sequencing with Release Times\n");
        printf("====================================================\n");

        printf("Select Algorithm:\n");
        printf("1. Brute Force (Exact)\n");
        printf("2. Greedy (WSPT Heuristic)\n");
        printf("0. EXIT Program\n");
        printf("Choice: ");
        scanf("%d", &algo_choice);

        if (algo_choice == 0) break;
        if (algo_choice < 1 || algo_choice > 2) {
            printf("Invalid choice. Try again.\n");
            continue;
        }

        printf("\nSelect Dataset:\n");
        printf("1. N=8  (test_n8.csv)\n");
        printf("2. N=9  (test_n9.csv)\n");
        printf("3. N=10 (test_n10.csv)\n");
        printf("4. N=11 (test_n11.csv) - [Danger zone for Brute Force begins]\n");
        printf("5. N=12 (test_n12.csv)\n");
        printf("6. N=10,000 (test_massive.csv)\n");
        printf("Choice: ");
        scanf("%d", &file_choice);

        // Map the choice to the correct filename
        char* filename = "";
        switch (file_choice) {
            case 1: filename = "data/test_n8.csv"; break;
            case 2: filename = "data/test_n9.csv"; break;
            case 3: filename = "data/test_n10.csv"; break;
            case 4: filename = "data/test_n11.csv"; break;
            case 5: filename = "data/test_n12.csv"; break;
            case 6: filename = "data/test_massive.csv"; break;
            default:
                printf("Invalid dataset choice.\n");
                continue;
        }

        // Safety catch for the massive case
        if (algo_choice == 1 && file_choice == 6) {
            printf("\nCAUTION: Brute Force tests every permutation (N!).\n");
            printf("Running N=10,000 on Brute Force will crash your system.\n");
            printf("Returning to main menu...\n");
            continue; 
        }

        run_scenario(filename, algo_choice);
    }

    printf("\nExiting testing hub. Goodbye!\n");
    return 0;
}


void run_scenario(const char* filename, int algo_choice) {
    Task* tasks = malloc(MAX_TASKS * sizeof(Task));
    if (tasks == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }
    
    int num_tasks = read_csv_to_array(filename, tasks, MAX_TASKS);
    if (num_tasks <= 0) {
        printf("Error: Failed to load tasks from %s\n", filename);
        free(tasks);
        return;
    }

    printf("\n[ Loaded %d tasks from %s ]\n", num_tasks, filename);

    // Set up timer variables
    clock_t start_time, end_time;
    double time_taken;

    if (algo_choice == 1) {
        printf("Running Brute Force Solver (Exact Algorithm)...\n");
        start_time = clock();
        brute_force_solver(tasks, num_tasks); 
        end_time = clock();
    } else if (algo_choice == 2) {
        printf("Running Greedy Solver (WSPT Heuristic)...\n");
        start_time = clock();
        greedy_solver(tasks, num_tasks);
        end_time = clock();
    }

    // Calculate time taken in milliseconds
    time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000;

    // Only calculate cost and print if we actually ran the Greedy algorithm
    // TODO: (Update this to if (algo_choice == 1 || algo_choice == 2) later)
    if (algo_choice == 1) { 
        long long total_cost = calculate_cost(tasks, num_tasks);

        if (num_tasks <= 20) {
            printf("\n--- Schedule Results ---\n");
            printf("ID\tRel\tWgt\tP_Time\tStart\tEnd\n");
            for (int i = 0; i < num_tasks; i++) {
                printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
                       tasks[i].id, tasks[i].release_time, tasks[i].weight, 
                       tasks[i].processing_time, tasks[i].start_time, tasks[i].completion_time);
            }
        } else {
            printf("\n[Schedule table hidden to prevent terminal flood for large dataset]\n");
        }
        
        printf("\n====================================================\n");
        printf("RESULTS:\n");
        printf("Total Weighted Completion Time: %lld\n", total_cost);
        printf("Execution Time: %.3f milliseconds\n", time_taken);
        printf("====================================================\n");
    } else if (algo_choice == 2) { 
        long long total_cost = calculate_cost(tasks, num_tasks);

        if (num_tasks <= 20) {
            printf("\n--- Schedule Results ---\n");
            printf("ID\tRel\tWgt\tP_Time\tStart\tEnd\n");
            for (int i = 0; i < num_tasks; i++) {
                printf("%d\t%d\t%d\t%d\t%d\t%d\n", 
                       tasks[i].id, tasks[i].release_time, tasks[i].weight, 
                       tasks[i].processing_time, tasks[i].start_time, tasks[i].completion_time);
            }
        } else {
            printf("\n[Schedule table hidden to prevent terminal flood for large dataset]\n");
        }
        
        printf("\n====================================================\n");
        printf("RESULTS:\n");
        printf("Total Weighted Completion Time: %lld\n", total_cost);
        printf("Execution Time: %.3f milliseconds\n", time_taken);
        printf("====================================================\n");
    }

    free(tasks);
}