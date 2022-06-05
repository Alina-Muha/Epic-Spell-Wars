#include "dice.h"

namespace dice {

int roll_the_dice(int n) {
  int result = 0;
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> roll(1, 6 * n);
  for (int i = 0; i < n; i++) {
    result += roll(rng);
  }
  return result;
}
} // namespace dice
