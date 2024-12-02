#include "GameMechs.h"
#include "MacUILib.h"
#include <iostream>


GameMechs::GameMechs()
{
    input = 0;
    boardSizeX = 30;
    boardSizeY = 15;
    food.setObjPos(-5,-5,'+');
}

GameMechs::GameMechs(int boardX, int boardY)
{

    boardSizeX = boardX;
    boardSizeY = boardY;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    input = 0;
    //specialFoodActive = false;

}

GameMechs::~GameMechs() {
    
}

void GameMechs::generateFood(const objPosArrayList& snakeBody) {
    static bool seeded = false; //ensures its seeded only once
    if (!seeded) {
        srand(time(0));
        seeded = true;
    }

    int newXval;
    int newYval;
    bool isValid = false;

    while (!isValid) 
    {
        newXval = rand() % (boardSizeX - 2) + 1;  // generates random position 
        newYval = rand() % (boardSizeY - 2) + 1;
        isValid = true;

        for (int i = 0; i < snakeBody.getSize(); ++i)   // checks if there's overlap with snake body
        {
            if (snakeBody.getElement(i).pos->x == newXval &&
                snakeBody.getElement(i).pos->y == newYval) {
                isValid = false;
                break;
            }
        }
    }

    // Set the new food position
    food.setObjPos(newXval, newYval, '+');
}

void GameMechs::generateFoods(const objPosArrayList& snakeBody) {
    srand(time(0)); //seed random number generator
    int newXval;
    int newYval;
    bool isValid;

    // Generate regular foods
    for (int i = 0; i < 2; ++i) {
        do {
            isValid = true;
            newXval = rand() % (boardSizeX - 2) + 1; // Ensure within boundaries
            newYval = rand() % (boardSizeY - 2) + 1;

            // Check overlap with snake
            for (int j = 0; j < snakeBody.getSize(); ++j) {
                if (snakeBody.getElement(j).pos->x == newXval &&
                    snakeBody.getElement(j).pos->y == newYval) {
                    isValid = false;
                    break;
                }
            }

            //ensure no overlap with previously placed foods
            for (int j = 0; j < i; ++j) {
                if (regularFoods[j].pos->x == newXval && regularFoods[j].pos->y == newYval) {
                    isValid = false;
                    break;
                }
            }
        } while (!isValid);

        regularFoods[i].setObjPos(newXval, newYval, '+'); // symbol for regular food
    }

    //generate special food
    if (!specialFoodActive) {
        do {
            isValid = true;
            newXval = rand() % (boardSizeX - 2) + 1;
            newYval = rand() % (boardSizeY - 2) + 1;

            //check overlap with snake
            for (int j = 0; j < snakeBody.getSize(); ++j) {
                if (snakeBody.getElement(j).pos->x == newXval &&
                    snakeBody.getElement(j).pos->y == newYval) {
                    isValid = false;
                    break;
                }
            }

            //ensure no overlap with regular foods
            for (int j = 0; j < 2; ++j) {
                if (regularFoods[j].pos->x == newXval && regularFoods[j].pos->y == newYval) {
                    isValid = false;
                    break;
                }
            }
        } while (!isValid);

        specialFood.setObjPos(newXval, newYval, '$'); //special food symbol
        specialFoodActive = true;
    }
}

objPos GameMechs::getSpecialFood() const
{
    return objPos();
}

objPos GameMechs::getFoodPos() const
{
    return food;
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;
}
    

char GameMechs::getInput() const
{
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score += 1;
    // implement change for bonus
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = '\0';
}

// More methods should be added here