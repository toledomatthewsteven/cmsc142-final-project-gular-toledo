# CMSC 142: Minimum Sequencing with Release Times

To compile:
```bash
make
./scheduler
```

## 🗂️ Repository Structure
```text
cmsc142-final-project-gular-toledo/
│
├── .gitignore               # Ignores compiled binaries
├── README.md                # Project documentation
│
├── src/                     # C Source Code
│   ├── main.c               # Shared entry point for both algorithms
│   ├── tasks.h              # Task struct definition and function prototypes
│   ├── utils.c              # Helper functions (CSV reader, cost calculator)
│   ├── brute_force.c        # Exact algorithm implementation (Track A)
│   └── greedy.c             # Approximation algorithm implementation (Track B)
│
└── data/                    # Datasets and Generators
    ├── generate_csv.py      # Python script to generate random task instances
    ├── test_n8-12.csv       # N=8 to 12 test cases (multiple files)
    └── test_massive.csv     # N=10,000 test case