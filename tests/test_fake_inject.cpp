#include "CppUTest/TestHarness.h"

extern "C" {
#include "game.h"
}

TEST_GROUP(GameTestGroup)
{
};

TEST(GameTestGroup, FirstTest)
{
   FAIL("Fail me!");
}

