#include "CppUTest/TestHarness.h"

#include "game.h"
#include "fake_inject.h"

static int closed_sahre_point(bool write, int value)
{
  static int saved_value;
  if (write) return saved_value;
  return saved_value = value;
}

void set_points(int points)
{
  closed_sahre_point(false, points);
}

int dice_point_fake()
{
  return closed_sahre_point(true, 0);
}

TEST_GROUP(GameTestGroup)
{
};

TEST(GameTestGroup, FirstTest)
{
  set_points(3 + 1);
  SET_FAKE_INJECT(dice_point, dice_point_fake);
  CHECK_EQUAL(1, isWon());
  RESET_FAKE_INJECT(dice_point);
}

