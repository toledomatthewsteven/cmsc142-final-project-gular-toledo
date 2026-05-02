/*
A solution that explores the entire 
search space (all possible task permutations)
 to guarantee finding the optimal schedule.
*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "tasks.h"

#define MAX_TASKS 10005 

// ORIGINAL PLAN : generate each permutation, solve each needed data then choose based off that
// realized that would take too much space so searched for a different approach

// permutation_generator uses a lexicographical permutation approach through iteration
// it starts with the smallest permutation, then identifies a pivot point and swaps the cell
// and then reverses the suffix
// source : https://www.geeksforgeeks.org/dsa/lexicographic-permutations-of-string/
int permutation_generator(Task tasks[], int n){
    // find the rightmost index whose index is smaller than the next
    int pivot = -1;
    for (int i = n - 2; i >= 0; i--) {
        if (tasks[i].id < tasks[i + 1].id) {
            pivot = i;
            break;
        }
    }

    // if there is no pivot, then we return and we have exhausted all permutations
    if (pivot == -1) return 0;

    // find the rightmost task that is greater than the pivot index
    int swap = -1;
    for (int i = n - 1; i > pivot; i--) {
        if (tasks[i].id > tasks[pivot].id) {
            swap = i;
            break;
        }
    }

    // swap the tasks places
    Task temp = tasks[pivot];
    tasks[pivot] = tasks[swap];
    tasks[swap] = temp;

    // sort the tasks after index i so it will be ascending
    int left = pivot + 1, right = n - 1;
    while (left < right) {
        Task tmp = tasks[left];
        tasks[left] = tasks[right];
        tasks[right] = tmp;
        left++;
        right--;
    }

    return 1;
}

// brute_force_solver iterates through each possible permutation, 
// gets the lowest_cost out of all permutation and returns the 
// specific schedule of tasks back to main
void brute_force_solver(Task tasks[], int n){
    long long lowest_cost = LLONG_MAX; //set to max so that the first lowest cost will be set to base
    Task best_schedule[MAX_TASKS]; 

    do{
        int clock = 0; 
        long long current_cost = 0;

        for (int i = 0; i < n; i++){
            if (clock < tasks[i].release_time) {
                // If the clock doesnt satisfy the release time, 
                // fast forward the clock with the release time
                // which will also affect the completion time of the current task
                tasks[i].start_time = tasks[i].release_time;
            } else {
                tasks[i].start_time = clock;
            }

            tasks[i].completion_time = tasks[i].start_time + tasks[i].processing_time;
            
            clock = tasks[i].completion_time;
        }

        //calculate best cost!
        current_cost = calculate_cost(tasks, n);

        //  Checks if the current permutation has the lowest cost, 
        //  if it does it stores its cost as the lowest cost and copies the 
        //  current schedule to best_schedule!
        if (current_cost < lowest_cost){
            lowest_cost = current_cost;
            // Copy the current set of tasks into best_schedule.
            memcpy(best_schedule, tasks, n * sizeof(Task));
        }
    } while(permutation_generator(tasks,n));

    memcpy(tasks, best_schedule, n * sizeof(Task)); // reset the global Task struct to the best schedule struct
}


// // IGNORE THIS PART, THIS WAS FOR TESTING YEHEY
// int main(){
//     char* filename = "../data/test_n8.csv";

//     Task* tasks = malloc(MAX_TASKS * sizeof(Task));
//     if (tasks == NULL) {
//         printf("Error: Memory allocation failed!\n");
//     }
    
//     int num_tasks = read_csv_to_array(filename, tasks, MAX_TASKS);
//     if (num_tasks <= 0) {
//         printf("Error: Failed to load tasks from %s\n", filename);
//         free(tasks);
//     }

//     for (int i = 0; i < num_tasks; i++) {
//             printf("%2d | %3d | %3d | %3d | %5d | %8d\n",
//                 tasks[i].id,
//                 tasks[i].release_time,
//                 tasks[i].processing_time,
//                 tasks[i].weight,
//                 tasks[i].start_time,
//                 tasks[i].completion_time);
//         }
   

//     brute_force_solver(tasks, num_tasks);

//      return 0;
// }
        


