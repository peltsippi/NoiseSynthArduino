#ifndef DigitalReadWriteMock_H
#define DigitalReadWriteMock_H


#define HIGH 1
#define LOW 0

void digitalReadWriteMock_Create(int arr_size);

void digitalReadWriteMock_Destroy();

int digitalRead(int pin); 
void __decoy_digitalWrite(int writePin, int value);

int arraySize();
int* arrayDump();

#endif