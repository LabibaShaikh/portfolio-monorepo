/**
 * @file board.cpp
 * @brief Implementation file for the Board class.
 */
/**
 * @file board.cpp
 * @brief Implementation file for the Board class.
 */
#include "board.h"

using std::vector;



const vector<vector<Cell>> Board::BOARD_1 =
{
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { BLOCKED, BLOCKED, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

const vector<vector<Cell>> Board::BOARD_2 =
{
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY, BLOCKED, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, BLOCKED, EMPTY },
    { EMPTY, BLOCKED, BLOCKED, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY }
};

const vector<vector<Cell>> Board::BOARD_0 =
{
    { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
     { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
      { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
       { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
         { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
          { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
           { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
            { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },
             { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY },

    
};



Board::Board()
{
  
        // Initialize the member variable 'board', not a local variable
        board = new std::vector<std::vector<Cell>>(DEFAULT_BOARD_DIMENSION, std::vector<Cell>(DEFAULT_BOARD_DIMENSION, EMPTY));

}

Board::~Board()
{
    delete board;
}



void Board::load(int boardId)
{
   if( boardId == 0){
     *board = BOARD_0;
     boardLoaded = true;
   }

   if( boardId == 1){
     *board = BOARD_1;
    
   }
   if( boardId == 2){
     *board = BOARD_2;
     boardLoaded = true;
   }

   else {
        boardLoaded = false;
   }

    //  boardLoaded = true; // Set this flag to true after successfully loading a board
   
}
// Boundary Checking: The method first checks if the provided position is within the valid boundaries of the board. If the position is outside the boundaries, it immediately returns true, treating out-of-bounds as blocked to prevent the player from moving out of the defined play area.
// Blocked Cell Checking: If the position is within bounds, the method then checks if the cell at that position is marked as BLOCKED in the board vector.
/**
 * Checks if a given position on the board is blocked.
 *
 * @param pos The position to check.
 * @return True if the position is blocked, false otherwise.
 */
bool Board::isBlocked(const Position& pos) {
    // First check if the position is within the bounds of the board
    if (pos.x < 0 || pos.x >= DEFAULT_BOARD_DIMENSION || pos.y < 0 || pos.y >= DEFAULT_BOARD_DIMENSION) {
        return true; // Position is out of bounds, treated as blocked for safety.
    }

    // Check if the cell at the given position is blocked
    return (*board)[pos.y][pos.x] == BLOCKED;
}

/**
 * @brief Sets the cell state at the given position on the board.
 * 
 * This function updates the state of the cell at the specified position on the board.
 * The position must be within the bounds of the board dimensions.
 * 
 * @param position The position of the cell to be updated.
 * @param newCellState The new state to be set for the cell.
 */
void Board::setCell(const Position& position, Cell newCellState)  {
    if (position.x >= 0 && position.x < DEFAULT_BOARD_DIMENSION && 
        position.y >= 0 && position.y < DEFAULT_BOARD_DIMENSION) {
        (*board)[position.y][position.x] = newCellState;
    }
}
// In Board class
/**
 * Checks if a given position is within the bounds of the board.
 *
 * @param position The position to check.
 * @return True if the position is within the bounds, false otherwise.
 */
bool Board::isPositionWithinBounds(const Position& position) {
    return position.x >= 0 && position.x < DEFAULT_BOARD_DIMENSION &&
           position.y >= 0 && position.y < DEFAULT_BOARD_DIMENSION;
}

/**
 * Clears the cell at the specified position on the board.
 *
 * @param position The position of the cell to be cleared.
 * @return True if the cell was successfully cleared, false otherwise.
 */
bool Board::clearCell(const Position& position) {
    if (isPositionWithinBounds(position)) {
        (*board)[position.y][position.x] = EMPTY;
        return true;
    }
    return false;
}

/**
 * Places the player on the board at the specified position.
 * 
 * @param position The position where the player should be placed.
 * @return True if the player was successfully placed, false otherwise.
 */
bool Board::placePlayer(Position position) {
    // Check if the position is within the board boundaries
    if (position.x < 0 || position.x >= DEFAULT_BOARD_DIMENSION || 
        position.y < 0 || position.y >= DEFAULT_BOARD_DIMENSION) {
        return false;  // Position is out of bounds
    }

    // Check if the position is not blocked
    if ((*board)[position.y][position.x] == BLOCKED) {
        return false;  // Cannot place player on a blocked cell
    }

    // Place the player
    (*board)[position.y][position.x] = PLAYER;
    return true;
}


/**
 * Enum representing the possible moves of a player on the board.
 */
/**
 * Moves the player forward on the board.
 * 
 * @param player A pointer to the player object.
 * @return The move made by the player.
 */
PlayerMove Board::movePlayerForward(Player* player) {
    Position nextPos = player->getNextForwardPosition();

    // Check bounds
    if (nextPos.x < 0 || nextPos.x >= DEFAULT_BOARD_DIMENSION || 
        nextPos.y < 0 || nextPos.y >= DEFAULT_BOARD_DIMENSION) {
        return OUTSIDE_BOUNDS;
    }

    // Check if the next position is blocked
    if ((*board)[nextPos.y][nextPos.x] == BLOCKED) {
        return CELL_BLOCKED;
    }

    // Move player: clear the old position
    (*board)[player->position.y][player->position.x] = EMPTY;

    // Set the new position
    (*board)[nextPos.y][nextPos.x] = PLAYER;
    player->updatePosition(nextPos);  // Update player's internal position

    return PLAYER_MOVED;
}



/**
 * Displays the current state of the board.
 * Prints the column headers and iterates over each cell in the board,
 * printing its status as '*' for BLOCKED and ' ' for EMPTY.
 *
 * @param player A pointer to the current player.
 */
/**
 * 
 * @param player A pointer to the current player.
 */
void Board::display(Player* player) {
    std::cout << "| |0|1|2|3|4|5|6|7|8|9|" << std::endl;
    for (int y = 0; y < DEFAULT_BOARD_DIMENSION; y++) {
        std::cout << "|" << y << "|";
        for (int x = 0; x < DEFAULT_BOARD_DIMENSION; x++) {
            if (player != nullptr && x == player->position.x && y == player->position.y) {
                player->displayDirection();  // Ensure this function outputs exactly one space-wide character
                std::cout << "|";  // Close the cell after player's direction display
            } else {
                std::cout << ((*board)[y][x] == EMPTY ? " " : 
                             (*board)[y][x] == BLOCKED ? "*" : " ") << "|";
            }
        }
        std::cout << std::endl;
    }
}



