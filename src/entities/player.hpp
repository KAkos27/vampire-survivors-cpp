#pragma once

#include "../abilities/ability.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

struct Experience {
  int level;
  float current;
  float xp_to_next_level;
};

struct PlayerHealth {
  float current;
  float max;
};

struct Stats {
  float base_health;
  float base_damage;
  float base_speed;

  PlayerHealth health;
  float damage;
  float speed;
};

class Player {

public:
  Player(float x, float y);
  Vector2 position;
  Experience experience;
  Stats stats;
  std::vector<std::unique_ptr<Ability>> abilities;
  bool leveled_up;
  bool is_alive;
  float collider_radius;
  void update_player(std::vector<std::unique_ptr<Enemy>> &enemies);
  void draw_player();
  void draw_abilities();
  void gain_xp(float amount);
  void take_damage(float amount);
  void heal(float amoutn);
  void upgrade_ability(AbilityId);
  Ability *get_ability(AbilityId);

private:
  void set_input_position();
  void update_abilities(std::vector<std::unique_ptr<Enemy>> &enemies);
  void init_stats(float health, float damage, float speed);
  void update_stats();
};
