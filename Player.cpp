#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // initial conditions for snake such as start postion, symbol, and score
    int startX = mainGameMechsRef->getBoardSizeX()/2;
    int startY = mainGameMechsRef->getBoardSizeY()/2;
    objPos initialPos(startX, startY, '*');
    playerPosList = new objPosArrayList(); // Initialize the position list for the snake
    playerPosList->insertHead(initialPos); // Insert the initial position as the snake's head
    eatFood = false; // Flag which will track if snake has eaten any food

    gameScore = 0;
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPosList()
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
    // PPA3 input processing logic    
    char input = mainGameMechsRef->getInput(); // get input from game mechanics to process 
    switch(input){
        case 27: // exit with esc key
            mainGameMechsRef->setExitTrue();
            break;

        // key processing here for going up, down, left, right, with wasd keys
        case 'w':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;

        case 'a':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;

        case 's':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;

        case 'd':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
        default:
            break;
    }
    mainGameMechsRef->clearInput(); // clear input after processing 

}
    
void Player::movePlayer()
{
    objPos newHeadPos; // stores the postions of the new head when player moves
    playerPosList->getHeadElement(newHeadPos); // gets current head postion and stores into newHeadPos

    // PPA3 Finite State Machine logic
    // updates the direction the snake moves in and includes the wrap around logic from PPA
    switch (myDir) {
        case UP:
            newHeadPos.y--;
            if (newHeadPos.y == 0)
            {
                newHeadPos.y = mainGameMechsRef->getBoardSizeY() - 2;
            }
            break;
        case LEFT:
            newHeadPos.x--;
            if (newHeadPos.x == 0)
            {
                newHeadPos.x = mainGameMechsRef->getBoardSizeX() - 2;
            }
            break;
        case DOWN:
            newHeadPos.y++;
            if (newHeadPos.y == mainGameMechsRef->getBoardSizeY() - 1)
            {
                newHeadPos.y = 1;
            }
            break;
        case RIGHT:
            newHeadPos.x++;
            if (newHeadPos.x == mainGameMechsRef->getBoardSizeX() - 1)
            {
                newHeadPos.x = 1;
            }
            break;
        default:
            break; // No movement for STOP or undefined directions
    }

    // checks if snake collided with itself and if so set loseFlag to true
    if (detectSnakeCollision(newHeadPos)) {
        mainGameMechsRef->setLoseTrue();
        return;
    }

    playerPosList->insertHead(newHeadPos);

    // removes tail if snake hasn't eaten food else it doesnt remove tail for the growing mechanism to work
    if (!eatFood) {
        playerPosList->removeTail(); // Remove tail to maintain length unless food is eaten
    } else {
        eatFood = false; // Reset food flag after growth
    }
}

int Player::getScore() const{
    // gets the size of the snake if list is not empty, subtract one as we aren't going to count head as having a score 
    if (playerPosList != nullptr){
        return playerPosList->getSize() - 1;
    }
    return 0;
}

bool Player::detectSnakeCollision(const objPos &headPos) const{
    
    // detects if snake collided with itself by checking if snakes head is in the same position as the rest of body
    for (int i = 1; i < playerPosList->getSize(); ++i) {
        objPos snakeBody;
        playerPosList->getElement(snakeBody, i);

        if (snakeBody.x == headPos.x && snakeBody.y == headPos.y) {
            return true;
            break; 
        }
    }
    return false;
}

void Player::setEatFood(bool eatenFood) {
    // sets boolean value for if snake eats food or not
    eatFood = eatenFood;
}

