#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <string>
#include <vector>

#include "Coin.h"
#include "FoodItem.h"
#define DELIMITER '|'
/**
 * @brief The FileManager class provides static methods for loading and saving
 * data to files.
 */
class FileManager {
   public:
    /**
     * @brief Loads a vector of FoodItem objects from a file.
     *
     * @param filename The name of the file to load from.
     * @return A vector of FoodItem objects loaded from the file.
     */
    static std::vector<FoodItem> loadFoodItems(const std::string& filename);

    /**
     * @brief Saves a vector of FoodItem objects to a file.
     *
     * @param filename The name of the file to save to.
     * @param items The vector of FoodItem objects to save.
     */
    static void saveFoodItems(const std::string& filename,
                              const std::vector<FoodItem>& items);

    /**
     * @brief Loads a vector of Coin objects from a file.
     *
     * @param filename The name of the file to load from.
     * @return A vector of Coin objects loaded from the file.
     */
    static std::vector<Coin> loadCoins(const std::string& filename);

    /**
     * @brief Saves a vector of Coin objects to a file.
     *
     * @param filename The name of the file to save to.
     * @param coins The vector of Coin objects to save.
     */
    static void saveCoins(const std::string& filename,
                          std::vector<Coin>& coins);
};

#endif  // FILE_MANAGER_H
