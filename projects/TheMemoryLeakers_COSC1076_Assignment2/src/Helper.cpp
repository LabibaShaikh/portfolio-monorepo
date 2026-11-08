#include "Helper.h"

#include <cctype>
#include <iostream>
#include <string>
#include <unordered_map>
using std::cin;
using std::cout;
using std::endl;
using std::exception;
using std::getline;
using std::string;
using std::unordered_map;

// Static member initialization
unordered_map<string, string> Helper::helpMessages;

/**
 * @brief Initialize the help messages for various prompts.
 */
void Helper::initializeHelpMessages() {
    helpMessages["Select your option: "] =
        "\033[1;33mChoose an option from the menu by entering the "
        "corresponding number.\033[0m";
    helpMessages["Enter Food ID to purchase: "] =
        "\033[1;33mEnter the unique ID of the food item you wish to "
        "purchase.\033[0m";
    helpMessages["Enter Food Name: "] =
        "\033[1;33mEnter the name of the new food item.\033[0m";
    helpMessages["Enter Food Description: "] =
        "\033[1;33mProvide a brief description of the food item.\033[0m";
    helpMessages["Enter Price: "] =
        "\033[1;33mEnter the price of the food item in dollars.\033[0m";
    helpMessages["Enter Food ID to Remove: "] =
        "\033[1;33mEnter the unique ID of the food item you wish to remove "
        "starting with an 'F'.\033[0m";

    helpMessages
        ["Please enter the denomination and count of the coin you want to "
         "give: "] =
            "\033[1;33mEnter the denomination and count of the coin in the "
            "format 'denomination count' (e.g., '1.00 2' for two 1-dollar "
            "coins). Valid denominations are 0.05, 0.10, 0.20, 0.50, 1.00, "
            "2.00.\033[0m";
}

/**
 * @brief Print a specific help message based on the provided prompt.
 * @param prompt The prompt message.
 */
void Helper::printSpecificHelp(const string& prompt) {
    if (helpMessages.find(prompt) != helpMessages.end()) {
        cout << helpMessages[prompt] << endl;
    } else {
        cout << "\033[1;33mNo specific help available for this input.\033[0m"
             << endl;
    }
}

Helper::StringInput Helper::getUserStringInput(const string& prompt) {
    cout << addHelpReminder(prompt);
    StringInput inputStruct = {"", false, true, false};
    getline(cin, inputStruct.input);

    if (cin.eof() || cin.bad() || cin.fail()) {
        inputStruct.isEOF = true;
        inputStruct.isInvalid = true;
        cout << endl;
    } else if (inputStruct.input.empty()) {
        inputStruct.isInvalid = false;
        inputStruct.isCancel = true;
    } else if (inputStruct.input == "h" || inputStruct.input == "help") {
        Helper::printSpecificHelp(
            prompt);                   // Use the prompt to get specific help
        inputStruct.isInvalid = true;  // Reprompt after showing help
    } else {
        inputStruct.isInvalid = false;
    }
    cin.clear();
    return inputStruct;
}

// Get user integer input with a prompt
Helper::IntInput Helper::getUserIntInput(const string& prompt) {
    cout << addHelpReminder(prompt);
    return Helper::getUserIntInputImpl(prompt);
}

// Get user float input with a prompt
Helper::FloatInput Helper::getUserFloatInput(const string& prompt) {
    cout << addHelpReminder(prompt);
    return Helper::getUserFloatInputImpl(prompt);
}

// Get user string input without a prompt
Helper::StringInput Helper::getUserStringInputImpl(const string& prompt) {
    StringInput inputStruct = {"", false, true, false};
    while (true) {
        getline(cin, inputStruct.input);

        if (cin.eof() || cin.bad() || cin.fail()) {
            inputStruct.isEOF = true;
            inputStruct.isInvalid = true;
            cout << endl;
            break;
        } else if (inputStruct.input.empty()) {
            inputStruct.isInvalid = false;
            inputStruct.isCancel = true;
            break;
        } else if (inputStruct.input == "h" || inputStruct.input == "help") {
            Helper::printSpecificHelp(prompt);
            cout << addHelpReminder(prompt);
        } else {
            inputStruct.isInvalid = false;
            break;
        }
    }
    cin.clear();
    return inputStruct;
}

// Get user input without a prompt
Helper::IntInput Helper::getUserIntInputImpl(const string& prompt) {
    StringInput inputStringStruct = Helper::getUserStringInputImpl(prompt);
    IntInput inputIntStruct = {-1, inputStringStruct.isEOF,
                               inputStringStruct.isInvalid,
                               inputStringStruct.isCancel};

    if (!inputStringStruct.isInvalid && !inputStringStruct.isEOF &&
        !inputStringStruct.isCancel) {
        try {
            inputIntStruct.input = stoi(inputStringStruct.input);
        } catch (const exception&) {
            inputIntStruct.isInvalid = true;
        }
    }
    return inputIntStruct;
}

// Get user float input without a prompt
Helper::FloatInput Helper::getUserFloatInputImpl(const string& prompt) {
    StringInput inputStringStruct = Helper::getUserStringInputImpl(prompt);
    FloatInput inputFloatStruct = {-1.0, inputStringStruct.isEOF,
                                   inputStringStruct.isInvalid,
                                   inputStringStruct.isCancel};

    if (!inputStringStruct.isInvalid && !inputStringStruct.isEOF &&
        !inputStringStruct.isCancel) {
        try {
            inputFloatStruct.input = stof(inputStringStruct.input);
        } catch (const exception&) {
            inputFloatStruct.isInvalid = true;
        }
    }
    return inputFloatStruct;
}

// Get user string input until valid
Helper::InputFlags Helper::getValidUserInput(const string& prompt,
                                             string& input) {
    StringInput inputStruct = {"", false, true, false};
    while (!inputStruct.isEOF && inputStruct.isInvalid &&
           !inputStruct.isCancel) {
        inputStruct = Helper::getUserStringInput(prompt);
        if (inputStruct.isInvalid && inputStruct.input != "h" &&
            inputStruct.input != "help") {
            cout << "Invalid input. Please enter a valid string." << endl;
        }
    }
    input = inputStruct.input;
    InputFlags inputFlags = {inputStruct.isEOF, inputStruct.isInvalid,
                             inputStruct.isCancel};
    return inputFlags;
}

// Get user integer input until valid
Helper::InputFlags Helper::getValidUserInput(const string& prompt, int& input) {
    IntInput inputStruct = {-1, false, true, false};
    while (!inputStruct.isEOF && inputStruct.isInvalid &&
           !inputStruct.isCancel) {
        inputStruct = Helper::getUserIntInput(prompt);
        if (inputStruct.isInvalid) {
            cout << "Invalid input. Please enter a valid int." << endl;
        }
    }
    input = inputStruct.input;
    InputFlags inputFlags = {inputStruct.isEOF, inputStruct.isInvalid,
                             inputStruct.isCancel};
    return inputFlags;
}

// Get user float input until valid
Helper::InputFlags Helper::getValidUserInput(const string& prompt,
                                             float& input) {
    FloatInput inputStruct = {-1, false, true, false};
    while (!inputStruct.isEOF && inputStruct.isInvalid &&
           !inputStruct.isCancel) {
        inputStruct = Helper::getUserFloatInput(prompt);
        if (inputStruct.isInvalid) {
            cout << "Invalid input. Please enter a valid float." << endl;
        }
    }
    input = inputStruct.input;
    InputFlags inputFlags = {inputStruct.isEOF, inputStruct.isInvalid,
                             inputStruct.isCancel};
    return inputFlags;
}

void Helper::PrintInvalidInput() { cout << "Invalid input." << endl; }

void Helper::displayHelp() {
    std::cout << "\033[1;33mUsage:\033[0m ./ftt <foodsfile> <coinsfile>"
              << std::endl;
    std::cout << "This program simulates a vending machine." << std::endl;
}



void Helper::handleCommandLineArgs(int argc, char** argv) {
    if (argc > 1) {
        std::string arg1 = argv[1];
        if (arg1 == "-h" || arg1 == "--help") {
            displayHelp();
            exit(0);
        }
    }
}

string Helper::addHelpReminder(const string& prompt) {
    return "\033[1;32m" + prompt +
           " (Type 'h' or 'help' for instructions): \033[0m";
}
