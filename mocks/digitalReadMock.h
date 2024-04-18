#ifndef DigitalReadMock_H
#define DigitalReadMock_H

void digitalReadMock_Create(int arr_size, int *array);

void digitalReadMock_Destroy();

int digitalRead(int pin);


#endif