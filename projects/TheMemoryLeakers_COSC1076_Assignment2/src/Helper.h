#ifndef HELPER_H
#define HELPER_H

#include <iostream>
#include <string>
#include <unordered_map>
using std::string;

/**
 * @class Helper
 * @brief A utility class that provides helper functions for user input.
 */
class Helper {
   public:
    /**
     * @brief Structure for storing user string input along with flags
     * indicating end-of-file and invalid input.
     */
    struct StringInput {
        string input; /**< The user input string. */
        bool isEOF; /**< Flag indicating if the end-of-file has been reached. */
        bool isInvalid; /**< Flag indicating if the input is invalid. */
        bool isCancel;  /**< Flag indicating if the input is a cancellation. */
    };

    /**
     * @brief Structure for storing user integer input along with flags
     * indicating end-of-file and invalid input.
     */
    struct IntInput {
        int input;  /**< The user input integer. */
        bool isEOF; /**< Flag indicating if the end-of-file has been reached. */
        bool isInvalid; /**< Flag indicating if the input is invalid. */
        bool isCancel;  /**< Flag indicating if the input is a cancellation. */
    };

    /**
     * @brief Structure for storing user float input along with flags indicating
     * end-of-file and invalid input.
     */
    struct FloatInput {
        float input; /**< The user input float. */
        bool isEOF; /**< Flag indicating if the end-of-file has been reached. */
        bool isInvalid; /**< Flag indicating if the input is invalid. */
        bool isCancel;  /**< Flag indicating if the input is a cancellation. */
    };

    /**
     * @brief Structure for storing flags indicating end-of-file and invalid
     * input.
     */
    struct InputFlags {
        bool isEOF; /**< Flag indicating if the end-of-file has been reached. */
        bool isInvalid; /**< Flag indicating if the input is invalid. */
        bool isCancel;  /**< Flag indicating if the input is a cancellation. */
    };

    /**
     * @brief Get user string input with a prompt.
     * @param prompt The prompt message displayed to the user.
     * @return The user string input along with end-of-file and invalid input
     * flags.
     */
    static StringInput getUserStringInput(const string& prompt);

    /**
     * @brief Get user integer input with a prompt.
     * @param prompt The prompt message displayed to the user.
     * @return The user integer input along with end-of-file and invalid input
     * flags.
     */
    static IntInput getUserIntInput(const string& prompt);

    /**
     * @brief Get user float input with a prompt.
     * @param prompt The prompt message displayed to the user.
     * @return The user float input along with end-of-file and invalid input
     * flags.
     */
    static FloatInput getUserFloatInput(const string& prompt);

    /**
     * @brief Get user string input without a prompt.
     * @return The user string input along with end-of-file and invalid input
     * flags.
     */
    static StringInput getUserStringInputImpl(const string& prompt);

    /**
     * @brief Get user integer input without a prompt.
     * @return The user integer input along with end-of-file and invalid input
     * flags.
     */
    static IntInput getUserIntInputImpl(const string& prompt);

    /**
     * @brief Get user float input without a prompt.
     * @return The user float input along with end-of-file and invalid input
     * flags.
     */
    static FloatInput getUserFloatInputImpl(const string& prompt);

    /**
     * @brief Loop and get user string input with a prompt until a valid input
     * is provided.
     * @param prompt The prompt message displayed to the user.
     * @param input The user string input.
     * @return Flags indicating end-of-file and invalid input.
     */
    static InputFlags getValidUserInput(const string& prompt, string& input);

    /**
     * @brief Loop and get user integer input with a prompt until a valid input
     * is provided.
     * @param prompt The prompt message displayed to the user.
     * @param input The user integer input.
     * @return Flags indicating end-of-file and invalid input.
     */
    static InputFlags getValidUserInput(const string& prompt, int& input);

    /**
     * @brief Loop and get user float input with a prompt until a valid input is
     * provided.
     * @param prompt The prompt message displayed to the user.
     * @param input The user float input.
     * @return Flags indicating end-of-file and invalid input.
     */
    static InputFlags getValidUserInput(const string& prompt, float& input);

    /**
     * @brief Prints a message indicating invalid input.
     */
    static void PrintInvalidInput();

    /**
     * @brief Dispaly the helper printout
     */
    static void displayHelp();
    static void handleCommandLineArgs(int argc, char** argv);
    static string addHelpReminder(const string& prompt);

    static std::unordered_map<string, string>
        helpMessages; /**< Map to store help messages for specific prompts. */
    static void initializeHelpMessages(); /**< Initialize help messages for
                                             various prompts. */
    static void printSpecificHelp(
        const string& prompt); /**< Print context-specific help message. */
};

#endif  // HELPER_H
