#include "GameMechs.h"
#include "MacUILib.h"


GameMechs::GameMechs()
{

}

GameMechs::GameMechs(int boardX, int boardY) : boardSizeX(boardX), boardSizeY(boardY), input(0), exitFlag(false), loseFlag(false)
{
    // Initializes the game mechanics with specific board dimensions and default values for input, exitFlag, and loseFlag
}

// do you need a destructor?

bool GameMechs::getExitFlagStatus()
{
    return exitFlag; // Returns the current state of the exit flag
}

char GameMechs::getInput()
{
    // gets user input
    if (MacUILib_hasChar())
    {
        input = MacUILib_getChar();
    }
    return input; // Return the obtained input character
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX; // Return the X dimension of the game board
}

int GameMechs::getBoardSizeY()
{
    return boardSizeY; // Return the Y dimension of the game board
}


void GameMechs::setExitTrue()
{
    exitFlag = true; // Set the exit flag to indicate the end of the game
}

void GameMechs::setInput(char this_input)
{
    input = this_input; // Set the input character
}

void GameMechs::clearInput()
{
    input = 0; // Reset the input to its default state (no input)
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag; // Returns the current state of the lose flag
}

void GameMechs::setLoseTrue()
{
    loseFlag = true; // Set the lose flag to indicate the player has lost the game
}

void GameMechs::setFood(objPos *playerPos, objPosArrayList *snake){
    // logic for generating food similar to PPA3 character generation
    int myRandomX, myRandomY;
    bool dupeExists;
    do {
        // Generate random X and Y coordinates within the board limits
        myRandomX = rand() % boardSizeX;
        myRandomY = rand() % boardSizeY;

        dupeExists = false;

        // Check for collision with the player's position or board edges
        if (myRandomX == playerPos->x && myRandomY == playerPos->y) {
            dupeExists = true;
        }
        else if (myRandomX == boardSizeX - 1 || myRandomY == boardSizeY - 1 || myRandomX == 0 || myRandomY == 0) {
            dupeExists = true;
        }

        // Check for collision with the snake's body
        for (int i = 0; i < snake->getSize(); ++i) {
            objPos snakeBody;
            snake->getElement(snakeBody, i);
            if (snakeBody.x == myRandomX && snakeBody.y == myRandomY) {
                dupeExists = true;
                break;
            }
        }

    } while (dupeExists); // Repeat until a free spot is found

    foodPos.setObjPos(myRandomX, myRandomY, 'O'); // Set the food position with symbol 'O'
}

void GameMechs::getFoodPos(objPos &returnPos){
    returnPos = foodPos; // Returns the current food position
}


