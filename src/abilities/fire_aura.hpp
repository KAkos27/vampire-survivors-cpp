#pragma once

#include "../entities/player.hpp"
#include "ability.hpp"
#include <vector>

class FireAura : public Ability {

public:
  FireAura(Player &player, bool unlocked);
  void update(std::vector<Enemy> &enemies) override;
  void draw() override;

private:
  Player &player;
  float radius;
  float damage_muliplier;
  float tick_time;
  void deal_damage(std::vector<Enemy> &enemies);
};
