#include "Coin.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

// Default constructor
Coin::Coin() {
    denomination = FIVE_CENTS;
    count = 0;
}

// Copy constructor
Coin::Coin(const Coin& other) {
    denomination = other.denomination;
    count = other.count;
}

// Constructor
Coin::Coin(Denomination denomination, unsigned count) {
    this->denomination = denomination;
    this->count = count;
}

// Constructor
Coin::Coin(int denom, unsigned count) {
    int index = -1;
    for (int i = 0; i < (int)denominationValueMap.size(); i++) {
        if (denominationValueMap[i] == denom) {
            index = i;
        }
    }
    if (index != -1) {
        this->denomination = static_cast<Denomination>(index);
    } else {
        // Handle invalid denomination value
        // You can throw an exception or set a default denomination
        // For example:
        // this->denomination = FIVE_CENTS;
    }
    this->count = count;
}

// Destructor
Coin::~Coin() {
    // No explicit cleanup needed
}

// Initialize the static member outside the class definition
vector<int> Coin::denominationValueMap = {0,   5,   10,   20,   50,  100,
                                          200, 500, 1000, 2000, 5000};

// Get the value of the coins in string such as "30.00"
// Used instead of float for precision (avoids float rounding errors by storing
// in cents and dividing by 100 for dollars)
string Coin::getStringValue() {
    int value = getCentsValue();
    return std::to_string(value * count / 100) + "." +
           std::to_string(value * count % 100);
}

// Get the value of the coins in cents
int Coin::getCentsValue() {
    int value = denominationValueMap[denomination];
    return value * count;
}

// Get the denomination value
int Coin::getDenominationValue() { return denominationValueMap[denomination]; }

// Get denomination of the coin
Denomination Coin::getDenomination() { return denomination; }

// Get the denomination of the coin in string format
string Coin::getDenominationString() {
    string denominationString;
    if (denomination == FIVE_CENTS) {
        denominationString = "5c";
    } else if (denomination == TEN_CENTS) {
        denominationString = "10c";
    } else if (denomination == TWENTY_CENTS) {
        denominationString = "20c";
    } else if (denomination == FIFTY_CENTS) {
        denominationString = "50c";
    } else if (denomination == ONE_DOLLAR) {
        denominationString = "$1";
    } else if (denomination == TWO_DOLLARS) {
        denominationString = "$2";
    } else if (denomination == FIVE_DOLLARS) {
        denominationString = "$5";
    } else if (denomination == TEN_DOLLARS) {
        denominationString = "1$0";
    } else if (denomination == TWENTY_DOLLARS) {
        denominationString = "$20";
    }
    return denominationString;
}

// Add coins to the current coin
void Coin::addCoins(unsigned count) { this->count += count; }

// Subtract coins from the current coin
bool Coin::subtractCoins(unsigned count) {
    bool success = false;
    if (this->count >= count) {
        this->count -= count;
        success = true;
    }
    return success;
}

// Get quantity of the coin
unsigned Coin::getQuantity() { return count; }

// Return if the denomination value is valid (e.g. 10 is valid as a 10 cent
// coin exists but 3 is not valid as a 3 cent coin does not exist)
bool Coin::isValidDenomination(int value) {
    bool valid = false;
    for (const auto& val : denominationValueMap) {
        if (val == value) {
            valid = true;
        }
    }
    return valid;
}
// Static method for getting the denomination string based on the value
string Coin::getDenominationString(int value) {
    string denominationString;
    if (value == 5) {
        denominationString = "5c";
    } else if (value == 10) {
        denominationString = "10c";
    } else if (value == 20) {
        denominationString = "20c";
    } else if (value == 50) {
        denominationString = "50c";
    } else if (value == 100) {
        denominationString = "$1";
    } else if (value == 200) {
        denominationString = "$2";
    } else if (value == 500) {
        denominationString = "$5";
    } else if (value == 1000) {
        denominationString = "$10";
    } else if (value == 2000) {
        denominationString = "$20";
    }
    return denominationString;
}

// Overloaded equality operators
bool Coin::operator==(const Coin& other) {
    return this->denomination == other.denomination &&
           this->count == other.count;
}

bool Coin::operator!=(const Coin& other) { return !(*this == other); }
