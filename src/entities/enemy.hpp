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
  void update_enemy();
  void take_damage(float damage);

private:
  Player *player;
  float speed;
  void follow_player();
  void check_for_player_hit();
};
