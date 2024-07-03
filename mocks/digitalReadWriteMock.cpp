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
        return fakeReadingArray[pin - 1];
    }
    return 0;
}

void __decoy_digitalWrite(int writePin, int value) {
    if (value > 1) {
        value = 1;
    }
    if (value < 0) {
        value = 0;
    }
    if (writePin <= fakeReadingArraySize) {

    fakeReadingArray[writePin - 1 ] = value;

    }

}