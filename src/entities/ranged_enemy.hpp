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
  void update_enemy();
  void take_damage(float damage);
  void draw_enemy();

private:
  Player *player;
  Color color;
  std::vector<EnemyProjectile> projectiles;
  float range;
  float difficulity;
  float speed;
  float damage;
  float attack_timer;
  float hurt_timer;
  float projectile_speed;
  float projectile_radius;
  float shoot_timer;
  bool hurt;
  bool in_range;
  void follow_player();
  void check_for_in_range();
  void check_for_player_hit();
  void shoot();
  void flash_enemy();
  void set_stats();
  void update_projectiles();
  void draw_projectiles();
  void check_for_projectile_hit();
  void calculate_difficulity(float game_time);
  void delete_dead_projectiles();
};
