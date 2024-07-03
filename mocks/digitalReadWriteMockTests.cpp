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
    - digitalWrite changes certain cell only
    - digitalread out of bounds -> does not crash or similar
    - digitalwrite with false values don't fail catastrophically but gets corrected to high if >1 and low if <0
    - what else?
    */ 

    CHECK_EQUAL(io_count, arraySize());

    for (int i = 1; i <= io_count; i++) {
        CHECK_EQUAL(LOW, digitalRead(i));
    }
    //int testArray[io_count] = { 0};
    //CHECK_EQUAL(testArray, arrayDump());
    //delete[] testArray;

    CHECK_EQUAL(LOW, digitalRead(5));
    //__decoy_digitalWrite(5,1);
    //CHECK_EQUAL(1, digitalWrite(5,1));
    __decoy_digitalWrite(5,HIGH);
    CHECK_EQUAL(HIGH, digitalRead(5));
    for (int i = 1; i <= io_count; i++) {
        if (i != 5) {
            CHECK_EQUAL(LOW, digitalRead(i));
        }
    }

    __decoy_digitalWrite(io_count + 5, HIGH); //writing above io_count to ensure there is nothing catastrophical happeningn

    __decoy_digitalWrite(10, 100);
    CHECK_EQUAL(HIGH, digitalRead(10));
    __decoy_digitalWrite(14, -100);
    CHECK_EQUAL(LOW, digitalRead(14));
}