#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList() : sizeList(0), sizeArray(200) {
    // Allocate memory for the array list and initialize elements
    aList = new objPos[sizeArray];
    for (int i = 0; i < sizeArray; i++){
        aList[i] = objPos();
    }
}

objPosArrayList::~objPosArrayList(){
    // Deallocate the array on heap
    delete[] aList;
}

void objPosArrayList::alterArray(int altCapacity){
    if (altCapacity <= sizeList){
        altCapacity = sizeList + 1;
    }

    // Create a new array with the updated capacity
    objPos* altList = new objPos[altCapacity];

    // Copy existing elements to the new array
    for (int i = 0; i < sizeList; i++){
        altList[i] = aList[i];
    }

    // Deallocate old array and update the pointer
    delete[] aList;
    aList = altList;
    sizeArray = altCapacity; // Update size of array 
}

int objPosArrayList::getSize(){
    return sizeList; // Return the number of elements in the list
}

void objPosArrayList::insertHead(objPos thisPos){
    // Resize array if necessary
    if (sizeList >= sizeArray){
        alterArray(sizeArray*2); 
    }

    // Create a new array to shift elements and insert the new head
    objPos* altList = new objPos[sizeArray];
    altList[0] = thisPos; // Insert the new element at the head

    // Shift existing elements
    for (int i = 0; i < sizeList; i++) {
        altList[i + 1] = aList[i];
    }

    // Replace old array with new array
    delete[] aList;
    aList = altList;
    sizeList++; // Increments size of list
}

void objPosArrayList::insertTail(objPos thisPos){
    // Add new element at the end of the list
    if (sizeList >= sizeArray) {
        alterArray(sizeArray * 2); 
    }
    aList[sizeList] = thisPos;
    sizeList++; // Increment list size
}

void objPosArrayList::removeTail() {
    if (sizeList > 0) {
        sizeList--; // Decrease the size, removing the last element/tail
    }
}

void objPosArrayList::removeHead() {
    // Shift elements to the left overwriting the head/first element
    if (sizeList > 0) {
        for (int i = 0; i < sizeList - 1; i++) {
            aList[i] = aList[i + 1];
        }
        sizeList--; // Decrease the size of list
    }
}
void objPosArrayList::getHeadElement(objPos &returnPos) {
    if (sizeList > 0) {
        returnPos = aList[0]; // Return the first element/head
    }
}

void objPosArrayList::getTailElement(objPos &returnPos){
    if (sizeList > 0) {
        returnPos = aList[sizeList - 1]; // Return the last element/tail
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index) {
    if (index >= 0 && index < sizeList) {
        returnPos = aList[index]; // Return the element at the specified index
    } else {
        returnPos = objPos(); // Return a default objPos if index is out of bounds
    }
    
}

