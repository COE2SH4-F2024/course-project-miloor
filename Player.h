#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  // This is the direction state

        Player(GameMechs* thisGMRef);
        ~Player();

        //objPos getPlayerPos() const; // Upgrade this in iteration 3.      
        objPosArrayList* getPlayerPos() const;  
        void updatePlayerDir();
        void movePlayer();

        // More methods to be added here
        bool checkSelfCollision();

    private:
        objPos playerPos; // Upgrade this in iteration 3.       
        enum Dir myDir;
        objPosArrayList* playerPosList;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif


