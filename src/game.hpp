#pragma once
#include "entities/enemy_spawner.hpp"
#include "entities/player.hpp"
#include "ui/level_up_event.hpp"
#include <raylib.h>

const float BASE_GAME_TIME = 60 * 30;

enum GameState {
  PLAYING,
  LEVEL_UP,
  PAUSED,
};

class Game {

public:
  GameState state;
  Game();
  float game_time;
  void run_game();

private:
  Player player;
  EnemySpawner enemy_spawner;
  LevelUpEvent level_up_event;
  Camera2D camera;
  void init_window();
  void check_for_level_up();
  void check_for_input();
  void update_game();
  void update_level_up_event();
  void draw_game();
};
