#include "CppUTest/TestHarness.h"
#include "digitalReadWriteMock.h"
//#include "/home/timo/.arduino15/packages/arduino/hardware/avr/1.8.6/cores/arduino/Arduino.h"

//#define digitalRead(a) FakedigitalRead(a)
//#define digitalWrite(a,b) FakedigitalWrite(a,b)


int io_count = 54;
//is there some variable that would be based on microcontroller? Mega : 54 digital io

TEST_GROUP(digitalReadWriteMock)
{
    void setup()
    {
        digitalReadWriteMock_Create(io_count); 
        //UT_PTR_SET(digitalRead, FakedigitalRead);
        //UT_PTR_SET(digitalWrite, FakedigitalWrite);
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

    CHECK_EQUAL(LOW, digitalRead(5));
    digitalWrite(5,HIGH);
    CHECK_EQUAL(HIGH, digitalRead(5));
    for (int i = 1; i <= io_count; i++) {
        if (i != 5) {
            CHECK_EQUAL(LOW, digitalRead(i));
        }
    }

    //writing above io_count to ensure there is nothing catastrophical happeningn
    digitalWrite(io_count + 5, HIGH); 

    //write excessive numbers to digital input
    digitalWrite(10, 100); 
    CHECK_EQUAL(HIGH, digitalRead(10));
    digitalWrite(14, -100);
    CHECK_EQUAL(LOW, digitalRead(14));
}