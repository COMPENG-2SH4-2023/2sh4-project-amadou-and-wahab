#include "objPosArrayList.h"

// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.
// Paste your CUTE Tested implementation here.

objPosArrayList::objPosArrayList() : sizeList(0), sizeArray(200) {
    aList = new objPos[sizeArray];
    for (int i = 0; i < sizeArray; i++){
        aList[i] = objPos();
    }
}

objPosArrayList::~objPosArrayList(){
    delete[] aList;
}

void objPosArrayList::alterArray(int altCapacity){
    if (altCapacity <= sizeList){
        altCapacity = sizeList + 1;
    }

    objPos* altList = new objPos[altCapacity];

    for (int i = 0; i < sizeList; i++){
        altList[i] = aList[i];
    }

    delete[] aList;
    aList = altList;
    sizeArray = altCapacity;
}

int objPosArrayList::getSize(){
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos){
    if (sizeList >= sizeArray){
        alterArray(sizeArray*2); 
    }
    objPos* altList = new objPos[sizeArray];

    altList[0] = thisPos;

    for (int i = 0; i < sizeList; i++) {
        altList[i + 1] = aList[i];
    }

    delete[] aList;
    aList = altList;
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos){
    if (sizeList >= sizeArray) {
        alterArray(sizeArray * 2); 
    }
    aList[sizeList] = thisPos;
    sizeList++;
}

void objPosArrayList::removeHead() {
    if (sizeList > 0) {
        for (int i = 0; i < sizeList - 1; i++){
            aList[i] = aList[i+1];
        }
        sizeList--;
    }
}

void objPosArrayList::removeTail() {
    if (sizeList > 0) {
        sizeList--;
    }
}

void objPosArrayList::getHeadElement(objPos &returnPos) {
    if (sizeList > 0) {
        returnPos = aList[0];
    }
}

void objPosArrayList::getTailElement(objPos &returnPos){
    if (sizeList > 0) {
        returnPos = aList[sizeList - 1];
    }
}

void objPosArrayList::getElement(objPos &returnPos, int index) {
    if (index >= 0 && index < sizeList) {
        returnPos = aList[index];
    } else {
        returnPos = objPos(); 
    }
}

