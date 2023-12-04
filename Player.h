#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        // void getPlayerPos(objPos &returnPos); // Upgrade this in iteration 3.
        objPosArrayList* getPlayerPosList();
        void updatePlayerDir();
        void movePlayer();

        // Added 
        int getScore() const;
        bool detectSnakeCollision(const objPos &headPos) const;
        void setEatFood(bool eatenFood);

    private:
        // objPos playerPos;  // Upgrade this in iteration 3.
        objPosArrayList* playerPosList;        
        enum Dir myDir;

        // Added
        bool eatFood;
        int gameScore;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif