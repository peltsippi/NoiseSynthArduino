#include "CppUTest/TestHarness.h"
#include "DetectKeys.h"

/* 
This blob is for detecting keyboard keys

But how the info should be transferred to the main program?

How to detect if key is not lifted between polling?

requires mock for digitalread and digitalwrite
*/



TEST_GROUP(DetectKeys)
{
    void setup()
    {
    }

    void teardown()
    {
    }
};

TEST(DetectKeys, something)
{
    //DOUBLES_EQUAL(10, GetdBValue(600,10,10),1);
}
