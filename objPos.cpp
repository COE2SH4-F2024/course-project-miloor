#include "objPos.h"
#include <iostream>

objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; //NULL
}

objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Respect the rule of six / minimum four
// [TODO] Implement the missing special member functions to meet the minimum four rule

//destructor
objPos::~objPos() {
    delete pos;
    pos = nullptr;
}

//copy Constructor
objPos::objPos(const objPos& other) {
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;
}

//copy Assignment Operator
objPos& objPos::operator=(const objPos& other) {
    if (this == &other)
        return *this;

    delete pos; //delete previous 

    //copy data
    pos = new Pos;
    pos->x = other.pos->x;
    pos->y = other.pos->y;
    symbol = other.symbol;

    return *this;
}

void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    
    return returnPos;
}

char objPos::getSymbol() const
{
    return symbol;
}

bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if(isPosEqual(refPos))
        return symbol;
    else
        return 0;
}
