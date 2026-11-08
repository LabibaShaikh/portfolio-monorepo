#include "LinkedList.h"

#include <algorithm>
#include <iomanip>
#include <iostream>

#define DELIMITER "|"
#define CURRENCY "$"
#define LINE_CHAR '-'
#define HEADER_LINE_COUNT 49
#define ID_PAD_LENGTH 6
#define PRICE_PAD_LENGTH 9
#define NAME_PAD_LENGTH \
    (HEADER_LINE_COUNT - ID_PAD_LENGTH - PRICE_PAD_LENGTH - 2)
#define HEADER_TITLE "Food Menu\n"
#define HEADER_UNDERLINE_COUNT 9
#define HEADER_COLUMNS                                            \
    ("ID" + string(ID_PAD_LENGTH - 2, ' ') + DELIMITER + "Name" + \
     string(NAME_PAD_LENGTH - 4, ' ') + DELIMITER + "Price\n")

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::stoi;
using std::string;
using std::to_string;
using std::vector;

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
    head = nullptr;
}

// Ensure ID is loaded
void LinkedList::addFoodItem(const FoodItem& item) {
    ensureIdLoaded();  // Load ID if not already loaded
    Node* newNode = new Node(new FoodItem(item));
    newNode->next =
        nullptr;  // New node will be the last node, so next is nullptr

    if (head == nullptr) {
        head = newNode;  // If the list is empty, new node becomes the head
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;  // Traverse to the end of the list
        }
        current->next = newNode;  // Append new node at the end
        newNode->prev = current;  // Set the previous pointer
    }
}

// Remove food item from the linked list
bool LinkedList::removeFoodItem(const string& id, FoodItem& removedItem) {
    ensureIdLoaded();  // Ensure ID is loaded
    Node* current = head;
    Node* toDelete = nullptr;  // To hold the node to be deleted

    bool removed = false;

    while (current != nullptr) {
        if (current->data->getId() == id) {
            removedItem = *(current->data);  // Copy the food item data before
                                             // deleting the node.

            if (current == head) {     // If the node to be removed is the head
                head = current->next;  // Move head to next node
                if (head) {            // Check if the new head exists
                    head->prev = nullptr;  // New head has no previous
                }
                toDelete = current;  // Set the node to be deleted
                removed = true;      // Mark as removed
                break;               // Exit the loop
            } else {                 // For middle or last node
                current->prev->next =
                    current->next;    // Link previous node to next node
                if (current->next) {  // If there is a next node
                    current->next->prev =
                        current
                            ->prev;  // Set its previous to current's previous
                }
                toDelete = current;  // Set the node to be deleted
                removed = true;      // Mark as removed
                break;               // Exit the loop
            }
        }
        current = current->next;
    }

    if (toDelete) {
        delete toDelete;  // Delete the node outside the traversal loop
    }
    return removed;  // Return false if the item was not found.
}

// Display all food items in the linked list in a tabular format
/**
 * Displays the food items in the linked list.
 * If the linked list is empty, it prints "No items to display."
 * Otherwise, it iterates over each node in the linked list and prints the
 * details of each food item. The details include the item's ID, name, price,
 * and currency.
 */
void LinkedList::displayFoodItems() const {
    if (head == nullptr) {
        cout << "No items to display." << endl;
        return;
    }
    Node* current = head;

    // Print table headers
    cout << HEADER_TITLE;
    cout << string(HEADER_UNDERLINE_COUNT, LINE_CHAR) << endl;
    cout << HEADER_COLUMNS;
    cout << string(HEADER_LINE_COUNT, LINE_CHAR) << endl;
    // Iterate over each node and print details
    while (current != nullptr) {
        FoodItem* item = current->data;
        cout << left << setw(ID_PAD_LENGTH) << item->getId() << DELIMITER
             << setw(NAME_PAD_LENGTH) << item->getName() << DELIMITER
             << CURRENCY << fixed << setprecision(2) << setw(PRICE_PAD_LENGTH)
             << item->getPrice() << endl;

        // Display options
        for (const auto& option : item->options) {
            cout << "  - Option: " << option << endl;
        }
        current = current->next;
    }
}

string LinkedList::generateNextId() {
    if (head == nullptr) {
        return "F0001";  // Start with F0001 if the list is empty.
    }

    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    string lastId = current->data->getId();
    int currentId =
        stoi(lastId.substr(1)) + 1;  // Increment the numeric part by 1.
    return "F" + to_string(currentId);
}

string LinkedList::generateFormattedNextId() {
    // Generate the next ID and calculate the number of leading zeros required.
    string nextId = generateNextId();
    int idLength = nextId.length() - 1;  // Exclude the 'F' prefix.
    int requiredZeros = 4 - idLength;
    return nextId.substr(0, 1) + string(requiredZeros, '0') +
           nextId.substr(1);  // Add leading zeros.
}

vector<FoodItem> LinkedList::getAllItems() const {
    // Create a vector to store all food items
    // if the list is empty, return an empty vector
    vector<FoodItem> items;
    Node* current = head;
    while (current != nullptr) {
        items.push_back(*(current->data));  //  data is a pointer to FoodItem
        current = current->next;
    }
    return items;
}

FoodItem* LinkedList::getItemById(const string& id) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data->getId() == id) {
            return current->data;
        }
        current = current->next;
    }
    return nullptr;
}

bool LinkedList::isInList(const string& id) const {
    Node* current = head;
    while (current != nullptr) {
        if (current->data->getId() == id) {
            return true;
        }
        current = current->next;
    }
    return false;
}