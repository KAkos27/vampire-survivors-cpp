#pragma once

#include "../abilities/ability.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

class Enemy;

class Player {

public:
  Player(float x, float y);
  Vector2 position;
  float damage;
  float collider_radius;
  void update_player(std::vector<Enemy> &enemies);

private:
  std::vector<std::unique_ptr<Ability>> abilities;
  float speed;
  void set_input_position();
  void update_abilities(std::vector<Enemy> &enemies);
};
