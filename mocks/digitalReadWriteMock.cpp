#include "digitalReadWriteMock.h"
#include <stdio.h>

int *fakeReadingArray;
int fakeReadingArraySize = 0;

/*
init by supplying array that tells what the digital reads are supposed to be. Then any queries will return based on this array.
*/



void digitalReadWriteMock_Create(int arr_size) {
    //int copyArray[arr_size];
    //fakeReadingArraySize = arr_size;
    //memcpy(&copyArray, &array, arr_size);
    //fakeReadingArray = &copyArray[0];
    int digitalReadArray[arr_size] = {0};
    fakeReadingArray = &digitalReadArray[0];
    fakeReadingArraySize = arr_size;

}

void digitalReadWriteMock_Destroy() {
    fakeReadingArraySize = 0;
    //delete[] fakeReadingArray;

}

int arraySize() {
    return fakeReadingArraySize;
}

int digitalRead(int pin) {
    return fakeReadingArray[pin];
    //return 5;
}

int digitalWrite(int pin, int value) {

    return 1;

}