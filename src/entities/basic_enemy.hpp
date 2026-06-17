#pragma once

#include "enemy.hpp"
#include <raylib.h>

class BasicEnemy : public Enemy {

public:
  BasicEnemy(Player *player, float game_time, Vector2 spawn_position);
  void update_enemy() override;
  void take_damage(float damage) override;
  void draw_enemy() override;

private:
  Player *player;
  Color color;
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
