# OSP_A3
# Memory Allocation Simulation

## Author Information
- **Name**: Shaikh Naima Labiba
- **Student Number**: s3954789
- **Repo Link**: [https://github.com/LabibaShaikh/OSP_A3.git]
# OSP_A3: Memory Allocation Simulation

## Author Information
- **Name**: Shaikh Naima Labiba
- **Student Number**: s3954789

## Project Overview
This project simulates memory management techniques in operating systems, specifically focusing on **First-Fit** and **Best-Fit** memory allocation strategies. The project is written in **C++**, using **linked lists** to manage allocated and free memory chunks. The simulation demonstrates the efficiency and drawbacks of these two allocation techniques in various scenarios.

## Project Tasks
The project has been divided into the following tasks:

### Task 1: Solution Design (10 marks)
- Utilized **linked lists** to manage memory allocations and free memory chunks.
- Implemented a `struct allocation` to represent memory chunks.
- Used global variables to track memory chunks.

### Task 2: Memory Allocation (10 marks)
- Implemented `alloc()` to allocate memory in fixed partition sizes of **32, 64, 128, 256, and 512 bytes**.
- Memory expansion handled using the **`sbrk()`** system call if no suitable chunk is available.

### Task 3: Allocation Strategies (25 marks)
- **First-Fit**: Allocates the first chunk that fits.
- **Best-Fit**: Allocates the smallest chunk that fits, minimizing fragmentation.

### Task 4: Memory Deallocation (10 marks)
- Implemented `dealloc()` to deallocate allocated memory chunks and return them to the free list.
- Merged adjacent free chunks to reduce fragmentation.

### Task 5: Testing (5 marks)
- Used the provided **`p2_gen.sh`** script to generate test sequences.
- Tested memory management with interleaved **alloc** and **dealloc** commands.

## Project Structure

```
OSP_A3/
├── src/
│   ├── main_firstfit.cpp        # Entry point for the First-Fit strategy
│   ├── main_bestfit.cpp         # Entry point for the Best-Fit strategy
│   ├── memory_manager.cpp       # Memory allocation and deallocation logic
│   ├── first_fit.cpp            # Implementation of the First-Fit strategy
│   ├── best_fit.cpp             # Implementation of the Best-Fit strategy
│   ├── include/
│   │   └── memory_manager.h     # Header file for memory management functions and structs
├── p2_gen.sh                # Script to generate test data
├── datafile                 # Sample data file for testing
├── bin/
│   ├── firstfit                 # Compiled executable for First-Fit strategy
│   ├── bestfit                  # Compiled executable for Best-Fit strategy
├── build/
│   └── *.o                      # Object files generated during compilation
├── Makefile                     # Makefile for building and cleaning the project
├── README.md                    # Project documentation and instructions
└── LICENSE                      # License for the project

```


## Building and Running the Project

### Prerequisites
- A Linux environment or **WSL** (Windows Subsystem for Linux) is required for compiling and running the program.
- **Make** must be installed to use the provided Makefile.

### Build Instructions
1. Clone the repository:
  ```bash
  git clone https://github.com/LabibaShaikh/OSP_A3.git
  ```

2. Navigate to the project directory and build the project:
  ```bash
  cd OSP_A3
  make all
  ```

3. Running the project:

  You can run both First-Fit and Best-Fit allocation strategies using the following commands:

  **First-Fit Allocation:**
  ```bash
  ./bin/firstfit datafile
  ```

  **Best-Fit Allocation:**
  ```bash
  ./bin/bestfit datafile
  ```

  Where `datafile` is the generated file containing a sequence of `alloc` and `dealloc` commands.

4. Generating Test Data:
  To generate test sequences of `alloc` and `dealloc` commands, first make the `p2_gen.sh` script executable and then run it:

  ```bash
  chmod +x p2_gen.sh
  ./p2_gen.sh 20 > datafile
  ```

  This command will generate 20 interleaved `alloc` and `dealloc` commands into a `datafile`.

5. Cleaning the Build:
  To clean up object files and executables, run the following command:
  ```bash
  make clean
  ```

6. Testing the Project:
  Use the `p2_gen.sh` script to generate test sequences, then run the project with the generated `datafile` using the `firstfit` or `bestfit` executables.
  Example test generation and execution:
  ```bash
  ./p2_gen.sh 20 > datafile
  ./bin/firstfit datafile   # Run First-Fit strategy
  ./bin/bestfit datafile    # Run Best-Fit strategy
  ```
  This will execute the First-Fit and Best-Fit allocation strategies and display the allocated and free memory chunks.

  Note: The project dynamically expands the memory pool if the required chunk size is not available. This feature simulates real-world memory management where memory may be expanded when necessary.

## License
This project is licensed under the MIT License. See the LICENSE file for details.
