#pragma once

#include "../entities/enemy.hpp"
#include <vector>

enum class AbilityId {
  BULLET,
  FIRE_AURA,
  METEOR,
  HEAL,
};

static const int MAX_ABILITY_LEVEL = 5;

class Ability {

public:
  const char *name;
  AbilityId id;
  bool is_unlocked;
  int level;
  virtual void update(std::vector<std::unique_ptr<Enemy>> &enemies) = 0;
  virtual void draw() = 0;
  virtual void upgrade() = 0;
  virtual ~Ability() = default;
};
