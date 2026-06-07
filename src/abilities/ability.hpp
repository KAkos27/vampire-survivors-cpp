#pragma once

#include "../entities/enemy.hpp"
#include <vector>

class Ability {

public:
  virtual void update(std::vector<Enemy> &enemies) {};
  virtual ~Ability() = default;
};
