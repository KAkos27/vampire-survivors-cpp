#pragma once

#include "../entities/player.hpp"
#include "ability.hpp"

class Heal : public Ability {

public:
  Heal(Player &player, bool unlocked);
  void update(std::vector<std::unique_ptr<Enemy>> &enemies) override;
  void draw() override;
  void upgrade() override;

private:
  Player &player;
  float heal_amount;
};
