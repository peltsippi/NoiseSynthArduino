#include "CppUTest/TestHarness.h"
#include "ReadMatrix.h"
#include "digitalReadWriteMock.h"

#define digitalRead(a) FakedigitalRead(a);
#define digitalWrite(a,b) FakedigitalWrite(a,b);

/* 
This blob is for reading input matrixes


*/
//int io_count = 54;

int rows[8] = { 1, 3, 5, 7, 9, 11, 13, 15};
int rowCount = 8;
int cols[8] = { 30, 32, 34, 36, 38, 40, 42, 44};
int colCount = 8;

TEST_GROUP(ReadMatrix)
{
    void setup()
    {
        digitalReadWriteMock_Create(54);
        //UT_PTR_SET(digitalRead, FakedigitalRead);
        //UT_PTR_SET(digitalWrite, FakedigitalWrite);
        //mode: input pullup. So default reading is 1 for everything
        for (int i = 0; i < rowCount; i++) {
            digitalWrite(rows[i], 1);

        }

        for (int i = 0; i < colCount; i++) {

        }
        
    }

    void teardown()
    {
        //delete[] rows;
        //delete[] cols;
        digitalReadWriteMock_Destroy();
    }
};

TEST(ReadMatrix, something)
{
    //DOUBLES_EQUAL(10, GetdBValue(600,10,10),1);
}
