#include "game.hpp"
#include <memory>
#include <raylib.h>

Game::Game() {}

void Game::init_window() {
  // const int monitor = GetCurrentMonitor();
  // const int screen_width = GetMonitorWidth(monitor);
  // const int screen_height = GetMonitorHeight(monitor);

  const int screen_width = 900;
  const int screen_height = 600;

  InitWindow(screen_width, screen_height, "Vampire Survivors");
  SetTargetFPS(60);
}

void Game::run_game() {
  init_window();
  run = std::make_unique<Run>();

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(BLACK);

      if (!run->acitve()) {
        restart_run();
      }
    }
    EndDrawing();
  }

  CloseWindow();
}

void Game::restart_run() { run = std::make_unique<Run>(); }
