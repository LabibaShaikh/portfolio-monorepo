// ConcreteCommands.h
#ifndef CONCRETE_COMMANDS_H
#define CONCRETE_COMMANDS_H

#include "Command.h"
#include "Helper.h"
#include "VendingMachine.h"

class DisplayMealOptionsCommand : public Command {
   private:
    VendingMachine* vendingMachine;

   public:
    DisplayMealOptionsCommand(VendingMachine* vm) : vendingMachine(vm) {}
    void execute() override { vendingMachine->displayItems(); }
    std::string getName() const override { return "Display Meal Options"; }
};

/**
 * @class PurchaseMealCommand
 * @brief A concrete implementation of the Command interface that represents a
 * command to purchase a meal from a vending machine.
 */
class PurchaseMealCommand : public Command {
   private:
    VendingMachine* vendingMachine;

   public:
    /**
     * @brief Constructs a PurchaseMealCommand object with the given vending
     * machine.
     * @param vm A pointer to the VendingMachine object.
     */
    PurchaseMealCommand(VendingMachine* vm) : vendingMachine(vm) {}

    /**
     * @brief Executes the purchase meal command.
     * If the purchase is successful, it displays a message indicating that the
     * transaction is cancelled.
     */
    void execute() override {
        bool exit_status = vendingMachine->purchaseItem();
        if (exit_status) {
            std::cout << "\033[1;31mTransaction Cancelled.\033[0m" << std::endl;
        }
    }

    /**
     * @brief Gets the name of the command.
     * @return The name of the command as a string.
     */
    std::string getName() const override { return "Purchase Meal"; }
};

class SaveAndExitCommand : public Command {
   private:
    VendingMachine* vendingMachine;

   public:
    SaveAndExitCommand(VendingMachine* vm) : vendingMachine(vm) {}
    void execute() override {
        vendingMachine->saveItems();
        exit(0);
    }
    std::string getName() const override { return "Save and Exit"; }
};

/**
 * @class AddFoodCommand
 * @brief A concrete implementation of the Command interface that represents a command to add food to a vending machine.
 */
class AddFoodCommand : public Command {
   private:
    VendingMachine* vendingMachine;

   public:
    /**
     * @brief Constructs an AddFoodCommand object with the given vending machine.
     * @param vm A pointer to the VendingMachine object.
     */
    AddFoodCommand(VendingMachine* vm) : vendingMachine(vm) {}

    /**
     * @brief Executes the command by adding an item to the vending machine.
     * If the item cannot be added, an error message is displayed.
     */
    void execute() override {
        bool exit_status = vendingMachine->addItem();
        if (exit_status) {
            std::cout << "\033[1;31mFailed to add item. EOF Detected.\033[0m"
                      << std::endl;
        }
    }

    /**
     * @brief Returns the name of the command.
     * @return The name of the command as a string.
     */
    std::string getName() const override { return "Add Food"; }
};

/**
 * @class RemoveFoodCommand
 * @brief A concrete implementation of the Command interface that represents a command to remove food from a vending machine.
 */
class RemoveFoodCommand : public Command {
   private:
    VendingMachine* vendingMachine;

   public:
    /**
     * @brief Constructs a RemoveFoodCommand object with the given vending machine.
     * @param vm A pointer to the VendingMachine object.
     */
    RemoveFoodCommand(VendingMachine* vm) : vendingMachine(vm) {}

    /**
     * @brief Executes the remove food command.
     * If the removal is successful, it displays a message indicating the end of file detection.
     */
    void execute() override {
        bool exit_status = vendingMachine->removeItem();
        if (exit_status) {
            std::cout << "\033[1;31mEOF detected. Canceling...\033[0m"
                      << std::endl;
        }
    }

    /**
     * @brief Gets the name of the command.
     * @return The name of the command as a string.
     */
    std::string getName() const override { return "Remove Food"; }
};

class DisplayBalanceCommand : public Command {
   private:
    VendingMachine* vendingMachine;

   public:
    DisplayBalanceCommand(VendingMachine* vm) : vendingMachine(vm) {}
    void execute() override { vendingMachine->cr.displayBalance(); }
    std::string getName() const override { return "Display Balance"; }
};

class AbortProgramCommand : public Command {
   public:
    void execute() override { exit(0); }
    std::string getName() const override { return "Abort Program"; }
};

#endif  // CONCRETE_COMMANDS_H
