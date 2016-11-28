#Fake Inject
-----------------------------

## A Fake Function Inject Assistant for C
Fake inject is a assistant tool for the fake function replacement during unit test. So that it can be easier to replace the dependancy with test double.

## Hello, fake inject!

Say you have such production code.

```C
//dice.c
#include <stdio.h>
#include "dice.h"
#include <stdlib.h>

int dice_point()
{
	srand(time(NULL));
	int r = ( rand() % 6 ) + 1;
	return r;
}

int isWin()
{
	int points = dice_point();
	if (points > 3){
		return TRUE;
	}
	return FALSE;
}
```
If you would like to test the function `isWin()`, but it depends on the function `dice_point()` which will generate the random number, it's hard to be tested. There is a way to write a fake function of `dice_point()` which is called `dice_point_fake()`
```C
int g_points;
void set_points(int points)
{
    g_points = points;
}
int dice_point_fake()
{
    return g_points;
}
```

So basic replace the `dice_point` with `dice_point_fake` is:
```C
...
#include "fake_inject.h"
...
TEST(DiceTest, GivenDiceWhenPointBiggerThanThreeShallWin)
{
	set_points(3 + 1);
	SET_INJECT_FAKE(dice_point, dice_point_fake);
	CHECK_EQUAL(1, isWin());
	RESET_INJECT_FAKE(dice_point);
}
```

## Cheat Sheet
<table>
    <tr>
        <th>Macro</th>
        <th>Description</th>
        <th>Example</th>
    </tr>
    <tr>
        <td>SET_INJECT_FAKE(function_name, fake_name);</td>
        <td>Use fake function call replace original real function call.</td>
        <td>SET_INJECT_FAKE(dice_point, dice_point_fake);</td>
    </tr>
    <tr>
        <td>RESET_INJECT_FAKE(function_name);</td>
        <td>Reset the fake function to original real function.</td>
        <td>RESET_INJECT_FAKE(dice_point);</td>
    </tr>
</table>
