#pragma once

#include "../entities/player.hpp"
#include "ability.hpp"
#include <vector>

struct MeteorCrater {
  Vector2 position;
  float duration;
  bool alive;
};

class Meteor : public Ability {

public:
  Meteor(Player &player, bool unlocked);
  void update(std::vector<Enemy> &enemies) override;
  void draw() override;

private:
  Player &player;
  std::vector<MeteorCrater> craters;
  float cooldown;
  float damage_multiplier;
  float crater_radius;
  float crater_damage_multiplier;
  float crater_duration;
  float crater_damage_tick_timer;
  void strike_meteor(std::vector<Enemy> &enemies);
  void deal_crater_damage(std::vector<Enemy> &enemies);
  void handle_crater_duration();
  void delete_dead_craters();
};
