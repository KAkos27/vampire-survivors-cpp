#pragma once

#include "../entities/player.hpp"
#include "ability.hpp"

class Heal : public Ability {

public:
  Heal(Player &player, bool unlocked);
  // void update(std::vector<Enemy> &enemies) override;
  // void draw() override;
  void upgrade() override;

private:
  Player &player;
};
