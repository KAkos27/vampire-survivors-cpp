#pragma once

#include "enemy.hpp"
#include "player.hpp"
#include <memory>
#include <raylib.h>
#include <vector>

class EnemySpawner {

public:
  EnemySpawner(Player &player);
  std::vector<std::unique_ptr<Enemy>> enemies;
  void update_enemies(float game_time, Camera2D camera);
  void draw_enemies();

private:
  Player &player;
  float spawn_timer;
  void spawn_enemies(float game_time, Camera2D camera);
  void separate_enemies();
  void delete_dead_enemies();
  Vector2 get_random_position(Camera2D camera);
};
