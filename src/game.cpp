#include "game.hpp"
#include "entities/enemy_spawner.hpp"
#include "entities/player.hpp"
#include "ui/level_up_event.hpp"
#include <raylib.h>

Game::Game() : player(400, 400), enemy_spawner(player), level_up_event(player) {
  state = PLAYING;
  game_time = BASE_GAME_TIME;
  camera = Camera2D();
}

void Game::init_window() {
  const int screen_width = 800;
  const int screen_height = 600;

  InitWindow(screen_width, screen_height, "Vampire Survivors");
  SetTargetFPS(60);

  camera.target = (Vector2){player.position.x, player.position.y};
  camera.offset = (Vector2){screen_width / 2.0f, screen_height / 2.0f};
  camera.zoom = 1.0f;
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
  camera.target = (Vector2){player.position.x, player.position.y};

  if (state == PLAYING) {
    float delta = GetFrameTime();
    game_time -= delta;

    player.update_player(enemy_spawner.enemies);
    enemy_spawner.update_enemies(game_time);
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
  BeginMode2D(camera);
  {
    player.draw_player();
    enemy_spawner.draw_enemies();
  }
  EndMode2D();

  int minutes = static_cast<int>(game_time) / 60;
  int seconds = static_cast<int>(game_time) % 60;

  DrawText(TextFormat("%02d:%02d", minutes, seconds), 300, 10, 20, GRAY);
  DrawText(TextFormat("level: %d, %.2f/%.2f", player.experience.level,
                      player.experience.current,
                      player.experience.xp_to_next_level),
           10, 10, 20, GRAY);
  DrawText(TextFormat("hp: %.2f/%.2f\ndamage: %.2f\nspeed: %.2f",
                      player.stats.health.current, player.stats.health.max,
                      player.stats.damage, player.stats.speed),
           10, 40, 20, GRAY);
  float gap = 10;
  for (auto &ability : player.abilities) {
    if (ability->is_unlocked) {
      DrawText(TextFormat("%s: %d", ability->name, ability->level), 600, gap,
               20, GRAY);
      gap += 20;
    }
  }
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
