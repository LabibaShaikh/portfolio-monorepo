// Command.h
#ifndef COMMAND_H
#define COMMAND_H

#include <string>

/**
 * @brief The Command class is an abstract base class that represents a command.
 *
 * This class provides an interface for executing a command and getting the name
 * of the command. Subclasses of Command must implement the execute() and
 * getName() methods.
 */
class Command {
   public:
    /**
     * @brief Destructor for the Command class.
     */
    virtual ~Command() {}

    /**
     * @brief Executes the command.
     *
     * This method should be implemented by subclasses to define the behavior of
     * the command.
     */
    virtual void execute() = 0;

    /**
     * @brief Gets the name of the command.
     *
     * This method should be implemented by subclasses to return the name of the
     * command.
     *
     * @return The name of the command.
     */
    virtual std::string getName() const = 0;
};

#endif  // COMMAND_H
