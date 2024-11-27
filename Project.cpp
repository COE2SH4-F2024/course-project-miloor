#include <iostream>
#include "MacUILib.h"
#include "objPos.h"

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

//struct objPos charInfo = {9,4,'@'};
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

    for (int j = 0; j < 5; j++) {
        itemBin[j].pos->x = j - 50;
        itemBin[j].pos->y = j - 50;
        itemBin[j].symbol = 'A' + j;
    }

    GenerateItems(itemBin, 5, 20, 10); 
    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();   

     //draw board
    int i,j;


    //loop through each row
    for (i = 0; i < 10; i++) {
        //loop through each column
        for (j = 0; j < 20; j++) {
            //check if we are at the border
            if (i == 0 || i == 9 || j == 0 || j == 19) {
                MacUILib_printf("%c", '#');
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
    MacUILib_Delay(10000000); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}


// The Item Generation Routine
////////////////////////////////////
void GenerateItems(objPos* itemBin, const int listSize, const int xRange, const int yRange)
{

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

            // //check and skip if overlap
            // if (x == player.x && y == player.y) {
            //     continue; 
            // }

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