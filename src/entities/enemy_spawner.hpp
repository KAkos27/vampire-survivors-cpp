#pragma once

#include "enemy.hpp"
#include "player.hpp"
#include <vector>

class EnemySpawner {

public:
  EnemySpawner(Player &player);
  std::vector<Enemy> enemies;
  void update_enemies();
  void draw_enemies();

private:
  Player &player;
  float spawn_timer;
  void spawn_enemies();
  void delete_dead_enemies();
};
