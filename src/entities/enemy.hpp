#pragma once

#include <raylib.h>

class Player;

struct EnemyHealth {
  float current;
  float max;
};

class Enemy {

public:
  Enemy(Player *player, float game_time, Vector2 spawn_position);

  Vector2 position;
  EnemyHealth health;
  bool alive;
  float collider_radius;
  float xp_drop;

  virtual void update_enemy() = 0;
  virtual void draw_enemy();
  virtual void take_damage(float damage);
  virtual ~Enemy() = default;

protected:
  Player *player;
  Color color;
  Color base_color;
  float speed;
  float difficulity;
  float damage;
  float attack_timer;
  float hurt_timer;
  bool hurt;

  virtual void follow_player();
  void calculate_difficulity(float game_time);
  void check_for_player_hit();
  void flash_enemy();
};
