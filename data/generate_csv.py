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
    print("Generating testing suite...")
    
    # Stepping stones for the Complexity Curve (N=8 to 12)
    sizes = [4, 5, 6, 7, 8, 9, 10, 11, 12]
    for n in sizes:
        generate_test_case(f'test_n{n}.csv', n, max_release=30, max_weight=10, max_processing=50)

    # The massive case for the scalability proof
    generate_test_case('test_massive.csv', 10000, max_release=500, max_weight=10, max_processing=50)
    
    print("Done! Files are ready in the data/ folder.")