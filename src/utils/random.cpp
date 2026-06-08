#include "random.hpp"
#include <random>

int random_int(int min, int max) {
  static std::random_device rd;
  static std::mt19937 rng(rd());

  std::uniform_int_distribution<int> dist(min, max);
  return dist(rng);
}
