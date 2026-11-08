#include "game.h"

Game::Game()
{
    // TODO
}

Game::~Game()
{
    // TODO
}


void Game::start()
{
    // Load the board and initialize player
    if (!loadBoard() || !initializePlayer()) {
        std::cerr << "Failed to start the game due to initialization error." << std::endl;
        return;
    }
    play();  // Start the game loop

}


bool Game::loadBoard() {
    // Assume there is a method to choose and load a board
    board->load(0);  // Example: Load board with ID 0
    return true;  // Change the return type to match the return type of board->load()
}

bool Game::initializePlayer() {
    // Initialize player at specific position and direction
    Position startPos(5, 4);  // Example start position
    player ->initialisePlayer(&startPos, NORTH);
    return true;
}

/**
 * @brief Starts the game and handles the gameplay loop.
 * 
 * This function prompts the user for commands and executes them until the user chooses to quit.
 * The available commands are "forward" to move the player forward, "turn_left" or "l" to turn the player left,
 * "turn_right" or "r" to turn the player right, and "quit" to exit the game.
 * 
 * During each iteration of the gameplay loop, the function checks if the player's movement is blocked by an obstacle.
 * If the movement is blocked, it displays a message indicating that the move is blocked.
 * Otherwise, it updates the player's position on the board.
 * 
 * After each command, the current state of the board is displayed.
 */
void Game::play() {
    std::string input;
    while (true) {
        std::cout << "Enter command (forward, turn_left, turn_right, quit): ";
        std::getline(std::cin, input);

        if (input == "quit") break;
        else if (input == "forward") {
            Position newPos = player -> getNextForwardPosition();
            if (board -> isBlocked(newPos)) {
                std::cout << "Move blocked!" << std::endl;
            } else {
                player->updatePosition(newPos);  // Assuming this method exists to update the board state
            }
        }
        else if (input == "turn_left" || input == "l") {
            player->turnDirection(TURN_LEFT);
        }
        else if (input == "turn_right" || input == "r") {
            player->turnDirection(TURN_RIGHT);
        }
        board->display(player);  // Display the current state of the board
    }
}