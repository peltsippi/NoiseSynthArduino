#ifndef DigitalReadWriteMock_H
#define DigitalReadWriteMock_H

void digitalReadWriteMock_Create(int arr_size);

void digitalReadWriteMock_Destroy();

int digitalRead(int pin);

int digitalWrite(int pin, int value);

int arraySize();

#endif