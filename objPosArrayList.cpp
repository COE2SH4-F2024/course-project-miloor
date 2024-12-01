#include "objPosArrayList.h"
#include <stdexcept>

// Paste your Tested implementation here.
// Paste your Tested implementation here.
// Paste your Tested implementation here.





int objPosArrayList::getSize() const 
{
    return size;
}

objPos objPosArrayList::getElement(int index) const 
{
    if (index < 0 || index >= static_cast<int>(elements.size())) {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}

// void objPosArrayList::addElement(const objPos& obj) {
//     elements.push_back(obj); // Add an element to the list
// }
