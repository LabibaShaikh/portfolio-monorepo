#include <iostream> // Include the iostream library for input and output operations
#include <fstream> // Include the fstream library for file operations
#include <string> // Include the string library for string operations
#include "memory_manager.h" // Include the custom memory manager header

/**
 * @file main_firstfit.cpp
 * @brief Main program for memory allocation using the First-Fit strategy.
 *
 * This program initializes a memory pool and processes commands from a datafile
 * to allocate and deallocate memory using the First-Fit strategy. The commands
 * are read from a file provided as a command-line argument.
 *
 * Usage:
 *   ./main_firstfit <datafile>
 *
 * The datafile should contain commands in the following format:
 *   - "alloc: <size>" to allocate a block of memory of the specified size.
 *   - "dealloc" to deallocate the last allocated memory block.
 *
 * The program prints the status of memory allocation and deallocation operations
 * to the standard output.
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status of the program.
 */
int main(int argc, char* argv[]) {
    // Pre-condition: argc should be greater than or equal to 2
    if (argc < 2) { // Check if the number of command-line arguments is less than 2
        std::cerr << "Error: Please provide a datafile as a command-line argument." << std::endl; // Print an error message
        return 1; // Return with an error code
    }

    // Initialize memory with a total size of 1024 bytes for testing
    std::size_t total_memory = 1024; // Define the total memory size
    initialize_memory(total_memory); // Initialize the memory pool with the specified size

    // Open the datafile
    std::ifstream infile(argv[1]); // Open the file specified by the command-line argument
    if (!infile) { // Check if the file could not be opened
        std::cerr << "Error: Unable to open datafile." << std::endl; // Print an error message
        return 1; // Return with an error code
    }

    std::string command; // Define a string to hold the command
    while (infile >> command) { // Read commands from the file
        if (command == "alloc:") { // Check if the command is "alloc:"
            std::size_t size; // Define a variable to hold the size
            infile >> size; // Read the size from the file
            std::cout << "Allocating " << size << " bytes using First-Fit strategy:" << std::endl; // Print the allocation message
            void* address = first_fit_alloc(size); // Allocate memory using the First-Fit strategy
            if (address != nullptr) { // Check if the allocation was successful
                std::cout << "Successfully allocated " << size << " bytes at address: " << address << std::endl; // Print the success message
            } else { // If the allocation failed
                std::cerr << "Error: Failed to allocate memory." << std::endl; // Print an error message
            }
        } else if (command == "dealloc") { // Check if the command is "dealloc"
            std::cout << "Deallocating the last allocated memory chunk." << std::endl; // Print the deallocation message
            // Implement LIFO deallocation (deallocate the last allocated chunk)
            if (!allocated_list.empty()) { // Check if there are allocated memory chunks
                void* last_allocated_address = allocated_list.back().start_address; // Get the address of the last allocated chunk
                dealloc(last_allocated_address); // Deallocate the last allocated chunk
            } else { // If there are no allocated memory chunks
                std::cerr << "Error: No allocated memory to deallocate." << std::endl; // Print an error message
            }
        }
    }

    // Print the final memory status
    print_memory_status(); // Print the status of the memory pool

    // Post-condition: The program should have processed all commands in the datafile
    return 0; // Return with a success code
}
