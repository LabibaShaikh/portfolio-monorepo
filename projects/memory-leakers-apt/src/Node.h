#ifndef NODE_H
#define NODE_H

#include "FoodItem.h"

/**
 * @file Node.h
 * @brief Defines the Node class for a linked list.
 */

/**
 * @class Node
 * @brief Represents a node in a linked list.
 *
 * The `Node` class is used to store a food item and a pointer to the next
 * node in the list. Each node contains a pointer to a dynamically allocated
 * `FoodItem` object.
 */
/**
 * @class Node
 * @brief Represents a node in a doubly linked list.
 *
 * The Node class contains a pointer to a FoodItem object, as well as pointers
 * to the next and previous nodes in the list. It is used to construct a doubly
 * linked list.
 */
class Node {
   public:
    FoodItem* data;  // Pointer to the food item data
    Node* next;      // Pointer to the next node in the list
    Node* prev;      // Pointer to the previous node

    /**
     * @brief Constructs a `Node` object with the given `FoodItem` pointer.
     *
     * @param item A pointer to the `FoodItem` object to be stored in the node.
     */
    Node(FoodItem* item) : data(item), next(nullptr), prev(nullptr) {}

    /**
     * @brief Destructor for the `Node` class.
     *
     * The destructor properly deletes the dynamically allocated `FoodItem`
     * object.
     */
    ~Node() {
        delete data;  // Properly delete the dynamically allocated FoodItem
    }
};

#endif  // NODE_H
