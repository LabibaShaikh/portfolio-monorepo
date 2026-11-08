/**
 * @file mscopier.cpp
 * @brief Multi-threaded file copying program.
 *Task 2: Multi threaded single file copying.
 *This program copies the contents of a source file to a destination file using
 *multiple reader and writer threads. The number of reader threads is specified
 *by the first command line argument 'n', and the source file and destination
 *file paths are specified by the second and third command line arguments
 *respectively.
 *
 * @note The program expects the following command line arguments: ./mscopier n
 *source_file destination_file
 *       - n: An integer between 2 and 10, specifying the number of reader
 *threads.
 *       - source_file: The path to the source file.
 *       - destination_file: The path to the destination file.
 *
 * @note The program uses a shared queue to store lines read from the source
 *file and a mutex and condition variables for thread synchronization.
 *
 * @note The program creates 'n' reader threads that read lines from the source
 *file and add them to the shared queue. It also creates a writer thread that
 *reads lines from the shared queue and writes them to the destination file.
 *
 * @note The program waits for all reader threads to finish before setting the
 *finished_reading flag to true and signaling the writer thread to finish.
 *
 * @note The program uses mutex and condition variables to ensure thread
 *synchronization and avoid race conditions.
 *
 * @note The program returns 0 if it executed successfully, and 1 otherwise.
 */

#include <fstream>
#include <iostream>
#include <pthread.h>
#include <queue>
#include <string>
#include <sys/stat.h> // For file existence and permissions checking
#include <vector>

#define MAX_QUEUE_SIZE 20

struct SharedQueue {
  std::queue<std::pair<int, std::string>>
      queue;             // Queue to store line number and line content
  pthread_mutex_t mutex; // Mutex for thread synchronization
  pthread_cond_t
      not_full; // Condition variable for signaling when the queue is not full
  pthread_cond_t
      not_empty; // Condition variable for signaling when the queue is not empty
  bool finished_reading = false; // Flag to indicate if reading is finished
  int next_line = 0;             // Next line number to be read
} sharedQueue;

struct ThreadArgs {
  std::ifstream *fin; // Pointer to the input file stream
  int threadId;       // Thread identifier
};

// Function prototypes
void *readerThread(void *arg);
void *writerThread(void *arg);
bool fileExists(const std::string &filename);
bool hasReadPermission(const std::string &filename);
bool hasWritePermission(const std::string &filename);
bool isFileEmpty(const std::string &filename);

/**
 * @brief Main function for the mscopier program.
 *
 * This function is the entry point of the program. It takes command line
 * arguments and performs file copying using multiple reader and writer threads.
 * The number of reader threads is specified by the first command line argument
 * 'n', and the source file and destination file paths are specified by the
 * second and third command line arguments respectively.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @return 0 if the program executed successfully, 1 otherwise.
 */
/**
 * @brief Main function that copies a source file to a destination file using multiple threads.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of strings containing the command-line arguments.
 *             Expected usage: ./mscopier n source_file destination_file
 *             - n: The number of threads to use for copying.
 *             - source_file: The path to the source file to be copied.
 *             - destination_file: The path to the destination file where the source file will be copied to.
 *
 * @return 0 if the copying is successful, 1 otherwise.
 */
int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Invalid number of arguments. Expected usage: ./mscopier n "
                 "source_file destination_file\n";
    return 1;
  }

  // Validate number of threads
  int n = atoi(argv[1]);
  if (n < 2 || n > 10) {
    std::cerr << "Invalid input: n should be an integer between 2 and 10.\n";
    return 1;
  }

  std::string sourceFile = argv[2];
  std::string destFile = argv[3];

  // Check if source file exists and is readable
  if (!fileExists(sourceFile) || !hasReadPermission(sourceFile)) {
    std::cerr << "Error: Source file does not exist or is not readable.\n";
    return 1;
  }

  // Check if destination file exists and if the user has write permission
  if (fileExists(destFile) && !hasWritePermission(destFile)) {
    std::cerr << "Error: Destination file exists but is not writable.\n";
    return 1;
  }

  // Check if source file is empty
  if (isFileEmpty(sourceFile)) {
    std::cerr << "Source file is empty. Nothing to copy.\n";
    return 0;
  }

  // Initialize mutex and condition variables
  pthread_mutex_init(&sharedQueue.mutex, NULL);
  pthread_cond_init(&sharedQueue.not_full, NULL);
  pthread_cond_init(&sharedQueue.not_empty, NULL);

  // Open the source file
  std::ifstream fin(sourceFile);
  if (!fin) {
    std::cerr << "Error opening source file: " << sourceFile << "\n";
    return 1;
  }

  // Close and reopen the destination file in write mode to ensure it's empty
  std::ofstream fout(destFile);
  if (!fout) {
    std::cerr << "Error opening destination file: " << destFile << "\n";
    return 1;
  }
  fout.close();

  std::vector<pthread_t> readers(
      n);           // Vector to store reader thread identifiers
  pthread_t writer; // Writer thread identifier

  // Create reader threads
  for (int i = 0; i < n; ++i) {
    ThreadArgs *args = new ThreadArgs{&fin, i + 1}; // Create thread arguments
    pthread_create(&readers[i], NULL, readerThread, args);
  }


  // Create the writer thread
  pthread_create(&writer, NULL, writerThread,
                 (void *)new std::string(destFile));

  // Wait for all reader threads to finish
  for (int i = 0; i < n; ++i) {
    pthread_join(readers[i], NULL);
  }

  // Signal the writer thread that reading is finished
  pthread_mutex_lock(&sharedQueue.mutex);
  sharedQueue.finished_reading = true; // Set finished_reading flag to true
  pthread_cond_broadcast(
      &sharedQueue.not_empty); // Signal all waiting writer threads
  pthread_mutex_unlock(&sharedQueue.mutex);

  // Wait for the writer thread to finish
  pthread_join(writer, NULL);

  // Clean up mutexes and condition variables
  pthread_mutex_destroy(&sharedQueue.mutex);
  pthread_cond_destroy(&sharedQueue.not_full);
  pthread_cond_destroy(&sharedQueue.not_empty);

  return 0;
}

// Method summary: Reader thread function that reads lines from the input file
// and adds them to the shared queue
void *readerThread(void *arg) {
  ThreadArgs *args = static_cast<ThreadArgs *>(arg);
  std::ifstream *fin = args->fin;
  std::string line;

  while (true) {
    pthread_mutex_lock(&sharedQueue.mutex); // Acquire the mutex

    while (sharedQueue.queue.size() >= MAX_QUEUE_SIZE) {
      pthread_cond_wait(&sharedQueue.not_full,
                        &sharedQueue.mutex); // Wait until the queue is not full
    }

    if (!std::getline(*fin, line)) { // Read a line from the input file
      pthread_mutex_unlock(&sharedQueue.mutex); // Release the mutex
      break;
    }

    sharedQueue.queue.push(
        std::make_pair(sharedQueue.next_line++, line)); // Add line to the queue
    pthread_cond_signal(
        &sharedQueue.not_empty); // Signal a waiting writer thread

    pthread_mutex_unlock(&sharedQueue.mutex); // Release the mutex
  }

  delete args;        // Delete the thread arguments
  pthread_exit(NULL); // Exit the thread
}

// Method summary: Writer thread function that reads lines from the shared queue
// and writes them to the output file
void *writerThread(void *arg) {
  std::string *destFile = static_cast<std::string *>(arg);
  std::ofstream fout(*destFile,
                     std::ios::app); // Open the output file in append mode

  if (!fout) {
    std::cerr << "Error opening destination file: " << *destFile << "\n";
    delete destFile;
    pthread_exit(NULL);
  }

  while (true) {
    pthread_mutex_lock(&sharedQueue.mutex); // Acquire the mutex

    while (sharedQueue.queue.empty() && !sharedQueue.finished_reading) {
      pthread_cond_wait(&sharedQueue.not_empty,
                        &sharedQueue.mutex); // Wait until the queue is not
                                             // empty or reading is finished
    }

    if (sharedQueue.queue.empty() && sharedQueue.finished_reading) {
      pthread_mutex_unlock(&sharedQueue.mutex); // Release the mutex
      break;
    }

    auto line_pair =
        sharedQueue.queue.front();    // Get the front line from the queue
    sharedQueue.queue.pop();          // Remove the front line from the queue
    fout << line_pair.second << "\n"; // Write the line to the output file

    pthread_cond_signal(
        &sharedQueue.not_full);               // Signal a waiting reader thread
    pthread_mutex_unlock(&sharedQueue.mutex); // Release the mutex
  }

  fout.close();       // Close the output file
  delete destFile;    // Delete the string pointer
  pthread_exit(NULL); // Exit the thread
}

// Method to check if a file exists
bool fileExists(const std::string &filename) {
  struct stat buffer;
  return (stat(filename.c_str(), &buffer) == 0);
}

// Method to check if the file has read permission
#include <unistd.h>

bool hasReadPermission(const std::string &filename) {
  return (access(filename.c_str(), R_OK) == 0);
}

// Method to check if the file has write permission
bool hasWritePermission(const std::string &filename) {
  return (access(filename.c_str(), W_OK) == 0);
}

// Method to check if the file is empty
bool isFileEmpty(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  return file.tellg() == 0;
}
