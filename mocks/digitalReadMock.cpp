
#include "digitalReadMock.h"
#include<stdio.h>

int *fakeReadingArray;
int fakeReadingArraySize = 0;

/*
init by supplying array that tells what the digital reads are supposed to be. Then any queries will return based on this array.
*/



void digitalReadMock_Create(int arr_size, int *array) {
    int copyArray[arr_size];
    fakeReadingArraySize = arr_size;
    
    memcpy(&copyArray, &array, arr_size);
}

void digitalReadMock_Destroy() {
    

}


int digitalRead(int pin) {
    return 5;
}