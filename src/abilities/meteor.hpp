#pragma once

#include "../entities/player.hpp"
#include "ability.hpp"
#include <vector>

struct MeteorCrater {
  Vector2 position;
  float duration;
  bool alive;
};

struct MeteorStats {
  float base_cooldown;
  float cooldown;
  float damage_multiplier;
  float crater_radius;
  float crater_damage_multiplier;
  float crater_duration;
  float base_crater_damage_tick_timer;
  float crater_damage_tick_timer;
};

class Meteor : public Ability {

public:
  Meteor(Player &player, bool unlocked);
  void update(std::vector<Enemy> &enemies) override;
  void draw() override;
  void upgrade() override;

private:
  Player &player;
  std::vector<MeteorCrater> craters;
  MeteorStats stats;
  void strike_meteor(std::vector<Enemy> &enemies);
  void deal_crater_damage(std::vector<Enemy> &enemies);
  void handle_crater_duration();
  void delete_dead_craters();
  MeteorStats get_current_stats();
  MeteorStats create_stats(float cooldown, float damage_multiplier,
                           float crater_radius, float crater_damage_multiplier,
                           float crater_duration,
                           float crater_damage_tick_timer);
};
