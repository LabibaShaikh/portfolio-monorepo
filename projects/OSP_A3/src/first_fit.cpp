#include "memory_manager.h" // Include the memory manager header
#include <iostream>         // Include the iostream library for input/output
#include <list>             // Include the list library for using std::list
#include <unistd.h>         // Include the unistd.h library for sbrk()

/**
 * @brief Allocates a chunk of memory using the first-fit strategy.
 *
 * This function attempts to allocate a chunk of memory of the specified size
 * from a free list of available memory chunks. It uses the first-fit strategy,
 * which means it will allocate the first available chunk that is large enough
 * to satisfy the request. If no suitable chunk is found, the function will
 * dynamically expand the memory and retry the allocation.
 *
 * @param chunk_size The size of the memory chunk to allocate.
 * @return A pointer to the start of the allocated memory chunk, or nullptr if
 *         the allocation fails.
 *
 * Precondition: chunk_size must be a positive integer.
 * Postcondition: Returns a pointer to the allocated memory chunk or nullptr if allocation fails.
 */
void* first_fit_alloc(std::size_t chunk_size) {
    chunk_size = get_fixed_size(chunk_size);  // Use the fixed partition size

    if (chunk_size == 0) { // Check if the chunk size is valid
        return nullptr; // Invalid size, return nullptr
    }

    // Iterate through the free list to find a suitable chunk
    for (auto it = free_list.begin(); it != free_list.end(); ++it) {
        if (it->size >= chunk_size) { // Check if the current chunk is large enough
            Allocation allocated_chunk; // Create a new allocation
            allocated_chunk.size = chunk_size; // Set the size of the allocated chunk
            allocated_chunk.start_address = it->start_address; // Set the start address of the allocated chunk
            allocated_chunk.end_address = static_cast<char*>(allocated_chunk.start_address) + chunk_size; // Set the end address of the allocated chunk
            allocated_list.push_back(allocated_chunk); // Add the allocated chunk to the allocated list

            it->start_address = allocated_chunk.end_address; // Update the start address of the free chunk
            it->size -= chunk_size; // Reduce the size of the free chunk

            if (it->size == 0) { // If the free chunk is completely used
                free_list.erase(it); // Remove the free chunk from the list
            }

            return allocated_chunk.start_address; // Return the start address of the allocated chunk
        }
    }

    // No suitable chunk found, dynamically expand memory
    std::cout << "Warning: Expanding memory by " << chunk_size << " bytes." << std::endl;
    void* new_memory = sbrk(chunk_size); // Request more memory from the system
    if (new_memory == (void*)-1) { // Check if the memory allocation failed
        std::cerr << "Error: Failed to allocate memory from the system." << std::endl;
        return nullptr; // Return nullptr if allocation failed
    }

    // Add new memory to the free list
    Allocation new_free_chunk; // Create a new free chunk
    new_free_chunk.size = chunk_size; // Set the size of the new free chunk
    new_free_chunk.start_address = new_memory; // Set the start address of the new free chunk
    new_free_chunk.end_address = static_cast<char*>(new_memory) + chunk_size; // Set the end address of the new free chunk
    free_list.push_back(new_free_chunk); // Add the new free chunk to the free list

    // Recursively attempt the allocation again
    return first_fit_alloc(chunk_size); // Retry the allocation
}