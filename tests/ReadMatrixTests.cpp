#include "../include/ReadMatrix.h"
//#include "../mocks/Arduino.h"
#include "../mocks/digitalReadWriteMock.h"
#include "CppUTest/TestHarness.h"

//#define digitalRead(a) FakedigitalRead(a)
//#define digitalWrite(a,b) FakedigitalWrite(a,b)
//#define delay(a) FakeDelay(a);

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
const int rowCount = sizeof(rows) / sizeof(rows[0]);
int cols[8] = { 30, 32, 34, 36, 38, 40, 42, 44};
//int colCount = 8;
const int colCount = sizeof(cols) / sizeof(cols[0]);

const int arrSize = rowCount * colCount;
int readArray[arrSize] = {0};

//void Delay(int a) {} //this probably needs clock mock or similar at some point?!

TEST_GROUP(ReadMatrix)
{
    void init() {
        for (int i = 0; i < rowCount; i++) {
            digitalWrite(rows[i], HIGH);
        }

        for (int i = 0; i < colCount; i++) {
            digitalWrite(cols[i], HIGH);
        }
    }
    void setup()
    {
        digitalReadWriteMock_Create(54);
        
        //mode: input pullup. So default reading is 1 for everything
        init();
        
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
}


TEST(ReadMatrix, OutputArrayAfterInit) {


    /*
    No way thins can be comprehended without this table. One col at a time
    is set 0 and if button is pressed, accompanying row reads out as 0 also..
    
            col1        col2        col3        col4        col 5.....
    row1    A[0] = 1    A[8]  = 1    A[16] = 1  A]24] = 1   A[32] = 1
    row2    A[1] = 1    A[9]  = 1    A[17] = 1  A[25] = 1   .....
    row3    A]2] = 1    A[10] = 1    A[18] = 1  A[26] = 1   ...
    row4    A[3] = 1    A[11] = 1    A[19] = 1  A[27] = 1
    row5    A[4] = 1    A[12] = 1    A[20] = 1  A[28] = 1
    row6    A[5] = 1    A[13] = 1    A[21] = 1  A[29] = 1
    row7    A]6} = 1    A[14] = 1    A[22] = 1  A[30] = 1
    row8    A[7] = 1    A[15] = 1    A[23] = 1  A[31] = 1
    */
    //init();
    //int* arrPtr = ReadMatrix(rowCount, rows, colCount, cols);

    //int readArray[arrSize] = {0};
    //init();
    //int testArray[arrSize] = {0};
    init();

    ReadMatrix(readArray, rowCount, rows, colCount, cols);

    for (int i = 0; i < rowCount; i++) {
        for (int j = 0; j < colCount; j++) {
            int index = j*rowCount + i;
            CHECK_EQUAL(HIGH, readArray[index]);
        }

    }
    

}

TEST(ReadMatrix, manipulated1) {

        /*
    No way thins can be comprehended without this table. One col at a time
    is set 0 and if button is pressed, accompanying row reads out as 0 also..
    
            col1        col2        col3        col4        col 5.....
    row1    A[0] = 1    A[8]  = 1    A[16] = 1  A]24] = 1   A[32] = 1
    row2    A[1] = 1    A[9]  = 1    A[17] = 1  A[25] = 1   .....
    row3    A]2] = 1    A[10] = 1    A[18] = 1  A[26] = 1   ...
    row4    A[3] = 1    A[11] = 1    A[19] = 1  A[27] = 1
    row5    A[4] = 1    A[12] = 1    A[20] = 1  A[28] = 1
    row6    A[5] = 1    A[13] = 1    A[21] = 1  A[29] = 1
    row7    A]6} = 1    A[14] = 1    A[22] = 1  A[30] = 1
    row8    A[7] = 1    A[15] = 1    A[23] = 1  A[31] = 1
    */
   //row 4 selected and toggled fixed, let's see what happens
    init(); //clear any previous residues
    int selectedRow = 4;
    selectedRow--; //just to make this more readable row 4 which translates to 3 in array
    digitalWrite(rows[selectedRow], LOW);

    ReadMatrix(readArray, rowCount, rows, colCount, cols);

    for (int i = 0; i < rowCount; i++) {
        bool match = (i == selectedRow);
        int value = 1;
        if (match)  {
            value = 0;
        }
    for (int j = 0; j < rowCount; j++) {
        int index = j*rowCount + i;
        CHECK_EQUAL(value, readArray[index]);
    }
    }
}

    TEST(ReadMatrix, manipulated2) {
    init();
    int selectedRow = 6; //next row and continue
    selectedRow--; 
    digitalWrite(rows[selectedRow], LOW);

    ReadMatrix(readArray, rowCount, rows, colCount, cols);
    for (int i = 0; i < rowCount; i++) {
        bool match = (i == selectedRow);
        int value = 1;
        if (match)  {
            value = 0;
        }
    for (int j = 0; j < rowCount; j++) {
        int index = j*rowCount + i;
        CHECK_EQUAL(value, readArray[index]);
    }
    }


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
