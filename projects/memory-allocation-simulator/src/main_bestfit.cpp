#include <iostream> // Include the iostream library for input and output operations
#include <fstream> // Include the fstream library for file operations
#include <string> // Include the string library for string operations
#include "memory_manager.h" // Include the custom memory manager header

/**
 * @file main_bestfit.cpp
 * @brief Main program for testing the Best-Fit memory allocation strategy.
 *
 * This program initializes a memory pool and processes commands from a datafile
 * to allocate and deallocate memory using the Best-Fit strategy.
 *
 * Usage:
 *   ./main_bestfit <datafile>
 *
 * The datafile should contain commands in the following format:
 *   alloc: <size>  - Allocates a block of memory of the specified size.
 *   dealloc        - Deallocates the last allocated memory block.
 *
 * The program prints the status of memory allocation and deallocation operations
 * to the standard output.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Returns 0 on successful execution, or 1 on error.
 */
int main(int argc, char* argv[]) {
    // Pre-condition: argc should be at least 2, argv should contain the program name and datafile name
    if (argc < 2) { // Check if the number of command-line arguments is less than 2
        std::cerr << "Error: Please provide a datafile as a command-line argument." << std::endl; // Print error message
        return 1; // Return 1 indicating error
    }

    // Initialize memory with a total size of 1024 bytes for testing
    std::size_t total_memory = 1024; // Define the total memory size as 1024 bytes
    initialize_memory(total_memory); // Initialize the memory pool with the specified size

    // Open the datafile
    std::ifstream infile(argv[1]); // Open the datafile specified in the command-line argument
    if (!infile) { // Check if the file could not be opened
        std::cerr << "Error: Unable to open datafile." << std::endl; // Print error message
        return 1; // Return 1 indicating error
    }

    std::string command; // Define a string to store commands from the datafile
    while (infile >> command) { // Read commands from the datafile
        if (command == "alloc:") { // Check if the command is "alloc:"
            std::size_t size; // Define a variable to store the size of memory to be allocated
            infile >> size; // Read the size from the datafile
            std::cout << "Allocating " << size << " bytes using Best-Fit strategy:" << std::endl; // Print allocation message
            void* address = best_fit_alloc(size); // Allocate memory using the Best-Fit strategy
            if (address != nullptr) { // Check if the allocation was successful
                std::cout << "Successfully allocated " << size << " bytes at address: " << address << std::endl; // Print success message
            } else { // If allocation failed
                std::cerr << "Error: Failed to allocate memory." << std::endl; // Print error message
            }
        } else if (command == "dealloc") { // Check if the command is "dealloc"
            std::cout << "Deallocating the last allocated memory chunk." << std::endl; // Print deallocation message
            // Implement LIFO deallocation (deallocate the last allocated chunk)
            if (!allocated_list.empty()) { // Check if there are allocated memory chunks
                void* last_allocated_address = allocated_list.back().start_address; // Get the address of the last allocated chunk
                dealloc(last_allocated_address); // Deallocate the last allocated chunk
            } else { // If there are no allocated memory chunks
                std::cerr << "Error: No allocated memory to deallocate." << std::endl; // Print error message
            }
        }
    }

    // Print the final memory status
    print_memory_status(); // Print the status of the memory pool

    // Post-condition: Memory pool should be in a consistent state, all allocated memory should be deallocated
    return 0; // Return 0 indicating successful execution
}
