import csv
import random

def generate_test_case(filename, n, max_release, max_weight, max_processing):
    with open(filename, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['id', 'release_time', 'weight', 'processing_time'])
        for i in range(n):
            r_j = random.randint(0, max_release)
            w_j = random.randint(1, max_weight)
            p_j = random.randint(1, max_processing)
            writer.writerow([i, r_j, w_j, p_j])
    print(f"Generated {filename} with {n} tasks.")

if __name__ == "__main__":
    # For N=8, keep release times VERY small (0 to 30) so they pile up in the queue
    # while processing times can still be up to 50. 
    generate_test_case('test_small.csv', 8, max_release=30, max_weight=10, max_processing=50)
    
    # For N=10,000, a release range of 0 to 500 is perfectly fine because 
    # the sheer volume of tasks will guarantee a massive queue.
    generate_test_case('test_massive.csv', 10000, max_release=500, max_weight=10, max_processing=50)