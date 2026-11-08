#include "CashRegister.h"

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "Coin.h"
#include "FileManager.h"
#include "FoodItem.h"
#include "Helper.h"

using std::cout;
using std::endl;
using std::fixed;
using std::left;
using std::setprecision;
using std::setw;
using std::string;
using std::vector;
// Define ANSI color codes
#define ANSI_COLOR_RED "\x1b[31m"
#define ANSI_COLOR_GREEN "\x1b[32m"
#define ANSI_COLOR_YELLOW "\x1b[33m"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN "\x1b[36m"
#define ANSI_COLOR_RESET "\x1b[0m"

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

CashRegister::CashRegister() { coins = {}; }

void CashRegister::initialize(const std::string& filename) {
    this->filename = filename;

    try {
        coins = FileManager::loadCoins(filename);
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to load items: " << e.what() << std::endl;
    }
}

void CashRegister::saveCoins() {
    try {
        FileManager::saveCoins(filename, coins);
    } catch (const std::runtime_error& e) {
        std::cerr << "Failed to save items: " << e.what() << std::endl;
    }
}

void CashRegister::addCoin(int denominationValue, int count) {
    bool coinAdded = false;
    if (Coin::isValidDenomination(denominationValue)) {
        for (auto& coin : coins) {
            if (coin.getDenominationValue() == denominationValue &&
                !coinAdded) {
                coin.addCoins(count);
                coinAdded = true;
            }
        }
        // If coin denomination does not exist, add a new coin
        Coin newCoin(denominationValue, count);
        coins.push_back(newCoin);
    } else {
        cout << ANSI_COLOR_RED << "Invalid coin denomination!"
             << ANSI_COLOR_RESET << endl;
    }
}

// Remove coins from the cash register targeting a specific coin denomination
// using the bool output of the Coin::subtractCoins method.
// using the bool output of the Coin::subtractCoins method.
bool CashRegister::removeCoin(int denominationValue, int count) {
    bool coinRemoved = false;

    if (Coin::isValidDenomination(denominationValue)) {
        for (auto& coin : coins) {
            if (coin.getDenominationValue() == denominationValue) {
                if (!coin.subtractCoins(count)) {
                    cout << "Not enough coins to remove!" << endl;
                } else {
                    coinRemoved = true;  // Coin found and removed
                }
                break;  // Coin denomination processed, break out of the loop
            }
        }

        if (!coinRemoved) {
            cout << "Coin denomination not found!" << endl;
        }
    } else {
        cout << "Invalid coin denomination!" << endl;
    }
    return coinRemoved;
}

// Display currency balance of the cash register. The function iterates through
// the coins vector and prints the denomination value, quantity, and value of
// each coin.

void CashRegister::displayBalance() {
    cout << HEADER_TITLE << endl;
    cout << string(HEADER_UNDERLINE_COUNT, LINE_CHAR) << endl;
    cout << HEADER_COLUMNS << endl;
    cout << string(HEADER_LINE_COUNT, LINE_CHAR) << endl;

    for (auto& coin : coins) {
        cout << left << setw(ID_PAD_LENGTH) << coin.getDenominationValue()
             << BALANCE_DELIMITER << setw(NAME_PAD_LENGTH) << coin.getQuantity()
             << BALANCE_DELIMITER << CURRENCY << fixed << setprecision(2)
             << setw(PRICE_PAD_LENGTH) << coin.getStringValue() << endl;
    }
}

bool CashRegister::handlePayment(float totalCost, const FoodItem& item) {
    cout << "You are purchasing: " << item.getName() << " - "
         << item.getDescription() << endl;
    cout << "Total cost is: " << ANSI_COLOR_GREEN << "$" << std::fixed
         << std::setprecision(2) << totalCost << ANSI_COLOR_RESET << endl;

    Helper::InputFlags inputFlags = {false, true, false};
    int inputDenomination = 0;
    float remainingCost = totalCost;
    float totalGiven = 0;
    bool purchaseSuccessful = false;
    std::vector<int> givenCoins;  // To store the given coins

    while (!inputFlags.isEOF && remainingCost > 0.0f && !inputFlags.isCancel) {
        inputDenomination = 0;
        cout << "You still owe " << ANSI_COLOR_RED << "$" << std::fixed
             << std::setprecision(2) << remainingCost << ANSI_COLOR_RESET
             << ": ";
        string prompt =
            "Please enter the denomination and count of the coin you want to "
            "give: ";
        inputFlags = Helper::getValidUserInput(prompt, inputDenomination);

        if (inputFlags.isCancel) {
            cout << "Operation cancelled. Returning to main menu." << endl;
            // Handle refund of the given coins
            cout << "Refunding given coins:" << endl;
            for (const int& coin : givenCoins) {
                cout << "Refunded coin: " << coin << " cents" << endl;
            }
            remainingCost = totalCost;  // Ensure the loop exits
        }

        if (!inputFlags.isInvalid && !inputFlags.isEOF &&
            !inputFlags.isCancel) {
            // Accept coins
            if (Coin::isValidDenomination(inputDenomination)) {
                // Store the given coin
                givenCoins.push_back(inputDenomination);
                // Update the coin count in the cash register
                addCoin(inputDenomination, 1);
                totalGiven += (inputDenomination) / 100.0f;
                remainingCost = totalCost - totalGiven;
            } else {
                cout << "Invalid coin denomination!" << endl;
            }
        }
    }

    if (remainingCost <= 0 && !inputFlags.isCancel) {
        cout << "Processing Payment..." << endl;
        if (remainingCost < 0) {
            // If able to give correct change
            if (!giveChange(-remainingCost)) {
                // If change cannot be given, revert the added coins
                for (const int& coin : givenCoins) {
                    removeCoin(coin, 1);
                }
                cout << "Transaction cancelled and coins refunded." << endl;
                purchaseSuccessful = false;
            } else {
                // If change can be given, complete the transaction
                purchaseSuccessful = true;
                cout << "Payment successful!" << endl;
            }
        } else {
            // If exact change is given
            purchaseSuccessful = true;
            cout << "Payment successful!" << endl;
        }
    } else if (inputFlags.isCancel) {
        cout << "Payment cancelled. Returning to main menu." << endl;
    } else {
        cout << "Not enough money given!" << endl;
    }

    return purchaseSuccessful;
}

bool CashRegister::giveChange(float changeAmount) {
    std::vector<Coin> changeCoins;
    bool changeGiven = false;

    if (changeAmount > 0) {
        vector<unsigned int> changeDenoms;

        // Convert changeAmount to cents
        unsigned int changeAmountCents =
            static_cast<unsigned int>(std::round(changeAmount * 100.0f));

        // Iterate through coin values from highest to lowest
        for (int i = Coin::denominationValueMap.size() - 1; i > 0; --i) {
            unsigned int denom = Coin::denominationValueMap[i];
            while (denom <= changeAmountCents) {
                changeDenoms.push_back(denom);
                changeAmountCents -= denom;

                // Attempt to remove the coin and check if successful
                if (!removeCoin(denom, 1)) {
                    cout << "Coin denomination not found!" << endl;
                    return false;  // If any denomination is not found, exit and
                                   // indicate failure
                }
            }
        }

        if (!changeDenoms.empty()) {
            cout << "Change Given: ";
            for (auto& denom : changeDenoms) {
                cout << Coin::getDenominationString(static_cast<int>(denom));
                cout << " ";
            }
            cout << endl;
            changeGiven = true;
        } else {
            cout << "Unable to find correct change!" << endl;
        }
    } else {
        cout << "Insufficient amount paid!" << endl;
    }

    return changeGiven;
}
