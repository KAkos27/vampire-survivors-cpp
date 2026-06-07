#include "game.hpp"
#include "entities/enemy_spawner.hpp"

Game::Game() : player(400, 400), enemy_spawner(player) {}

void Game::init_window() {
  InitWindow(800, 600, "Vampire Survivors");
  SetTargetFPS(60);
}

void Game::run_game() {
  init_window();

  while (!WindowShouldClose()) {

    BeginDrawing();

    ClearBackground(BLACK);
    enemy_spawner.update_enemies();
    player.update_player(enemy_spawner.enemies);

    EndDrawing();
  }

  CloseWindow();
}
