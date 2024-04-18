#include "CppUTest/TestHarness.h"

#include "digitalReadMock.h"

TEST_GROUP(digitalReadMock)
{
    void setup()
    {
        digitalReadMock_Create();
    }

    void teardown()
    {
        digitalReadMock_Destroy();
    }
}