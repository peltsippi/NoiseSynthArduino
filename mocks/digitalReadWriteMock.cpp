#include "digitalReadWriteMock.h"
#include <stdio.h>
#include <string.h>

//int *fakeReadingArray = malloc(int[]);
//int *fakeReadingArray;
int* fakeReadingArray = (int*) calloc(1,sizeof(int[0]));
int fakeReadingArraySize = 0;

/*
init by supplying array that tells what the digital reads are supposed to be. Then any queries will return based on this array.
*/



void digitalReadWriteMock_Create(int arr_size) {
    fakeReadingArraySize = arr_size;
    int* oldPtr = fakeReadingArray;
    fakeReadingArray = (int*) realloc(oldPtr, sizeof(int[arr_size]));
    memset(fakeReadingArray, 0 , arr_size);
}

void digitalReadWriteMock_Destroy() {
    
    free(fakeReadingArray);
    fakeReadingArraySize = 0;

}

int arraySize() {
    return fakeReadingArraySize;
}

int* arrayDump() {
    return &fakeReadingArray[0];
}

int digitalRead(int pin) {
    if (fakeReadingArraySize >= pin &&  pin > 0) {
    
    if (fakeReadingArray[pin - 1] < 0 || fakeReadingArray[pin-1] > 1) {
        return pin;
    }
    return fakeReadingArray[pin - 1];

    }
    return 0;
    //return 5;
}

void __decoy_digitalWrite(int writePin, int value) {

    if (writePin <= fakeReadingArraySize) {

    fakeReadingArray[writePin - 1 ] = value;

    }

    //return 1;

}