#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "objPosArrayList.h" // Added
#include "Player.h"
#include "GameMechs.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

// Added
class Player;
GameMechs* gameMech = nullptr;
Player* player = nullptr;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);


int main(void)
{

    Initialize();

    while(!gameMech->getExitFlagStatus())  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    exitFlag = false; // Flag for exiting game

    srand((unsigned int)time(NULL)); // Seed the random number generator

    // Create game mechanics object with specified board size
    // Create player object with game mechanics as the reference for interactions
    gameMech = new GameMechs(26, 13);
    player = new Player(gameMech);
    
    objPos pPos; // Temporary object to store position

    // Set initial player position and generate the first food item
    objPosArrayList* pBody = player->getPlayerPosList();
    if (pBody && pBody->getSize() > 0) {
        pBody->getHeadElement(pPos);
    }
    gameMech->setFood(&pPos, pBody);
}

void GetInput(void)
{
   // Input processing logic from other PPAs
   gameMech->getInput();
}

void RunLogic(void)
{
    // Main game logic in here including player movement and collision detection

    // Logic for updating player direction and moving the snake body
    player->updatePlayerDir();
    player->movePlayer();

    // Get the current snake body, and food position
    objPosArrayList* pBody = player->getPlayerPosList();
    objPos snakeHead;
    objPos foodPos;
    gameMech->getFoodPos(foodPos);

    // Gets the head of the snake
    if (pBody && pBody->getSize() > 0) {
        pBody->getHeadElement(snakeHead);
    }

    // Regenerates food if snake collides with food and sets eatFood to true for growing mechanism to work
    if (snakeHead.x == foodPos.x && snakeHead.y == foodPos.y) {
        gameMech->setFood(&snakeHead, pBody); 
        player->setEatFood(true); 
    }
    gameMech->clearInput(); // Clears input
}

void DrawScreen(void)
{
    objPos foodPos;
    objPosArrayList* pBody = player->getPlayerPosList();
    gameMech->getFoodPos(foodPos);

    int row, col;

    // Logic for drawing game board, snake, and food items
    MacUILib_clearScreen();
    for (row = 0; row < gameMech->getBoardSizeY(); row++)
    {
        for (col = 0; col < gameMech->getBoardSizeX(); col++)
        {
            // Draws the game borders
            if (row == 0 || row == gameMech->getBoardSizeY() - 1 || col == 0 || col == gameMech->getBoardSizeX() - 1)
            {   
                MacUILib_printf("#");
            }

            // Draws the food onto the board
            else if (col == foodPos.x && row == foodPos.y) 
            {
                MacUILib_printf("%c", foodPos.symbol);
            }

            // Draws the snake onto the board as long as the position is not occupied and the remaining positions are empty
            else {
                bool exists = false;
                for (int i = 0; i < pBody->getSize(); i++) {
                    objPos body;
                    pBody->getElement(body, i);

                    if (col == body.x && row == body.y) {
                        MacUILib_printf("%c", body.symbol);
                        exists = true;
                        break;
                    }
                }
                if (exists == false)
                {
                    MacUILib_printf(" ");
                }  

            }
        }  
        
        MacUILib_printf("\n");
    }

    MacUILib_printf("\n");
    
    // Clear the screen and show game stats after losing
    if (gameMech->getLoseFlagStatus())
    {   
        MacUILib_clearScreen();
        MacUILib_printf("\nYou Lost\nGame Over!");
        MacUILib_printf("\nYour Snake Collected %d Units of Food!\n", player->getScore());
        gameMech->setExitTrue();
    }

    // Game stats and instructions to display while playing
    else {
        MacUILib_printf("\nINSTRUCTIONS\nThe goal of the game is to capture as much food as you can and grow your snake.\nIf your snake crashes into itself you lose. Goodluck and Have Fun!\n");
        MacUILib_printf("\nGame Score: %d\n", player->getScore());
        MacUILib_printf("\nPress ESC to exit");
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    // Deallocate/delete members on heap
    delete player;
    delete gameMech;
  
    MacUILib_uninit();
}
