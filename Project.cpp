#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "time.h"

using namespace std;

#define DELAY_CONST 100000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

void GenerateItems(objPos* itemBin, const int listSize, const int xRange, const int yRange);


Player* player;
char input; //user input
GameMechs* gameMechs = new GameMechs();

objPos itemBin[5];

int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    gameMechs = new GameMechs(30, 15);
    player = new Player(gameMechs);

    for (int j = 0; j < 5; j++) {
        itemBin[j].pos->x = j - 50;
        itemBin[j].pos->y = j - 50;
        itemBin[j].symbol = 'A' + j;
    }

    GenerateItems(itemBin, 5, gameMechs->getBoardSizeX(), gameMechs->getBoardSizeY()); 
    exitFlag = false;
}

void GetInput(void)
{
    if(MacUILib_hasChar()==1)
    {
        char input = MacUILib_getChar();
        gameMechs->setInput(input);
    } 
}

void RunLogic(void)
{
    player->updatePlayerDir();
    player->movePlayer();
    input = '\0';
    if(gameMechs->getExitFlagStatus())
    {
        exitFlag = true;
    }
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

     //draw board
    int i,j;

    objPos playerPos = player->getPlayerPos();
    //MacUILib_printf("Player Pos: (%d, %d) Symbol: %c\n", playerPos.pos->x, playerPos.pos->y, playerPos.symbol);
    //MacUILib_printf("\n");

    //loop through each row
    for (i = 0; i < gameMechs->getBoardSizeY(); i++) {
        //loop through each column
        for (j = 0; j < gameMechs->getBoardSizeX(); j++) {
            //check if we are at the border
            if (i == 0 || i == gameMechs->getBoardSizeY() - 1 || j == 0 || j == gameMechs->getBoardSizeX() - 1) {
                MacUILib_printf("%c", '#');
            } 
            //check if we are at the players position
            else if (i == playerPos.pos->y && j == playerPos.pos->x) {
                MacUILib_printf("%c", playerPos.symbol); //print player char
            } 

            else
            {
                int itemFound = 0;
                int k;
                for (k = 0; k < 5; k++)
                {
                    if (i == itemBin[k].pos->y && j == itemBin[k].pos->x)
                    {
                        MacUILib_printf("%c", itemBin[k].symbol); // Item symbol
                        itemFound = 1;
                        break;
                    }
                }
                if (itemFound == 0)
                {
                    MacUILib_printf(" ");
                }
            
            }
        }
        MacUILib_printf("\n");
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   

    if (gameMechs->getLoseFlagStatus())
    {
        MacUILib_printf("You lost! Try again!");
    } else {
        MacUILib_printf("You tried! Your score is: %d\n", gameMechs->getScore());
    }

    if (gameMechs)
    {
        delete gameMechs;
        gameMechs = nullptr;
    }

    if (player) 
    {
        delete player;
        player = nullptr; 
    }

    MacUILib_uninit();
}


// The Item Generation Routine
////////////////////////////////////
void GenerateItems(objPos* itemBin, const int listSize, const int xRange, const int yRange)
{

    objPos playerPos = player->getPlayerPos();

    int usedCharacters[5];
    for (int k = 0; k < 5; k++) {
        usedCharacters[k] = 0; //0 means not used
    }

    srand(time(NULL)); // rand number generator
    int count = 0;

    for (int i = 0; i < listSize; i++) {
        int x, y;
        int validPosition = 0;  

        char chosenChar;
        int charIndex;

        do {
            charIndex = (rand() % (126 - 33 + 1)) +33;
        } while (usedCharacters[charIndex]==1 || charIndex == 64 || charIndex == 35);

        //mark this character index as used
        itemBin[i].symbol = (char)charIndex;
        
        while (!validPosition) {
            //generate between 1 and range-1
            x = (rand() % (xRange - 2)) + 1; 
            y = (rand() % (yRange - 2)) + 1; 

            //check and skip if overlap
            if (x == playerPos.pos->x && y == playerPos.pos->y) {
                continue; 
            }

            //check if theres already an item 
            int positionOccupied = 0;
            for (int j = 0; j < i; j++) {
                if (itemBin[j].pos->x == x && itemBin[j].pos->y == y) {
                    positionOccupied = 1;
                    break;
                }
            }

            //skip if occupied
            if (positionOccupied) {
                continue; 
            }

            //if no conflicts
            itemBin[i].pos->x = x;
            itemBin[i].pos->y = y;
            
            validPosition = 1;
        }
    }

}