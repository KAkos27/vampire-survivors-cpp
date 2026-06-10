#pragma once

#include "entities/enemy_spawner.hpp"
#include "entities/player.hpp"
#include "ui/level_up_event.hpp"
#include <raylib.h>

const float BASE_RUN_TIME = 30 * 60;

enum RunState {
  PLAYING,
  LEVEL_UP,
  PAUSED,
};

class Run {

public:
  Run();
  ~Run();
  bool acitve();

private:
  Player player;
  EnemySpawner enemy_spawner;
  LevelUpEvent level_up_event;
  Camera2D camera;
  RunState state;
  Texture2D background_tile;
  float run_time;
  void check_for_level_up();
  void check_for_input();
  void update_run();
  void draw_run();
  void update_level_up_event();
};
