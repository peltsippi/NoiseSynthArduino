#include "CppUTest/TestHarness.h"
#include "../include/ReadMatrix.h"
//#include "../include/ReadMatrix.h"
#include "../mocks/digitalReadWriteMock.h"

#define digitalRead(a) FakedigitalRead(a)
#define digitalWrite(a,b) FakedigitalWrite(a,b)

/* 
Testing logic:

Initially everything sets to 1 (this is being handled correctly by the hardware normally)

Flipping intentionally one IO does not affect others
HIGH means not detected and LOW means detected
This might be really tricky, it needs to be hooked up somehow during function execution?!?

Output makes sense somehow
Output is absolutely correct

What else?

*/
//int io_count = 54;

int rows[8] = { 1, 3, 5, 7, 9, 11, 13, 15};
//int rowCount = 8;
int rowCount = sizeof(rows) / sizeof(rows[0]);
int cols[8] = { 30, 32, 34, 36, 38, 40, 42, 44};
//int colCount = 8;
int colCount = sizeof(cols) / sizeof(cols[0]);

TEST_GROUP(ReadMatrix)
{
    void setup()
    {
        digitalReadWriteMock_Create(54);
        
        //mode: input pullup. So default reading is 1 for everything
        for (int i = 0; i < rowCount; i++) {
            digitalWrite(rows[i], HIGH);
        }

        for (int i = 0; i < colCount; i++) {
            digitalWrite(cols[i], HIGH);
        }
        
    }

    void teardown()
    {
        //delete[] rows;
        //delete[] cols;
        digitalReadWriteMock_Destroy();
    }
};

TEST(ReadMatrix, init_ok)
{
    for (int i = 0; i < rowCount; i++) {
        CHECK_EQUAL(HIGH, digitalRead(rows[i]));
    }
    for (int i = 0; i < colCount; i++) {
         CHECK_EQUAL(HIGH, digitalRead(cols[i]));
    }
    //DOUBLES_EQUAL(10, GetdBValue(600,10,10),1);
}


TEST(ReadMatrix, OutputArray) {

    //int *testArr[rowCount] = ReadMatrix(rowCount, rows, colCount, cols);

    
    /*int *arr[rowCount][colCount] = ReadMatrix(rowCount, rows, colCount, cols);

    for (int i = 0; i < rowCount; i++) {
        for (int j= 0; j < colCount; j++ ) {
            CHECK_EQUAL(HIGH, arr[i][j]);
        }
    }*/
    
   //int num = TestMatrix(rowCount, rows, colCount, cols);
   //CHECK_EQUAL(50, TestMatrix(rowCount, rows, colCount, cols));
   
}
