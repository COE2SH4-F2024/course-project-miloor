#include "Player.h"
#include "MacUILib.h"



Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');

    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
     return playerPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();


    if (input!= '\0')
    {
    switch (input)
    {
        case 'w': 
            if (myDir == RIGHT || myDir == LEFT || myDir == STOP)
            {
                myDir = UP;
            }
            break;
        case 's': 
            if (myDir == RIGHT || myDir == LEFT || myDir == STOP)
            {
                myDir = DOWN;
            }
            break;
        case 'a': 
            if (myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = LEFT;
            }
            break;
        case 'd': 
            if (myDir == UP || myDir == DOWN || myDir == STOP)
            {
                myDir = RIGHT;
            }
            break;
        case ' ': 
            myDir = STOP;
            break;
        default:
            break;
    }    
    } 
}

void Player::movePlayer()
{

    //change player position
    if (myDir == UP)
    {
        playerPos.pos->y--;
    }
    else if (myDir == DOWN)
    {
        playerPos.pos->y++;
    }
    else if (myDir == RIGHT)
    {
        playerPos.pos->x++;
    }
    else if (myDir == LEFT)
    {
        playerPos.pos->x--;
    }

    //border wraparound
    if (playerPos.pos->y == mainGameMechsRef->getBoardSizeY()-1)
    {
        playerPos.pos->y = 1;
    }
    else if (playerPos.pos->y == 0)
    {
        playerPos.pos->y = mainGameMechsRef->getBoardSizeY()-1;
    }
    if (playerPos.pos->x == mainGameMechsRef->getBoardSizeX()-1)
    {
        playerPos.pos->x = 1;
    }
    else if (playerPos.pos->x == 0)
    {
        playerPos.pos->x = mainGameMechsRef->getBoardSizeX()-1;
    }
}

// More methods to be added