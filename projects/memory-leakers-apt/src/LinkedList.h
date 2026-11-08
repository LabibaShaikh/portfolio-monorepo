#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <vector>

#include "IdManager.h"
#include "Node.h"

/**
 * @class LinkedList
 * @brief A class representing a linked list of FoodItems.
 *
 * The LinkedList class provides functionality to store and manage a collection
 * of FoodItems. It supports operations such as adding, removing, and displaying
 * food items. It also provides methods to generate unique IDs for food items.
 */
/**
 * @class LinkedList
 * @brief A class representing a linked list of FoodItems.
 *
 * The LinkedList class provides functionality to add, remove, and display
 * FoodItems in a linked list. It also provides methods to generate unique IDs
 * for each FoodItem.
 */
class LinkedList {
   public:
    /**
     * @brief Constructs an empty LinkedList object.
     */
    LinkedList() : head(nullptr), nextId(1), idLoaded(false) {}

    /**
     * @brief Ensures that the next ID is loaded from storage.
     *
     * If the ID has not been loaded yet, this method loads the next ID from
     * storage.
     */
    void ensureIdLoaded() {
        if (!idLoaded) {
            nextId = loadNextId();
            idLoaded = true;
        }
    }

    /**
     * @brief Destroys the LinkedList object and frees the memory.
     */
    ~LinkedList();

    /**
     * @brief Adds a FoodItem to the linked list.
     *
     * @param item The FoodItem to be added.
     */
    void addFoodItem(const FoodItem& item);

    /**
     * @brief Removes a FoodItem from the linked list.
     *
     * @param id The ID of the FoodItem to be removed.
     * @param removedItem A reference to store the removed FoodItem.
     * @return True if the FoodItem was successfully removed, false otherwise.
     */
    bool removeFoodItem(const std::string& id, FoodItem& removedItem);

    /**
     * @brief Clears the linked list, removing all FoodItems.
     */
    void clear();

    /**
     * @brief Displays all FoodItems in the linked list.
     */
    void displayFoodItems() const;

    /**
     * @brief Generates the next unique ID for a FoodItem.
     *
     * @return The generated ID.
     */
    std::string generateNextId();

    /**
     * @brief Generates the next formatted unique ID for a FoodItem.
     *
     * @return The generated formatted ID.
     */
    std::string generateFormattedNextId();

    /**
     * @brief Retrieves all FoodItems in the linked list.
     *
     * @return A vector containing all FoodItems.
     */
    std::vector<FoodItem> getAllItems() const;

    /**
     * @brief Retrieves a FoodItem from the linked list by ID.
     *
     * @param id The ID of the FoodItem to retrieve.
     * @return A pointer to the FoodItem if found, nullptr otherwise.
     */
    FoodItem* getItemById(const std::string& id) const;

    /**
     * @brief Is in list?
     *
     * @return Bool if in list
     */
    bool isInList(const std::string& id) const;

   private:
    Node* head;     // Pointer to the head of the linked list
    int nextId;     // Next ID to be used for the next food item
    bool idLoaded;  // Flag indicating whether the next ID has been loaded
};

#endif  // LINKEDLIST_H
