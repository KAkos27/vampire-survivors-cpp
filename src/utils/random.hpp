#pragma once

#include <algorithm>
#include <random>
#include <vector>

int random_int(int min, int max);

float random_float(float min, float max);

template <typename T> void shuffle_vector(std::vector<T> &vector) {
  static std::random_device rd;
  static std::mt19937 rng(rd());

  std::shuffle(vector.begin(), vector.end(), rng);
}
