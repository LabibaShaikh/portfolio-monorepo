#ifndef CASH_REGISTER_H
#define CASH_REGISTER_H

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Coin.h"
#include "FileManager.h"
#include "Helper.h"

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::string;
using std::vector;

#define BALANCE_DELIMITER "|"
#define CURRENCY "$"
#define LINE_CHAR '-'
#define HEADER_LINE_COUNT 28
#define ID_PAD_LENGTH 7
#define PRICE_PAD_LENGTH 10
#define NAME_PAD_LENGTH \
    (HEADER_LINE_COUNT - ID_PAD_LENGTH - PRICE_PAD_LENGTH - 2)
#define HEADER_TITLE "Balance Summary"
#define HEADER_UNDERLINE_COUNT 12
#define HEADER_COLUMNS                                                   \
    ("Denom" + string(ID_PAD_LENGTH - 5, ' ') + BALANCE_DELIMITER +      \
     "Quantity" + string(NAME_PAD_LENGTH - 8, ' ') + BALANCE_DELIMITER + \
     "Value")

class CashRegister {
   public:
    /**
     * @brief Constructs a CashRegister object.
     */
    CashRegister();  // Constructor

    /**
     * @brief Handles the payment for a given total cost.
     * @param totalCost The total cost of the items being purchased.
     */
    bool handlePayment(float totalCost, const FoodItem& item);

    /**
     * @brief Initializes the CashRegister with coin data from a file.
     * @param filename The name of the file containing the coin data.
     */
    void initialize(const std::string& filename);

    /**
     * @brief Saves the current coin data to a file.
     */
    void saveCoins();

    /**
     * @brief Adds coins of a specific denomination and count to the
     * CashRegister.
     * @param denominationValue The value of the coin denomination.
     * @param count The number of coins to add.
     */
    void addCoin(int denominationValue, int count);

    /**
     * @brief Adds a Coin object to the CashRegister.
     * @param coin The Coin object to add.
     */
    void addCoin(Coin& coin);

    /**
     * @brief Removes coins of a specific denomination and count from the
     * CashRegister.
     * @param denominationValue The value of the coin denomination.
     * @param count The number of coins to remove.
     */
    bool removeCoin(int denominationValue, int count);

    /**
     * @brief Displays the currency balance of the CashRegister.
     */
    void displayBalance();  // Displays the currency balance

    bool giveChange(float changeAmount);

   private:
    std::string filename;  // The name of the file containing the coin data

    std::vector<Coin> coins;  // The vector of Coin objects representing the
                              // coins in the CashRegister
};

#endif  // CASH_REGISTER_H
