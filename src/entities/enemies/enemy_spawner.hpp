#pragma once

#include "../../levels/base_level.hpp"
#include "../player.hpp"
#include "enemy.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

class EnemySpawner {

public:
  EnemySpawner(Player &player, BaseLevel &level);
  std::vector<std::unique_ptr<Enemy>> enemies;
  std::vector<std::unique_ptr<Item>> dropped_items;
  void update_enemies(float game_time, Camera2D camera, float run_time);
  void draw_enemies();

private:
  Player &player;
  BaseLevel &level;
  float spawn_timer;
  void spawn_enemies(float game_time, Camera2D camera, float run_time);
  void separate_enemies();
  void delete_dead_enemies();
  std::unique_ptr<Enemy> create_boss(BossID boss_id, float game_time,
                                     Vector2 spawn_position);
  Vector2 get_random_position(Camera2D camera);
};
