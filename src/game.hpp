#pragma once

#include "run.hpp"
#include <memory>
#include <raylib.h>

class Game {

public:
  Game();
  void run_game();

private:
  std::unique_ptr<Run> run;
  void restart_run();
  void init_window();
};
