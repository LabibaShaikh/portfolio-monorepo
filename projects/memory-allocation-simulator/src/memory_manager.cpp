#include <iostream>  // Include the iostream library for input/output operations 
#include <list>      // Include the list library for using std::list
#include <cstddef>   // Include the cstddef library for std::size_t
#include <cstdint>   // Include std::uintptr_t for address comparisons
#include <unistd.h>  // Include the unistd library for sbrk()

// Structure to represent a memory allocation
struct Allocation {
    std::size_t size;  // Size of the memory chunk
    void* start_address;  // Start address of the allocated memory
    void* end_address;    // End address of the allocated memory
};

// Global variables to manage memory chunks
std::list<Allocation> allocated_list;  // List of allocated memory chunks
std::list<Allocation> free_list;       // List of free memory chunks

// Function to initialize memory (for demonstration purposes)
// Pre-condition: total_memory is a positive integer representing the total amount of memory to initialize.
// Post-condition: A single free memory chunk of the specified size is created and added to the free list.
void initialize_memory(std::size_t total_memory) {
    // Create an initial free memory chunk of the given size
    Allocation initial_free_chunk;
    initial_free_chunk.size = total_memory;
    initial_free_chunk.start_address = sbrk(total_memory); // Allocate memory using sbrk
    
    // Add the initial chunk to the free list
    free_list.push_back(initial_free_chunk);
    
    // Post-condition: The free list contains one chunk of the specified size.
}

// Helper function to enforce fixed partition sizes
// Pre-condition: requested_size is a positive integer representing the size of memory requested.
// Post-condition: Returns the fixed partition size that is greater than or equal to the requested size. 
// If the requested size exceeds the maximum partition size (512 bytes), an error message is printed and 0 is returned.
std::size_t get_fixed_size(std::size_t requested_size) {
    if (requested_size <= 32) return 32;  // Return 32 if requested size is less than or equal to 32
    else if (requested_size <= 64) return 64;  // Return 64 if requested size is less than or equal to 64
    else if (requested_size <= 128) return 128;  // Return 128 if requested size is less than or equal to 128
    else if (requested_size <= 256) return 256;  // Return 256 if requested size is less than or equal to 256
    else if (requested_size <= 512) return 512;  // Return 512 if requested size is less than or equal to 512
    else {
        std::cerr << "Error: Requested size exceeds maximum partition size (512 bytes)." << std::endl;
        return 0; // Return 0 for invalid size
    }
}

// Function to print the current status of memory (allocated and free chunks)
// Pre-condition: The global lists allocated_list and free_list may contain memory chunks.
// Post-condition: The status of all allocated and free memory chunks is printed to the console.
void print_memory_status() {
    std::cout << "\nAllocated Memory Chunks:" << std::endl;
    for (const auto& chunk : allocated_list) {  // Iterate through the allocated list
        std::cout << "Start Address: " << chunk.start_address
                  << ", End Address: " << chunk.end_address
                  << ", Size: " << chunk.size << " bytes" << std::endl;
    }

    std::cout << "\nFree Memory Chunks:" << std::endl;
    for (const auto& chunk : free_list) {  // Iterate through the free list
        std::cout << "Start Address: " << chunk.start_address
                  << ", End Address: " << chunk.end_address
                  << ", Size: " << chunk.size << " bytes" << std::endl;
    }
}

// Function to deallocate memory
// Pre-condition: address is a pointer to a memory chunk that was previously allocated.
// Post-condition: The specified memory chunk is deallocated and moved back to the free list. Adjacent chunks are merged to reduce fragmentation.

const std::size_t ALIGNMENT_TOLERANCE = 256;  // Allow for a larger alignment discrepancy

/**
 * @brief Deallocates a previously allocated memory chunk.
 *
 * This function searches for the memory chunk corresponding to the given address
 * in the allocated list, removes it from the allocated list, and inserts it into
 * the free list in sorted order. It then attempts to merge the newly freed chunk
 * with adjacent free chunks if they are within the alignment tolerance.
 *
 * @param address The starting address of the memory chunk to be deallocated.
 *
 * @details
 * - If the address is found in the allocated list, the corresponding chunk is
 *   removed from the allocated list and inserted into the free list.
 * - The free list is maintained in sorted order based on the starting address of
 *   the chunks.
 * - The function attempts to merge the newly freed chunk with the next and previous
 *   chunks in the free list if they are within the alignment tolerance.
 * - If the address is not found in the allocated list, an error message is printed.
 *
 * @note The function assumes that the free list and allocated list are maintained
 *       as sorted lists based on the starting address of the chunks.
 */
void dealloc(void* address) {
    for (auto it = allocated_list.begin(); it != allocated_list.end(); ++it) {  // Iterate through the allocated list
        if (it->start_address == address) {  // Check if the start address matches the given address
            Allocation freed_chunk = *it;  // Copy the allocation to be freed
            allocated_list.erase(it);  // Remove the allocation from the allocated list

            // Insert the chunk into the free list in sorted order
            auto free_it = free_list.begin();
            while (free_it != free_list.end() && free_it->start_address < freed_chunk.start_address) {
                ++free_it;
            }
            free_it = free_list.insert(free_it, freed_chunk);  // Insert the freed chunk into the free list

            // Merge with next chunk if within alignment tolerance
            auto next_it = std::next(free_it);
            if (next_it != free_list.end()) {
                uintptr_t current_end_address = reinterpret_cast<uintptr_t>(free_it->end_address);
                uintptr_t next_start_address = reinterpret_cast<uintptr_t>(next_it->start_address);
                if ((next_start_address - current_end_address) <= ALIGNMENT_TOLERANCE) {
                    free_it->size += next_it->size + (next_start_address - current_end_address);
                    free_it->end_address = next_it->end_address;
                    free_list.erase(next_it);  // Remove the next chunk after merging
                }
            }

            // Merge with previous chunk if within alignment tolerance
            if (free_it != free_list.begin()) {
                auto prev_it = std::prev(free_it);
                uintptr_t prev_end_address = reinterpret_cast<uintptr_t>(prev_it->end_address);
                uintptr_t current_start_address = reinterpret_cast<uintptr_t>(free_it->start_address);
                if ((current_start_address - prev_end_address) <= ALIGNMENT_TOLERANCE) {
                    prev_it->size += free_it->size + (current_start_address - prev_end_address);
                    prev_it->end_address = free_it->end_address;
                    free_list.erase(free_it);  // Remove the current chunk after merging
                }
            }

            std::cout << "Successfully deallocated memory at address: " << address << std::endl;
            return;  // Exit the function after deallocating
        }
    }

    // If the address is not found, print an error message
    std::cerr << "Error: Unable to deallocate memory at address " << address << ". Address not found." << std::endl;
}

// Memory management functions using First-Fit strategy (implemented in first_fit.cpp) and Best-Fit strategy (implemented in best_fit.cpp)
