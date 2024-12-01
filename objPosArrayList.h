#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include <vector>
#include "objPos.h"

class objPosArrayList
{
    private:
        std::vector<objPos> elements; 
        objPos* aList;
        int listSize;
        int arrayCapacity;
        int size;

    public:
        objPosArrayList();
        ~objPosArrayList();

        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
        void addElement(const objPos& obj); //optional
};

#endif