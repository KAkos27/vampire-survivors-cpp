#include "game.hpp"
#include "entities/enemy_spawner.hpp"
#include "ui/level_up_event.hpp"
#include <raylib.h>

Game::Game() : player(400, 400), enemy_spawner(player), level_up_event(player) {
  state = PLAYING;
}

void Game::init_window() {
  InitWindow(800, 600, "Vampire Survivors");
  SetTargetFPS(60);
}

void Game::run_game() {
  init_window();

  while (!WindowShouldClose()) {
    check_for_input();

    BeginDrawing();
    {
      ClearBackground(BLACK);

      update_game();
      draw_game();
      update_level_up_event();
    }
    EndDrawing();
  }

  CloseWindow();
}

void Game::update_game() {
  if (state == PLAYING) {
    player.update_player(enemy_spawner.enemies);
    enemy_spawner.update_enemies();
    check_for_level_up();
  }
}

void Game::check_for_level_up() {
  if (player.leveled_up) {
    state = LEVEL_UP;
    player.leveled_up = false;
    level_up_event.set_event();
  }
}

void Game::update_level_up_event() {
  if (state == LEVEL_UP) {
    level_up_event.update_event();

    if (level_up_event.been_selected) {
      state = PLAYING;
    }
  }
}

void Game::draw_game() {
  player.draw_player();
  enemy_spawner.draw_enemies();
  DrawText(TextFormat("level: %d, %.2f/%.2f", player.experience.level,
                      player.experience.current,
                      player.experience.xp_to_next_level),
           10, 10, 20, GRAY);
  DrawText(TextFormat("hp: %.2f/%.2f\ndamage: %.2f\nspeed: %.2f",
                      player.stats.health.current, player.stats.health.max,
                      player.stats.damage, player.stats.speed),
           10, 40, 20, GRAY);
}

void Game::check_for_input() {
  if (IsKeyPressed(KEY_P)) {
    if (state == PLAYING) {
      state = PAUSED;
    } else {
      state = PLAYING;
    }
  }
}
