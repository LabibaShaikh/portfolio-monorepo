#include "IdManager.h"

#include <fstream>
#include <iostream>
#include <string>

/**
 * @brief Loads the next available ID from the food data file.
 *
 * This function reads the food data file and finds the highest ID present.
 * It then returns the next available ID by incrementing the highest ID by 1.
 * If the file doesn't exist, it starts the IDs from 1.
 *
 * @return The next available ID.
 */
int loadNextId() {
    std::ifstream file("data/foods.dat");
    std::string line;
    int highestId = 0;  // Start with ID 0 as IDs start at F0001

    if (!file) {
        std::cerr << "No existing food data file found, starting IDs at F0001."
                  << std::endl;
        highestId = 0;  // Start IDs from 1 if file doesn't exist
    } else {
        // Read each line from the file and parse the ID
        while (getline(file, line)) {
            std::size_t pos =
                line.find('|');  // Find the position of the first delimiter
            if (pos != std::string::npos) {
                std::string idPart = line.substr(
                    1, pos - 1);  // Extract the ID part, skipping 'F'
                int id = std::stoi(idPart);  // Convert to integer
                if (id > highestId) {
                    highestId = id;
                }
            }
        }
        file.close();
    }

    return highestId + 1;  // Return the next ID (1 if no IDs are present)
}

/**
 * @brief Saves the next available ID to the food data file.
 *
 * This function saves the next available ID to the food data file.
 * If the file doesn't exist, it displays an error message.
 *
 * @param id The next available ID to be saved.
 */
void saveNextId(int id) {
    std::ofstream file("data/foods.dat");
    if (!file) {
        std::cerr << "Failed to save next ID" << std::endl;
    } else {
        file << id;
        file.close();
    }
}
