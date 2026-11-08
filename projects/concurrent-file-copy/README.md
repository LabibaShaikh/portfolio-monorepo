# OSP_A1
GitHub repo for Operating Systems Processes Assignment 1: [https://github.com/LabibaShaikh/OSP_A1](https://github.com/LabibaShaikh/OSP_A1)

## Team members: 
- Shaikh Naima Labiba (s3954789)
- Jessica Bath (s3718060)

--- 

All `make` functions are accessible from the root directory.

---

## Task 1

Task completed using pair programming by Shaikh Naima Labiba (s3954789) & Jessica Bath (s3718060).

**To compile:**  
`make` from the root directory.

**To run:**  
From the root directory, run:  
`./mmcopier n source_dir dest_dir`  
*where `n` is the number of files to be copied over from `source_dir` to `dest_dir` and is a positive integer less than or equal to 10.*

---

## Task 2

Task completed using pair programming by Shaikh Naima Labiba (s3954789) & Jessica Bath (s3718060).
**To compile:**  
`make` from the root directory.

**To run:**  
Navigate to the `src` directory, then run:  
`./mscopier n input.txt output.txt`  
*where `n` is an integer between 2 and 10. The program will create `n` reader threads and `n` writer threads. These threads will work concurrently to read from `input.txt` and write to `output.txt`.*

### Locks and Condition Variables Implementation

In Task 2 (`mscopier.cpp`), the following synchronization mechanisms have been implemented to manage concurrent access to shared resources:

1. **Mutex Lock (pthread_mutex_t)**  
   - **File:** `mscopier.cpp`  
   - **Line:** 43  
   - **Purpose:** The `pthread_mutex_t mutex` is declared in the `SharedQueue` structure to synchronize access to the shared queue. This ensures that only one thread can modify the queue at a time.

2. **Condition Variable (pthread_cond_t)**  
   - **File:** `mscopier.cpp`  
   - **Line:** 45-46  
   - **Purpose:** Two condition variables, `not_full` and `not_empty`, are declared to signal threads when the queue is either not full or not empty, respectively. This helps avoid busy waiting and allows threads to sleep while waiting for conditions to be met.

3. **Mutex Lock Usage in Reader Threads**  
   - **File:** `mscopier.cpp`  
   - **Line:** 170 (within `readerThread` function)  
   - **Purpose:** Before accessing or modifying the shared queue, each reader thread locks the mutex to ensure exclusive access.

4. **Condition Variable Wait in Reader Threads**  
   - **File:** `mscopier.cpp`  
   - **Line:** 175 (within `readerThread` function)  
   - **Purpose:** The reader thread waits on the `not_full` condition variable if the queue is full, ensuring it doesn’t add more lines to an already full queue.

5. **Condition Variable Signal in Reader Threads**  
   - **File:** `mscopier.cpp`  
   - **Line:** 184 (within `readerThread` function)  
   - **Purpose:** After adding a line to the queue, the reader thread signals the `not_empty` condition variable, waking up any writer thread that might be waiting.

6. **Mutex Lock Usage in Writer Threads**  
   - **File:** `mscopier.cpp`  
   - **Line:** 195 (within `writerThread` function)  
   - **Purpose:** Before accessing or modifying the shared queue, each writer thread locks the mutex to ensure exclusive access.

7. **Condition Variable Wait in Writer Threads**  
   - **File:** `mscopier.cpp`  
   - **Line:** 200 (within `writerThread` function)  
   - **Purpose:** The writer thread waits on the `not_empty` condition variable if the queue is empty, ensuring it doesn’t try to write when there’s nothing to write.

8. **Condition Variable Signal in Writer Threads**  
   - **File:** `mscopier.cpp`  
   - **Line:** 212 (within `writerThread` function)  
   - **Purpose:** After writing a line from the queue to the destination file, the writer thread signals the `not_full` condition variable, waking up any reader thread that might be waiting.

---

## Additional Instructions

**To generate a word list between 1 to 30:**  
Navigate to the `src` directory and run this command:  
`./generate_text.sh 30 > input.txt`

---
