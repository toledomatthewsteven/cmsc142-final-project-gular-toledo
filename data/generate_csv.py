import csv
import random
import os

def generate_test_case(filename, n):
    with open(filename, 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['id', 'release_time', 'weight', 'processing_time'])
        for i in range(n):
            r_j = random.randint(0, 500)
            w_j = random.randint(1, 10)
            p_j = random.randint(1, 50)
            writer.writerow([i, r_j, w_j, p_j])
    print(f"Generated {filename} with {n} tasks.")

if __name__ == "__main__":
    generate_test_case('test_small.csv', 8)
    generate_test_case('test_massive.csv', 10000)