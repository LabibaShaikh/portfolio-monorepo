// Menu.h
#ifndef MENU_H
#define MENU_H

#include <vector>

#include "Command.h"
#include "Helper.h"

/**
 * @class Menu
 * @brief Represents a menu with a list of commands.
 *
 * The Menu class provides functionality to display a menu, add commands to the
 * menu, and capture user input for menu selection. It stores a vector of
 * Command pointers to represent the list of available commands.
 */
class Menu {
   public:
    Menu();  // Constructor
    void displayMenu();
    void addCommand(Command* command);
    void captureUserMenuInput();

   private:
    std::vector<Command*> commands;
};

#endif  // MENU_H
