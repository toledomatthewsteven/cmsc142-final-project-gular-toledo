#ifndef TASKS_H
#define TASKS_H

typedef struct {
    int id;           
    int release_time; 
    int weight;       
    int processing_time; 
    int start_time;   
    int completion_time; 
} Task;

// Shared Function Prototypes
long long calculate_cost(Task tasks[], int n);
int read_csv_to_array(const char* filename, Task tasks[], int max_tasks);
void greedy_solver(Task tasks[], int n);
void brute_force_solver(Task tasks[], int n);

#endif