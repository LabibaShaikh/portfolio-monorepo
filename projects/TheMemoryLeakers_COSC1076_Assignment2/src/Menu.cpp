#include "Menu.h"

#include <iostream>

#define INDENT "   "

Menu::Menu() {}

void Menu::displayMenu() {
    std::cout << "Main Menu: " << std::endl;
    for (size_t i = 0; i < commands.size(); ++i) {
        std::cout << INDENT << i + 1 << ". " << commands[i]->getName()
                  << std::endl;
    }
}

void Menu::addCommand(Command* command) { commands.push_back(command); }

void Menu::captureUserMenuInput() {
    Helper::IntInput userInputStruct = {0, false, true, false};
    bool continueLoop = true;  // Flag to control the loop

    while (continueLoop) {
        displayMenu();
        userInputStruct = Helper::getUserIntInput("Select your option: ");

        if (!userInputStruct.isInvalid && !userInputStruct.isEOF) {
            int choice = userInputStruct.input - 1;
            if (choice >= 0 && choice < static_cast<int>(commands.size())) {
                commands[choice]->execute();
                std::cout << std::endl;
            } else {
                std::cout << "\033[1;31mInvalid choice, please select a valid "
                             "option.\033[0m"
                          << std::endl;
            }
        } else if (userInputStruct.isEOF) {
            std::cout << "\033[1;33mQuitting program...\033[0m" << std::endl;
            continueLoop = false;  // Exit the loop
        } else {
            std::cout
                << "\033[1;31mInvalid input, please enter a number.\033[0m"
                << std::endl;
        }
    }
}
