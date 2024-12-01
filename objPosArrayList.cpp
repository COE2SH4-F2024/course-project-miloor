#include "objPosArrayList.h"

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.

//constructor
objPosArrayList::objPosArrayList()
{
    listSize = 1;
    arrayCapacity = ARRAY_MAX_CAP;
    aList = new objPos[arrayCapacity];
}

//deconstructor
objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

//getSize
int objPosArrayList::getSize() const
{
    return listSize;
}

//assign thisPos to first element of aList
void objPosArrayList::insertHead(objPos thisPos)
{
    //shift elements 
    int i;
    for (i = listSize; i > 0; i--)
    {
        aList[i] = aList[i - 1];
    }

    //assign to first
    aList[0] = thisPos;
    listSize++;
}

//add thisPos to end of te list 
void objPosArrayList::insertTail(objPos thisPos)
{
    aList[listSize] = thisPos;
    listSize++;
}

//
void objPosArrayList::removeHead()
{
    for(int i = 0; i < listSize - 1; i++)
    {
        aList[i] = aList[i + 1];
    }
    listSize--;
}

void objPosArrayList::removeTail()
{
    listSize--;
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    return aList[index];
}

