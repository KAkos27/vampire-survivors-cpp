#pragma once
#include "entities/enemy_spawner.hpp"
#include "entities/player.hpp"

class Game {

public:
  Game();
  void run_game();

private:
  void init_window();
  Player player;
  EnemySpawner enemy_spawner;
};
