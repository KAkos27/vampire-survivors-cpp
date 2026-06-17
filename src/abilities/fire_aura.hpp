#pragma once

#include "../entities/player.hpp"
#include "ability.hpp"
#include <vector>

struct FireAuraStats {
  float radius;
  float damage_muliplier;
  float base_tick_time;
  float tick_time;
};

class FireAura : public Ability {

public:
  FireAura(Player &player, bool unlocked);
  void update(std::vector<std::unique_ptr<Enemy>> &enemies) override;
  void draw() override;
  void upgrade() override;

private:
  Player &player;
  FireAuraStats stats;
  void deal_damage(std::vector<std::unique_ptr<Enemy>> &enemies);
  FireAuraStats get_current_stats();
  FireAuraStats create_stats(float radius, float damage_muliplier,
                             float tick_time);
};
