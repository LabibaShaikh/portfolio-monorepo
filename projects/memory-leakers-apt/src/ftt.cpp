#include <iostream>

#include "ConcreteCommands.h"
#include "Helper.h"
#include "Menu.h"
#include "VendingMachine.h"


/**
 * The main function of the program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line arguments.
 * @return 0 indicating successful program execution.
 */
int main(int argc, char **argv) {
    Helper::handleCommandLineArgs(argc, argv);  // Check for help argument
    Helper::initializeHelpMessages();

    VendingMachine vm;
    vm.autoInitialize(argc, argv);

    Menu menu;
    menu.addCommand(new DisplayMealOptionsCommand(&vm));
    menu.addCommand(new PurchaseMealCommand(&vm));
    menu.addCommand(new SaveAndExitCommand(&vm));
    menu.addCommand(new AddFoodCommand(&vm));
    menu.addCommand(new RemoveFoodCommand(&vm));
    menu.addCommand(new DisplayBalanceCommand(&vm));
    menu.addCommand(new AbortProgramCommand());

    menu.captureUserMenuInput();

    return 0;
}
