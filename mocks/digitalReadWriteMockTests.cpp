#include "CppUTest/TestHarness.h"
#include "digitalReadWriteMock.h"

int io_count = 54;

TEST_GROUP(digitalReadWriteMock)
{
    void setup()
    {
        digitalReadWriteMock_Create(io_count); //is there some variable that would be based on microcontroller? Mega : 54 digital io
    }

    void teardown()
    {
        digitalReadWriteMock_Destroy();
    }
};

TEST(digitalReadWriteMock, init) {
    /*
    How to test this?
    - initialises completely as 0
    - array size is correct
    - array size limits something?
    - digitalWrite changes certain cell only
    - what else?
    */
    CHECK_EQUAL(io_count, arraySize());
    CHECK_EQUAL(0, digitalRead(5));
    CHECK_EQUAL(1, digitalWrite(5,1));
    CHECK_EQUAL(1, digitalRead(5));
}