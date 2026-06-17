#pragma once

#include "run.hpp"
#include <memory>
#include <raylib.h>

enum class GameState {
  ON_MAIN_MENU,
  RUN_STARTED,
};

class Game {

public:
  Game();
  void run_game();

private:
  std::unique_ptr<Run> run;
  GameState state;
  void new_run();
  void init_window();
  void handle_main_menu();
  void handle_current_run();
};
