/**
 * @file mmcoper.cpp
 * @brief Multi-threaded file copier program.
 * Task 1: Multi-threaded multiple file copying.
 * This program copies multiple files from a source directory to a destination
 * directory using multiple threads. The number of files to be copied and the
 * source and destination directories are provided as command line arguments.
 * The program creates a separate thread for each file to be copied and uses the
 * pthread library for thread management. Each thread reads the contents of a
 * source file and writes it to a destination file. The program ensures that the
 * number of threads created does not exceed a maximum limit.
 *
 * @note This program assumes that the source files are named "sourceX.txt" and
 * the destination files are named "destX.txt", where X is the index of the
 * file.
 * @note The program expects the following command line arguments: ./mmcopier n
 * source_dir destination_dir, where n is the number of files to be copied,
 * source_dir is the source directory, and destination_dir is the destination
 * directory.
 * @note The program checks if the input arguments are valid integers and within
 * the specified range.
 * @note The program displays error messages if the input arguments are invalid
 * or if there are any issues with file operations.
 */
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <string>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>

#define NUM_ARGS 4
#define MAX_NUM_FILES 10
#define SOURCE_FILE_PRE "source"
#define DEST_FILE_PRE "dest"
#define FILE_EXT ".txt"

// Structure to hold the arguments for copying a file
struct CopyArgs {
  int fileIndex;
  std::string sourceDir;
  std::string destDir;
};

// Check if the input arguments are valid integers
bool validIntInput(int argc, char *argv[]);

// Function executed by each thread to copy a file
void *copyFile(void *arg);

/**
 * @brief Main function that copies files using multiple threads.
 *
 * This function takes command line arguments and performs the following steps:
 * 1. Checks if the correct number of arguments are provided.
 * 2. Checks if the input arguments are valid integers.
 * 3. Converts the first argument to an integer.
 * 4. Creates a vector to hold thread IDs and a vector to hold copy arguments.
 * 5. Sets the source and destination directories.
 * 6. Creates threads to copy files, each thread using a different copy
 * argument.
 * 7. Waits for all threads to finish.
 *
 * @param argc The number of command line arguments.
 * @param argv An array of strings containing the command line arguments.
 * @return 0 if the program executed successfully, 1 otherwise.
 */
int main(int argc, char *argv[]) {
  // Check if the correct number of arguments are provided
  if (argc == NUM_ARGS) {
    // Check if the input arguments are valid integers
    if (validIntInput(argc, argv)) {
      int n = atoi(argv[1]); // Convert the argument to an integer

      std::vector<pthread_t> threads(n); // Vector to hold thread IDs
      std::vector<CopyArgs> args(n);     // Vector to hold copy arguments

      std::string source = argv[2]; // Source directory
      std::string dest = argv[3];   // Destination directory

      // Create threads to copy files
      for (int i = 0; i < n; ++i) {
        args[i] = {i + 1, source, dest}; // Set copy arguments
        pthread_create(&threads[i], NULL, copyFile, &args[i]); // Create thread
      }

      // Wait for all threads to finish
      for (int i = 0; i < n; ++i) {
        pthread_join(threads[i], NULL); // Wait for thread to finish
      }
    } else {
      std::cerr << "Invalid input: n should be a positive integer less than or "
                   "equal to 10.\n";
      return 1;
    }
  } else {
    std::cerr << "Invalid number of arguments. Expected arguments: ./mmcopier "
                 "n source_dir destination_dir\n";
    return 1;
  }
  return 0;
}

// Check if the input argument is a valid integer within the specified range
bool validIntInput(int argc, char *argv[]) {
  int n = atoi(argv[1]); // Convert the argument to an integer
  return n > 0 &&
         n <= MAX_NUM_FILES; // Check if the integer is within the range
}

// Function executed by each thread to copy a file
void *copyFile(void *arg) {
  CopyArgs *args =
      static_cast<CopyArgs *>(arg); // Cast the argument to the correct type
  std::string sourceFile = args->sourceDir + "/" + SOURCE_FILE_PRE +
                           std::to_string(args->fileIndex) +
                           FILE_EXT; // Generate source file path
  std::string destFile = args->destDir + "/" + DEST_FILE_PRE +
                         std::to_string(args->fileIndex) +
                         FILE_EXT; // Generate destination file path

  std::ifstream fin(sourceFile); // Open source file for reading
  if (!fin) {
    std::cerr << "Error opening source file: " << sourceFile << "\n";
    pthread_exit(NULL); // Exit the thread
  }

  std::ofstream fout(destFile); // Open destination file for writing
  if (!fout) {
    std::cerr << "Error opening destination file: " << destFile << "\n";
    pthread_exit(NULL); // Exit the thread
  }

  std::string line;
  while (std::getline(fin, line)) {
    fout << line << "\n"; // Copy each line from source file to destination file
  }

  pthread_exit(NULL); // Exit the thread
}
