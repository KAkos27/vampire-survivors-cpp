#pragma once

#include <raylib.h>

class Player;

struct EnemyHealth {
  float current;
  float max;
};

class Enemy {

public:
  Vector2 position;
  EnemyHealth health;
  bool alive;
  float collider_radius;
  float xp_drop;
  virtual void update_enemy() = 0;
  virtual void draw_enemy() = 0;
  virtual void take_damage(float damage) = 0;
  virtual ~Enemy() = default;
};
