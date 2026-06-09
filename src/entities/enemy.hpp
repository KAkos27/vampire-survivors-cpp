#pragma once

#include <raylib.h>

class Player;

struct EnemyHealth {
  float current;
  float max;
};

class Enemy {

public:
  Enemy(Player *player);
  Vector2 position;
  EnemyHealth health;
  bool alive;
  float collider_radius;
  float xp_drop;
  void update_enemy();
  void take_damage(float damage);
  void draw_enemy();

private:
  Player *player;
  Color color;
  float speed;
  bool hurt;
  float hurt_timer;
  void follow_player();
  void check_for_player_hit();
  void flash_enemy();
};
