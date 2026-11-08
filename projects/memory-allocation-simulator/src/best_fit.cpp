#include "memory_manager.h"
#include <iostream>
#include <list>
#include <unistd.h> // for sbrk()

extern std::list<Allocation> allocated_list; // List of allocated memory chunks
extern std::list<Allocation> free_list; // List of free memory chunks

/**
 * @brief Allocates memory using the best-fit strategy.
 *
 * This function attempts to allocate a chunk of memory of the specified size
 * using the best-fit strategy from a free list of memory chunks. If no suitable
 * chunk is found, it dynamically expands the memory and retries the allocation.
 *
 * @param chunk_size The size of the memory chunk to allocate.
 * @return A pointer to the allocated memory chunk, or nullptr if allocation fails.
 *
 * @pre The free_list must be initialized and may contain free memory chunks.
 * @post If a suitable chunk is found, it is allocated and removed from the free list.
 *       If no suitable chunk is found, the memory is expanded, and the allocation is retried.
 *       The allocated_list is updated with the new allocation.
 */
void* best_fit_alloc(std::size_t chunk_size) {
    chunk_size = get_fixed_size(chunk_size);  // Use the fixed partition size

    if (chunk_size == 0) {
        return nullptr; // Invalid size
    }

    auto best_fit_it = free_list.end(); // Iterator for the best-fitting chunk
    std::size_t smallest_diff = SIZE_MAX; // Smallest difference between chunk sizes

    // Find the best-fitting chunk
    for (auto it = free_list.begin(); it != free_list.end(); ++it) {
        if (it->size >= chunk_size) { // Check if the chunk is large enough
            std::size_t diff = it->size - chunk_size; // Calculate the difference
            if (diff < smallest_diff) { // Check if this is the smallest difference
                smallest_diff = diff; // Update the smallest difference
                best_fit_it = it; // Update the best-fitting chunk iterator
            }
        }
    }

    // Allocate the best-fitting chunk if found
    if (best_fit_it != free_list.end()) {
        Allocation allocated_chunk; // Create a new allocation
        allocated_chunk.size = chunk_size; // Set the size of the allocation
        allocated_chunk.start_address = best_fit_it->start_address; // Set the start address
        allocated_chunk.end_address = static_cast<char*>(allocated_chunk.start_address) + chunk_size; // Set the end address
        allocated_list.push_back(allocated_chunk); // Add the allocation to the allocated list

        // Update the free chunk
        best_fit_it->start_address = allocated_chunk.end_address; // Update the start address of the free chunk
        best_fit_it->size -= chunk_size; // Decrease the size of the free chunk

        // Remove the chunk if its size reaches zero
        if (best_fit_it->size == 0) {
            free_list.erase(best_fit_it); // Remove the chunk from the free list
        }

        return allocated_chunk.start_address; // Return the start address of the allocated chunk
    }

    // No suitable chunk found, dynamically expand memory
    std::cout << "Warning: Expanding memory by " << chunk_size << " bytes." << std::endl;
    void* new_memory = sbrk(chunk_size); // Request more memory from the system
    if (new_memory == (void*)-1) {
        std::cerr << "Error: Failed to allocate memory from the system." << std::endl;
        return nullptr; // Return nullptr if memory allocation fails
    }

    // Add new memory to the free list
    Allocation new_free_chunk; // Create a new free chunk
    new_free_chunk.size = chunk_size; // Set the size of the new free chunk
    new_free_chunk.start_address = new_memory; // Set the start address of the new free chunk
    new_free_chunk.end_address = static_cast<char*>(new_memory) + chunk_size; // Set the end address of the new free chunk
    free_list.push_back(new_free_chunk); // Add the new free chunk to the free list

    // Recursively attempt the allocation again
    return best_fit_alloc(chunk_size); // Retry the allocation
}
