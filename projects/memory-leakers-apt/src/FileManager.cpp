#include "FileManager.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

#include "FoodItem.h"

std::vector<FoodItem> FileManager::loadFoodItems(const std::string& filename) {
    std::vector<FoodItem> items;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    // Read each line from the file
    std::string line;
    while (getline(file, line)) {
        std::istringstream ss(line);
        std::string id, name, description, priceStr;
        float price;
        getline(ss, id, DELIMITER);
        getline(ss, name, DELIMITER);
        getline(ss, description, DELIMITER);
        getline(ss, priceStr);
        price = std::stof(priceStr);

        items.emplace_back(id, name, description, price);
    }
    // Close the file
    file.close();
    return items;  // Return the vector of food items
}

void FileManager::saveFoodItems(const std::string& filename,
                                const std::vector<FoodItem>& items) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " +
                                 filename);
    }
    for (const auto& item : items) {
        file << item.getId() << DELIMITER << item.getName() << DELIMITER
             << item.getDescription() << DELIMITER << item.getPrice() << '\n';
    }
    file.close();
}

// Load coins from a file
std::vector<Coin> FileManager::loadCoins(const std::string& filename) {
    std::vector<Coin> coins;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    // Read each line from the file
    std::string line;
    while (getline(file, line)) {
        std::istringstream ss(line);
        int denomination, quantity;

        ss >> denomination;
        if (ss.fail() || ss.peek() != ',') {
            throw std::runtime_error("Malformed coin data: " + line);
        }
        ss.ignore();
        ss >> quantity;
        // Create a Coin object and add it to the vector
        // Create coin
        Coin coin = Coin(denomination, quantity);
        coins.emplace_back(coin);
    }
    file.close();
    return coins;
}

// Save coins to a file
void FileManager::saveCoins(const std::string& filename,
                            std::vector<Coin>& coins) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing: " +
                                 filename);
    }
    for (Coin& coin : coins) {
        file << static_cast<int>(coin.getDenominationValue()) << ","
             << coin.getQuantity() << std::endl;
    }
    file.close();
}