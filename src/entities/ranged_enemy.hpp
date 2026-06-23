#pragma once

#include "enemy.hpp"
#include <raylib.h>
#include <vector>

struct EnemyProjectile {
  Vector2 position;
  Vector2 velocity;
  float life_time;
  bool alive;
};

class RangedEnemy : public Enemy {

public:
  RangedEnemy(Player *player, float game_time, Vector2 spawn_position);
  void update_enemy() override;
  void draw_enemy() override;

private:
  std::vector<EnemyProjectile> projectiles;
  float range;
  float projectile_speed;
  float projectile_radius;
  float shoot_timer;
  bool in_range;
  void follow_player() override;
  void check_for_in_range();
  void shoot();
  void update_projectiles();
  void draw_projectiles();
  void check_for_projectile_hit();
  void delete_dead_projectiles();
};
