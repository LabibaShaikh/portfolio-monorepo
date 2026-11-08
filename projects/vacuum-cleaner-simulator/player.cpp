/**
 * @file player.cpp
 * @brief Implementation file for the Player class and related functions.
 */

#include "player.h"
#include <vector>
#include <algorithm>  // Include to use std::find

/**
 * @brief Default constructor for the Position class.
 * 
 * This constructor initializes the x and y coordinates of the position to 0.
 */
Position::Position() : x(0), y(0) {}

/**
 * @brief Constructs a Position object with the specified x and y coordinates.
 *
 * @param x The x coordinate of the position.
 * @param y The y coordinate of the position.
 */
Position::Position(int x, int y) : x(x), y(y) {}

/**
 * @brief Default constructor for the Player class.
 * 
 * This constructor initializes the player object.
 */
Player::Player()
{
    //TODO
}

/**
 * @brief Initializes the player's position and direction.
 *
 * @param position A pointer to the Position object representing the player's position.
 * @param direction The initial direction of the player.
 */
void Player::initialisePlayer(Position* position, Direction direction) {
    this->position = *position;  // Dereference the pointer and set the player's position
    this->direction = direction; // Set the direction
    this->moves = 0;             // Reset move count
}

/**
 * @brief Turns the player's direction.
 *
 * @param turnDirection The direction to turn.
 */
void Player::turnDirection(TurnDirection turnDirection)
{
    // Define the list of directions in the order they are to be cycled through.
    static const std::vector<Direction> directions = {NORTH, EAST, SOUTH, WEST};
    
    // Find the current index of the direction in the list.
    auto currentDirectionIndex = std::find(directions.begin(), directions.end(), direction) - directions.begin();
    
    if (turnDirection == TURN_RIGHT) {
        // Move to the next direction in the list, wrapping around to the beginning if necessary.
        direction = directions[(currentDirectionIndex + 1) % directions.size()];
    } else if (turnDirection == TURN_LEFT) {
        // Move to the previous direction in the list, wrapping around to the end if necessary.
        direction = directions[(currentDirectionIndex + 3) % directions.size()];  // +3 is equivalent to -1 modulo size
    }

    // Optionally, display the new direction after turning
    // I decided to keep it commented out as it is not required for the current implementation
    // this displayed the current direction after turning in the corner of the board, uncomment to see
    // displayDirection();
}

/**
 * @brief Calculates the next position if the player moves forward.
 *
 * @return The next position if the player moves forward.
 */
Position Player::getNextForwardPosition()
{
    Position nextPosition = position; // Create a copy of the current position

    // Update the next position based on the current direction
    if (direction == NORTH) {
        nextPosition.y--;
    } else if (direction == EAST) {
        nextPosition.x++;
    } else if (direction == SOUTH) {
        nextPosition.y++;
    } else if (direction == WEST) {
        nextPosition.x--;
    }

    return nextPosition;
}

/**
 * @brief Updates the player's position.
 *
 * @param position The new position of the player.
 */
/**
 * @brief Updates the player's position.
 *
 * @param newPosition The new position of the player.
 */
void Player::updatePosition(Position newPosition)
{
    // Update the player's current position with the new position
    position = newPosition;

    // Increment the move count to record this as a valid move
    moves++;

    
}


/**
 * @brief Displays the player's direction.
 *
 * Prints the corresponding arrow symbol based on the current direction of the player.
 */
void Player::displayDirection() {
    if (direction == NORTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_NORTH;
    } else if (direction == EAST) {
        std::cout << DIRECTION_ARROW_OUTPUT_EAST;
    } else if (direction == SOUTH) {
        std::cout << DIRECTION_ARROW_OUTPUT_SOUTH;
    } else if (direction == WEST) {
        std::cout << DIRECTION_ARROW_OUTPUT_WEST;
    }
}

