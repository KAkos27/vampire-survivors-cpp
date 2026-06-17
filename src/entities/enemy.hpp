#pragma once

#include <raylib.h>

class Player;

enum class EnemyType {
  WEAK,
  STRONG,
  BOSS,
};

struct EnemyHealth {
  float current;
  float max;
};

class Enemy {

public:
  Enemy(Player *player, float game_time, Vector2 spawn_position,
        EnemyType type);
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
  EnemyType type;
  float difficulity;
  float speed;
  float damage;
  float attack_timer;
  float hurt_timer;
  bool hurt;
  void follow_player();
  void check_for_player_hit();
  void flash_enemy();
  void set_stats();
  void calculate_difficulity(float game_time);
};
