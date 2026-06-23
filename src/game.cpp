#include "game.hpp"
#include "levels/base_level.hpp"
#include "raygui.h"
#include <memory>
#include <raylib.h>

Game::Game() { state = GameState::ON_MAIN_MENU; }

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

  while (!WindowShouldClose()) {
    BeginDrawing();
    {
      ClearBackground(BLACK);
      handle_current_run();
      handle_main_menu();
    }
    EndDrawing();
  }

  CloseWindow();
}

void Game::new_run() { run = std::make_unique<Run>(BaseLevel()); }

void Game::handle_current_run() {
  if (state != GameState::RUN_STARTED) {
    return;
  }

  if (!run->acitve()) {
    state = GameState::ON_MAIN_MENU;
  }
}

void Game::handle_main_menu() {
  if (state != GameState::ON_MAIN_MENU) {
    return;
  }

  const float width = 720;
  const float height = 72;

  const float centerX = (GetScreenWidth() / 2.0) - (width / 2.0);
  const float centerY = (GetScreenHeight() / 2.0) - (height / 2.0);

  bool clicked = GuiButton({centerX, centerY, width, height}, "Play");

  if (clicked) {
    new_run();
    state = GameState::RUN_STARTED;
  }
}
