#include "CppUTest/TestHarness.h"
#include "DetectKeys.h"

/* 
This blob is for detecting keyboard keys

But how the info should be transferred to the main program?
What if this returns an array of buttons pressed? Would it make any sense?
Not optimal probably or not sure.

How to detect if key is not lifted between polling?

What if this returns an array of actual sounds? So it would process also released keys etc...

requires mock for digitalread and digitalwrite -> done
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
