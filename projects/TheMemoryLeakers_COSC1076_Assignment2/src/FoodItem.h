
#ifndef FOOD_ITEM_H
#define FOOD_ITEM_H
#include <string>
#include <vector>
class FoodItem {
   public:
    /**
     * @brief Represents a food item.
     *
     * This class stores information about a food item, including its ID, name,
     * description, and price.
     */

    std::string id;                    /**< The ID of the food item. */
    std::string name;                  /**< The name of the food item. */
    std::string description;           /**< The description of the food item. */
    float price;                       /**< The price of the food item. */
    std::vector<std::string> options;  // Vector to hold different options

    /**
     * @brief Constructs a FoodItem object with the given parameters.
     *
     * @param id The ID of the food item.
     * @param name The name of the food item.
     * @param description The description of the food item.
     * @param price The price of the food item.
     */
    FoodItem(std::string id, const std::string& name,
             const std::string& description,
             float price);  // Constructor declaration

    /**
     * @brief Destroys the FoodItem object.
     *
     * This is the destructor for the FoodItem class.
     */
    ~FoodItem();  // Destructor declaration

    /**
     * @brief Default constructor for the FoodItem class.
     *
     * Initializes the ID, name, description, and price of the food item to
     * empty values or zero.
     */
    FoodItem() : id(""), name(""), description(""), price(0.0) {}

    /**
     * @brief Gets the ID of the food item.
     *
     * @return The ID of the food item.
     */
    std::string getId() const;

    /**
     * @brief Gets the name of the food item.
     *
     * @return The name of the food item.
     */
    std::string getName() const;

    /**
     * @brief Gets the description of the food item.
     *
     * @return The description of the food item.
     */
    std::string getDescription() const;

    /**
     * @brief Gets the price of the food item.
     *
     * @return The price of the food item.
     */
    float getPrice() const;

    /**
     * @brief Checks if two FoodItem objects are equal.
     *
     * @param other The other FoodItem object to compare.
     * @return True if the two FoodItem objects are equal, false otherwise.
     */
    bool operator==(const FoodItem& other) const;
    void addOption(
        const std::string& option);  // Function to add an option to the vector
};

#endif  // FOOD_ITEM_H