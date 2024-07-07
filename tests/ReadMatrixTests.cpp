#include "../include/ReadMatrix.h"
#include "../mocks/digitalReadWriteMock.h"
#include "CppUTest/TestHarness.h"

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


TEST(ReadMatrix, OutputArrayAfterInit) {

     //let's just use 1d array instead! arr[999]
    //referenced by arr[colNumber * rowCount + rowNumber] ?!?!
    int* arrPtr = ReadMatrix(rowCount, rows, colCount, cols);

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            if (i != j) { //when working correctly this probably works like this or not?!?
                CHECK_EQUAL(1, arrPtr[j*rowCount + i]);
            }
        }

    }
    

}

TEST(ReadMatrix, manipulated) {

    //column set to low -> there should be only single zero in whole array if there is no input

}

    /*int* ptr = ReadMatrix(rowCount, rows, colCount, cols);

    for (int j = 0; j < colCount; j++) {
        for (int i = 0; i < rowCount; i++) {
            CHECK_EQUAL(HIGH, ptr[i + j * rowCount]);
        }
    }*/

 //  CHECK_EQUAL(HIGH, testfunc(1));

    //int **testArr = ReadMatrix(rowCount, rows, colCount, cols);
    //int *ptr[rowCount][colCount]
    //ptr = &testArr;
    //ptr = (int*) testArr;

    //CHECK_EQUAL(HIGH, *ptr);

    //int *testArr[rowCount] = ReadMatrix(rowCount, rows, colCount, cols);
    //int *testArr[rowCount][colCount];
    //testArr = ReadMatrix(rowCount, rows, colCount, cols);

    /*for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            CHECK_EQUAL(HIGH, testArr[i][j]);
        }
    }*/
    
    /*int *arr[rowCount][colCount] = ReadMatrix(rowCount, rows, colCount, cols);

    for (int i = 0; i < rowCount; i++) {
        for (int j= 0; j < colCount; j++ ) {
            CHECK_EQUAL(HIGH, arr[i][j]);
        }
    }*/
    
   //int num = TestMatrix(rowCount, rows, colCount, cols);
   //CHECK_EQUAL(50, TestMatrix(rowCount, rows, colCount, cols));
   
//
