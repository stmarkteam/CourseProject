#include "../src/function.h"
#include "../src/map.h"
#include "../thirdparty/ctest.h"
#include "../src/function.cpp"

CTEST(win_game, event_win_game){
  int n = 1;
  int result = Collision(n);
  int expected = 7;
  ASSERT_EQUAL(expected, result);
}

CTEST(lose_game, lose_game_test){
  int n = 100;
  int result = Collision(n);
  int expected = 5;
  ASSERT_EQUAL(expected, result);
}
