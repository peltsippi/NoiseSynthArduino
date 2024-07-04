#include "CppUTest/TestHarness.h"
#include "ReadMatrix.h"

/* 
This blob is for reading input matrixes


*/

int rows[8] = { 1, 3, 5, 7, 9, 11, 13, 15};
int rowCount = 8;
int cols[8] = { 30, 32, 34, 36, 38, 40, 42, 44};
int colCount = 8;

TEST_GROUP(ReadMatrix)
{
    void setup()
    {
        //mode: input pullup. So default reading is 1 for everything
        for (int i = 0; i < rowCount; i++) {
            digitalWrite(rows[i], 1);

        }

        for (int i = 0; i < colCount; i++) {

        }
        
    }

    void teardown()
    {
        delete[] rows;
        delete[] cols;
    }
};

TEST(ReadMatrix, something)
{
    //DOUBLES_EQUAL(10, GetdBValue(600,10,10),1);
}
