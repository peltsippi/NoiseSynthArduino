#ifndef DigitalReadWriteMock_H
#define DigitalReadWriteMock_H

#include "../include/Arduino.h"

//#define HIGH 1
//#define LOW 0

void digitalReadWriteMock_Create(int arr_size);

void digitalReadWriteMock_Destroy();

int FakedigitalRead(int pin); 
int digitalRead(int pin); //for some reason Arduino.h import is not working...
void FakedigitalWrite(int writePin, int value);
void digitalWrite(int writePin, int value);

int arraySize();

#endif