#include "Player.h"
#include "MacUILib.h"



Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    //playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '*');
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(mainGameMechsRef->getBoardSizeX()/2,mainGameMechsRef->getBoardSizeY()/2,'*'));

    // more actions to be included
}

Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

// objPos Player::getPlayerPos() const
// {
//     // return the reference to the playerPos arrray list
//     //return playerPos;
//     return playerPosList->getHeadElement();
// }

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
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
    objPos headPos = playerPosList->getHeadElement(); //position of head
    

    //change player position
    if (myDir == UP)
    {
        headPos.pos->y--;
    }
    else if (myDir == DOWN)
    {
        headPos.pos->y++;
    }
    else if (myDir == RIGHT)
    {
        headPos.pos->x++;
    }
    else if (myDir == LEFT)
    {
        headPos.pos->x--;
    }

    //border wraparound
    if (headPos.pos->y == mainGameMechsRef->getBoardSizeY()-1)
    {
        headPos.pos->y = 1;
    }
    else if (headPos.pos->y == 0)
    {
        headPos.pos->y = mainGameMechsRef->getBoardSizeY()-1;
    }
    if (headPos.pos->x == mainGameMechsRef->getBoardSizeX()-1)
    {
        headPos.pos->x = 1;
    }
    else if (headPos.pos->x == 0)
    {
        headPos.pos->x = mainGameMechsRef->getBoardSizeX()-1;
    }

    playerPosList->insertHead(headPos);
    playerPosList->removeTail();
}

// More methods to be added