#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include <string>

#include "CashRegister.h"
#include "LinkedList.h"

/**
 * @class VendingMachine
 * @brief Represents a vending machine that manages a collection of items.
 *
 * The VendingMachine class provides functionality to add and remove items from
 * the inventory, display the available items, save the items to a file, and
 * auto-initialize the inventory based on command line arguments.
 */
/**
 * @class VendingMachine
 * @brief Represents a vending machine that holds items and manages
 * transactions.
 *
 * The VendingMachine class provides functionality to add and remove items from
 * the inventory, display the available items, save the inventory to a file,
 * and purchase items. It also supports auto-initialization of the inventory
 * based on command line arguments.
 */
class VendingMachine {
   public:
    CashRegister
        cr; /**< The cash register associated with the vending machine. */
    /**
     * @brief Default constructor for the VendingMachine class.
     *
     * Initializes the inventory with an empty LinkedList.
     */
    VendingMachine() : inventory() {}

    /**
     * @brief Adds an item to the vending machine's inventory.
     *
     * @return true if the item was successfully added, false otherwise.
     */
    bool addItem();

    /**
     * @brief Removes an item from the vending machine's inventory.
     */
    bool removeItem();

    /**
     * @brief Displays the items available in the vending machine's inventory.
     */
    void displayItems();

    /**
     * @brief Saves the items in the vending machine's inventory to a file.
     */
    void saveItems();

    bool purchaseItem();

    /**
     * @brief Auto-initializes the vending machine's inventory based on command
     * line arguments.
     *
     * @param argc The number of command line arguments.
     * @param argv An array of command line argument strings.
     */
    void autoInitialize(int argc, char** argv);

    void intialize(const std::string& foodsFile);

   private:
    LinkedList inventory; /**< The inventory of items in the vending machine. */
};

#endif  // VENDINGMACHINE_H