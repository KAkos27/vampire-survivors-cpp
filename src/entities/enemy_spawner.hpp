#pragma once

#include "enemy.hpp"
#include "player.hpp"
#include <vector>

class EnemySpawner {

public:
  EnemySpawner(Player &player);
  std::vector<Enemy> enemies;
  void update_enemies(float game_time);
  void draw_enemies();

private:
  Player &player;
  float spawn_timer;
  void spawn_enemies(float game_time);
  void separate_enemies();
  void delete_dead_enemies();
};
