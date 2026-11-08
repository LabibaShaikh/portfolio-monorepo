#ifndef COIN_H
#define COIN_H

#include <string>
#include <unordered_map>
#include <vector>

using std::string;
using std::vector;

// Coin.h defines the coin structure for managing currency in the system.
#define DELIM ","  // delimiter

// enumeration representing the various types of currency available in the
// system.
enum Denomination {
    FIVE_CENTS,
    TEN_CENTS,
    TWENTY_CENTS,
    FIFTY_CENTS,
    ONE_DOLLAR,
    TWO_DOLLARS,
    FIVE_DOLLARS,
    TEN_DOLLARS,
    TWENTY_DOLLARS
};

// represents a coin type stored in the cash register perhaps. Each demonination
// will have exactly one of these in the cash register.
/**
 * @class Coin
 * @brief Represents a coin with a denomination and count.
 */
class Coin {
   public:
    static vector<int> denominationValueMap;

    /**
     * @brief Default constructor for Coin.
     */
    Coin();

    /**
     * @brief Copy constructor for Coin.
     * @param other The Coin object to be copied.
     */
    Coin(const Coin& other);

    Coin(int denom, unsigned count);

    /**
     * @brief Constructor for Coin.
     * @param denomination The denomination of the coin.
     * @param coinCount The count of the coin.
     */
    Coin(Denomination denomination, unsigned coinCount);

    /**
     * @brief Destructor for Coin.
     */
    ~Coin();

    /**
     * @brief Get the string value of the coin.
     * @return The string value of the coin.
     */
    std::string getStringValue();

    /**
     * @brief Get the cents value of the coin.
     * @return The cents value of the coin.
     */
    int getCentsValue();

    /**
     * @brief Get the string representation of the coin's denomination.
     * @return The string representation of the coin's denomination.
     */
    std::string getDenominationString();

    /**
     * @brief Get the integer value of the coin's denomination.
     * @return The integer value of the coin's denomination.
     */
    int getDenominationValue();

    /**
     * Retrieves the denomination of the coin.
     *
     * @return The denomination of the coin.
     */
    Denomination getDenomination();

    /**
     * @brief Add coins to the current count.
     * @param count The number of coins to add.
     */
    void addCoins(unsigned count);

    /**
     * @brief Subtract coins from the current count.
     * @param count The number of coins to subtract.
     * @return True if the operation was successful, false otherwise.
     */
    bool subtractCoins(unsigned count);

    /**
     * @brief Check if a given value is a valid denomination value.
     * @param value The value to check.
     * @return True if the value is valid, false otherwise.
     */
    static bool isValidDenomination(int value);

    static string getDenominationString(int value);

    /**
     * @brief Get the quantity of the coin.
     * @return The quantity of the coin.
     */
    unsigned getQuantity();

    /**
     * @brief Overloaded equality operator for comparing two coins.
     * @param other The other Coin object to compare with.
     * @return True if the coins are equal, false otherwise.
     */
    bool operator==(const Coin& other);

    /**
     * @brief Overloaded inequality operator for comparing two coins.
     * @param other The other Coin object to compare with.
     * @return True if the coins are not equal, false otherwise.
     */
    bool operator!=(const Coin& other);

    /**
     * @brief The denomination type of the coin.
     */
    Denomination denomination;

    /**
     * @brief The count of how many of these coins are in the cash register.
     */
    unsigned count;
};

#endif  // COIN_H
