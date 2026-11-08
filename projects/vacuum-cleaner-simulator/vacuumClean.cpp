/**
 * @file vacuumClean.cpp
 * @brief Implementation of the vacuum cleaner game.
 */

#include "game.h"
#include "helper.h"
#include "player.h"
#include "board.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>

using std::string;
Board board;
Player player;

/**
 * @brief Display the menu options.
 */
void menuOptions(void)
{
    std::cout << "1. Play Game" << std::endl;
    std::cout << "2. Show Student's information" << std::endl;
    std::cout << "3. Quit" << std::endl;
    std::cout << std::endl;
    std::cout << "Please enter your choice: ";
}

/**
 * @brief Display the student information.
 * @param name The name of the student.
 * @param id The student ID.
 * @param email The student's email.
 */
void showStudentInformation(string name, string id, string email)
{
    std::cout << "-----------------------------------" << std::endl;
    std::cout << "Name: " << name << std::endl;
    std::cout << "Student ID: " << id << std::endl;
    std::cout << "Email: " << email << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}

/**
 * @brief Instructions on how to play the game.
 */
void playGame(void)
{
    std::cout << "You can use the following commands to play the game:" << std::endl;
    std::cout << "load <g>" << std::endl;
    std::cout << "   g: number of the game board to load" << std::endl;
    std::cout << "init <x>,<y>,<direction>" << std::endl;
    std::cout << "   x: horizontal position of the vacuum cleaner in the room (between 0 & 9)" << std::endl;
    std::cout << "   y: vertical position of the vacuum cleaner in the room (between 0 & 9)" << std::endl;
    std::cout << "   direction: direction of the vacuum cleaner’s movement (north, east, south, west)" << std::endl;
    std::cout << "forward (or f)" << std::endl;
    std::cout << "turn_left (or l)" << std::endl;
    std::cout << "turn_right (or r)" << std::endl;
    std::cout << "quit" << std::endl;
    board.load(0);  // This will load BOARD_0 wjich is the empty board
    board.display(nullptr);  // Display the board assuming the display method handles nullptr for no player
}

/**
 * @brief Executes the instructions for the vacuum cleaner game.
 * @param board The game board.
 * @param player The player object.
 */
void Instructions(Board& board, Player& player) {
    bool continueInstructions = true;
    bool boardLoaded = false;
    bool playerInitialised = false;

    while (continueInstructions) {
        std::cout << "\nAt this stage of the program, the following commands are acceptable:" << std::endl;
        if (!boardLoaded) {
            std::cout << "load <g> - Load a game board." << std::endl;
        }
        if (!playerInitialised && boardLoaded) {
            std::cout << "init <x>,<y>,<direction> - Initialize player position and direction." << std::endl;
        }
        if (playerInitialised) {
            std::cout << "forward or 'f' - Move player forward." << std::endl;
            std::cout << "turn_left or 'l' - Turn player left." << std::endl;
            std::cout << "turn_right or 'r' - Turn player right." << std::endl;
        }
        std::cout << "quit - Quit the game." << std::endl;
        std::cout << "Please enter your choice: ";

        string input;
        if (!std::getline(std::cin, input)) {
            if (std::cin.eof()) {
                std::cout << "End of file detected. Exiting game." << std::endl;
                break;  // Properly handle EOF
            } else {
                std::cerr << "Input error. Please try again." << std::endl;
                continue;
            }
        }

        if (input == "quit") {
            std::cout << "\nTotal player moves: " << player.moves << std::endl;
            std::cout << "Exiting game...\n" << std::endl;
            break;
        }

        std::vector<string> tokens;
        Helper::splitString(input, tokens, " ,");

        if (!tokens.empty()) {
            string command = tokens[0];
            if (command == "load" && !boardLoaded) {
                int boardChoice = std::stoi(tokens[1]);
                board.load(boardChoice);
                board.display(nullptr);
                boardLoaded = true;
            } else if (command == "init" && boardLoaded && !playerInitialised) {
                try {
                    int x = std::stoi(tokens[1]);
                    int y = std::stoi(tokens[2]);
                    std::string dir = tokens[3];
                    Direction direction;
                    if (dir == "north") direction = NORTH;
                    else if (dir == "east") direction = EAST;
                    else if (dir == "south") direction = SOUTH;
                    else if (dir == "west") direction = WEST;
                    else throw std::invalid_argument("Invalid direction");

                    Position pos(x, y);
                    if (board.isPositionWithinBounds(pos) && !board.isBlocked(pos)) {
                        player.initialisePlayer(&pos, direction);
                        board.display(&player);
                        playerInitialised = true;
                    } else if (!board.isPositionWithinBounds(pos)) {
                        std::cerr << "\nOut of bounds." << std::endl;
                    } else {
                        std::cerr << "\nObstacle encountered." << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << std::endl;
                }
            } else if (playerInitialised) {
                if (command == "forward" || command == "f") {
                    Position newPos = player.getNextForwardPosition();
                    if (board.isPositionWithinBounds(newPos)) {
                        if (!board.isBlocked(newPos)) {
                            player.updatePosition(newPos);
                            board.display(&player);
                        } else {
                            std::cout << "\nUnable to move - cell is blocked." << std::endl;
                        }
                    } else {
                        std::cout << "\nThe vacuum cleaner is at the edge of the board and cannot move further in that direction." << std::endl;
                    }
                } else if (command == "turn_left" || command == "l") {
                    player.turnDirection(TURN_LEFT);
                    board.display(&player);
                } else if (command == "turn_right" || command == "r") {
                    player.turnDirection(TURN_RIGHT);
                    board.display(&player);
                }
            } else {
                std::cerr << "Invalid command or action not available. Please try again." << std::endl;
            }
        } else {
            std::cerr << "No command entered. Please try again." << std::endl;
        }
    }
}




/**
 * @brief Main function.
 * @return EXIT_SUCCESS.
 */
int main()
{
    while (!std::cin.eof()) {  // Continue until EOF
        menuOptions();
        int choice = 0;
        if (!(std::cin >> choice)) { // Check if input is an integer
            if (std::cin.eof()) { // Check if EOF is encountered
                break;  // Exit if EOF is encountered
            }
            std::cin.clear();  // Clear error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Skip bad input
            std::cout << "Invalid input. Please try again.\n";
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Clear the newline character

        if (choice == 1) {
            playGame(); 
            Instructions(board, player); // Call Instructions directly since Helper's methods are static
        } else if (choice == 2) {
            showStudentInformation("Shaikh Naima Labiba", "s3954789", "s3954789@student.rmit.edu.au");
        } else if (choice == 3) {
            break; // Exit the main loop and end the program
        } else {
            std::cout << "Invalid choice. Please try again.\n";
            // call menuOptions() again here or just loop back to the beginning.
        }
    }
    std::cout << std::endl;
    std::cout << "Good bye!\n";
    return EXIT_SUCCESS;
}
    


// Example of validating and updating position in game logic
// Position nextPosition = player.getNextForwardPosition();
// if (board.isPositionValid(nextPosition)) {  // Assume this method checks boundaries and other conditions
//     player.updatePosition(nextPosition);
// } else {
//     std::cout << "Cannot move to the new position: Out of bounds or blocked!" << std::endl;
// }
