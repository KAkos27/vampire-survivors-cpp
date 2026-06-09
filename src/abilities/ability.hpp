#pragma once

#include "../entities/enemy.hpp"
#include <vector>

enum AbilityId {
  BULLET,
  FIRE_AURA,
  METEOR,
};

class Ability {

public:
  const char *name;
  AbilityId id;
  bool is_unlocked;
  virtual void update(std::vector<Enemy> &enemies) {};
  virtual void draw() {};
  virtual ~Ability() = default;
};
