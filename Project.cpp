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

Player* player;
char input; //user input
GameMechs* gameMechs = new GameMechs();

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
    gameMechs -> generateFoods(*(player -> getPlayerPos()));

    exitFlag = false;
}

void GetInput(void)
{
    if(MacUILib_hasChar()==1)
    {
        input = MacUILib_getChar();
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

    objPosArrayList* playerPos = player->getPlayerPos();
    objPos foodPos = gameMechs -> getFoodPos();
    objPos specialFood = gameMechs -> getSpecialFood();

    //loop through each row
    for (i = 0; i < gameMechs->getBoardSizeY(); i++) {

        //loop through each column
        for (j = 0; j < gameMechs->getBoardSizeX(); j++) {

            //check if we are at the border
            if (i == 0 || i == gameMechs->getBoardSizeY() -1|| j == 0 || j == gameMechs->getBoardSizeX()-1) {
                MacUILib_printf("%c", '#');
            } 

            else{
            int partExists =0;
            int foodPlaced = 0;

            //loop through all snake parts to see if any should be placed at (i,j)
                for(int k = 0; k < playerPos->getSize(); k++)
                {
                    objPos currentPart = playerPos->getElement(k); //current body part
                    if(i == currentPart.pos->y && j==currentPart.pos->x)
                        {
                        MacUILib_printf("%c",currentPart.getSymbol());
                        partExists =1;
                        }
                }

                if (partExists==0)
                {
                    //generate regular foods 
                    for (int n = 0; n < 2; n++)
                    {
                        objPos regularFood = gameMechs -> getRegularFood(n);
                        if (i == regularFood.pos->y && j == regularFood.pos->x)
                        {
                            MacUILib_printf("%c", regularFood.symbol);
                            foodPlaced = 1;
                        }

                    }

                    //generate special food if exists 
                    if (i == specialFood.pos->y && j == specialFood.pos->x)
                        {
                            MacUILib_printf("%c", specialFood.symbol);
                            foodPlaced = 1;
                        }
                
                }
                
                if (!foodPlaced && !partExists)
                {
                    MacUILib_printf(" ");
                }
            
            }
            
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Controls\nw - move up\na - move left\ns- move down\nd - move right\nCurrent score: %d", gameMechs->getScore());
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();   

    if (gameMechs->getLoseFlagStatus()==true)
    {
        MacUILib_printf("You lost! Try again! Your score is: %d\n", gameMechs->getScore());
    } else {
        MacUILib_printf("Your score is: %d\n", gameMechs->getScore());
    }

    delete gameMechs;
    gameMechs = nullptr;
    delete player;
    player = nullptr; 

    MacUILib_uninit();
}
