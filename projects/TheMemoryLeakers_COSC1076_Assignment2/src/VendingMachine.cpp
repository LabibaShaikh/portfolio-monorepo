#include "VendingMachine.h"

#include <iomanip>
#include <iostream>
#include <string>

#include "CashRegister.h"
#include "FileManager.h"
#include "Helper.h"

using std::cout;
using std::endl;
using std::string;

void VendingMachine::autoInitialize(int argc, char** argv) {
    std::string coinsFile = "";
    std::string foodsFile = "";

    // Check if the help argument is provided
    if (argc == 2 &&
        (std::string(argv[1]) == "-help" || std::string(argv[1]) == "-h")) {
        Helper::displayHelp();
        exit(EXIT_SUCCESS);
    } else if (argc >= 3) {
        foodsFile = argv[1];
        coinsFile = argv[2];
    } else {
        std::cerr << "Error: Please provide both coins and foods data files in "
                     "the correct order."
                  << std::endl;
        Helper::displayHelp();
        exit(EXIT_FAILURE);
    }

    // Initialize the VendingMachine with the provided files
    intialize(foodsFile);
    cr.initialize(coinsFile);
}

void VendingMachine::intialize(const std::string& foodsFile) {
    try {
        auto items = FileManager::loadFoodItems(foodsFile);
        for (const auto& item : items) {
            inventory.addFoodItem(item);
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to load items: " << e.what() << std::endl;
    }
}

bool VendingMachine::addItem() {
    string name = "";
    string namePrompt = "Enter Food Name: ";
    string description = "";
    string descriptionPrompt = "Enter Food Description: ";
    float price = 0.0;
    string pricePrompt = "Enter Price: $";
    bool shouldReturnToMenu =
        false;  // To track if we should return to the main menu

    // Use formatted ID generator
    std::string id = inventory.generateFormattedNextId();

    // Get valid user input for name
    Helper::InputFlags inputFlags = Helper::getValidUserInput(namePrompt, name);
    if (inputFlags.isCancel) {
        cout << "Operation cancelled. Returning to main menu." << endl;
        shouldReturnToMenu = true;
    }

    if (!inputFlags.isEOF && !shouldReturnToMenu) {
        // Get valid user input for description
        inputFlags = Helper::getValidUserInput(descriptionPrompt, description);
        if (inputFlags.isCancel) {
            cout << "Operation cancelled. Returning to main menu." << endl;
            shouldReturnToMenu = true;
        }
    }

    if (!inputFlags.isEOF && !shouldReturnToMenu) {
        // Get valid user input for price
        inputFlags = Helper::getValidUserInput(pricePrompt, price);
        if (inputFlags.isCancel) {
            cout << "Operation cancelled. Returning to main menu." << endl;
            shouldReturnToMenu = true;
        }
    }

    if (!inputFlags.isEOF && !shouldReturnToMenu) {
        inventory.addFoodItem(FoodItem(id, name, description, price));
        std::cout << endl;
        std::cout << "Item " << name << " has been added with ID " << id
                  << " and price $" << std::fixed << std::setprecision(2)
                  << price << " with Description: " << description << "."
                  << endl;
    }

    return inputFlags.isEOF || shouldReturnToMenu;
}

/**
 * Removes a food item from the vending machine inventory based on the provided
 * ID. Prompts the user to enter the ID of the food item to be removed. If the
 * item is found and successfully removed, it displays the details of the
 * removed item and saves the updated inventory to a file.
 */
bool VendingMachine::removeItem() {
    string id;
    string idPrompt = "Enter Food ID to Remove: ";
    bool shouldReturnToMenu =
        false;  // To track if we should return to the main menu

    // Get valid user input for name
    Helper::InputFlags inputFlags = Helper::getValidUserInput(idPrompt, id);
    if (inputFlags.isCancel) {
        cout << "Operation cancelled. Returning to main menu." << endl;
        shouldReturnToMenu = true;
    }

    if (!inputFlags.isEOF && !shouldReturnToMenu) {
        // Variable to hold the removed item data.
        FoodItem removedItem;
        if (inventory.removeFoodItem(id, removedItem)) {
            std::cout << "ID: " << removedItem.getId()
                      << ", Name: " << removedItem.getName()
                      << ", Description: " << removedItem.getDescription()
                      << ", Price: $" << std::fixed << std::setprecision(2)
                      << removedItem.getPrice() << " has been removed."
                      << std::endl;
            // Formatting
            cout << endl;
        } else {
            std::cout << "Item with ID " << id << " not found." << std::endl;
            // Formatting
            cout << endl;
        }
    }

    return inputFlags.isEOF || shouldReturnToMenu;
}

/**
 * Displays the food items available in the vending machine.
 */
void VendingMachine::displayItems() { inventory.displayFoodItems(); }

/**
 * Saves the food items in the vending machine to a file.
 * The food items are saved using the FileManager class.
 * If an error occurs during the saving process, an exception is caught
 * and an error message is printed to the standard error stream.
 */
void VendingMachine::saveItems() {
    try {
        FileManager::saveFoodItems("data/foods.dat", inventory.getAllItems());
    } catch (const std::exception& e) {
        std::cerr << "Error saving items: " << e.what() << std::endl;
    }

    // Call cr save coins
    cr.saveCoins();
}

bool VendingMachine::purchaseItem() {
    string id;
    string idPrompt = "Enter Food ID to purchase: ";
    bool paymentSuccess = false;
    bool shouldReturnToMenu =
        false;  // To track if we should return to the main menu

    Helper::InputFlags inputFlags = {
        isEOF : false,
        isInvalid : true,
        isCancel : false
    };

    while (!inventory.isInList(id) && !inputFlags.isEOF &&
           !inputFlags.isCancel) {
        // Get valid user input for name
        inputFlags = Helper::getValidUserInput(idPrompt, id);

        if (inputFlags.isCancel) {
            cout << "Operation cancelled. Returning to main menu." << endl;
            shouldReturnToMenu = true;
        }

        if (!inputFlags.isEOF) {
            // Variable to hold the removed item data.
            FoodItem removedItem;
            if (inventory.isInList(id)) {
                // Get item
                FoodItem item = *inventory.getItemById(id);

                // Get price
                float price = item.getPrice();

                // Handle payment
                paymentSuccess = cr.handlePayment(price, item);

                // Formatting
                cout << endl;
            } else {
                std::cout << "Item with ID " << id << " not found."
                          << std::endl;
                // Formatting
                cout << endl;
            }
        }
    }

    return inputFlags.isEOF || !paymentSuccess || shouldReturnToMenu;
}
