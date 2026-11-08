#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include <cstddef> // for std::size_t
#include <list>

// Struct to represent an allocated memory chunk
/**
 * @struct Allocation
 * @brief Represents a memory allocation with its size and address range.
 *
 * This structure is used to keep track of a memory allocation, including its
 * size and the start and end addresses of the allocated memory block.
 *
 * @var std::size_t Allocation::size
 * The size of the allocated memory block in bytes.
 *
 * @var void* Allocation::start_address
 * The starting address of the allocated memory block.
 *
 * @var void* Allocation::end_address
 * The ending address of the allocated memory block.
 */
struct Allocation {
    std::size_t size;
    void* start_address;
    void* end_address;
};

// Global lists to manage memory chunks
extern std::list<Allocation> allocated_list;
extern std::list<Allocation> free_list;

// Function declarations
void initialize_memory(std::size_t total_memory);
void* first_fit_alloc(std::size_t size);
void* best_fit_alloc(std::size_t size);
void dealloc(void* address);
void print_memory_status();
std::size_t get_fixed_size(std::size_t requested_size);

#endif
