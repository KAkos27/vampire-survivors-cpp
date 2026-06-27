#include "run.hpp"
#include "../entities/enemies/enemy_spawner.hpp"
#include "../entities/player.hpp"
#include "../levels/base_level.hpp"
#include "level_up_event.hpp"
#include <raylib.h>

Run::Run(BaseLevel level)
    : run_level(level),
      player(Player(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f)),
      enemy_spawner(EnemySpawner(player, run_level)),
      level_up_event(LevelUpEvent(player)) {

  level_up_view = LevelUpView();

  run_time = BASE_RUN_TIME;
  state = RunState::PLAYING;

  camera = Camera2D();
  camera.target = {player.position.x, player.position.y};
  camera.offset = {GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f};
  camera.zoom = 1.0f;

  background_tile = LoadTexture("../assets/floor.png");
}

Run::~Run() { UnloadTexture(background_tile); }

bool Run::acitve() {
  check_for_input();
  update_run();
  draw_run();
  update_level_up_event();

  return player.is_alive;
}

void Run::update_run() {
  camera.target = {player.position.x, player.position.y};

  if (state == RunState::PLAYING) {
    float delta = GetFrameTime();
    run_time -= delta;

    player.update_player(enemy_spawner.enemies);
    enemy_spawner.update_enemies(run_time, camera, run_time);
    check_for_level_up();
  }
}

void Run::check_for_level_up() {
  if (player.leveled_up > 0) {
    state = RunState::LEVEL_UP;
    level_up_event.set_event();
  }
}

void Run::update_level_up_event() {
  if (state == RunState::LEVEL_UP) {
    int index = level_up_view.update_view(level_up_event, player);

    if (index != -1) {
      level_up_event.select_option(index);
    }

    if (level_up_event.completed) {
      state = RunState::PLAYING;
    }
  }
}

void Run::draw_run() {
  BeginMode2D(camera);
  {

    DrawTexture(background_tile, 0, 0, WHITE);

    player.draw_player();
    enemy_spawner.draw_enemies();
  }
  EndMode2D();

  int minutes = static_cast<int>(run_time) / 60;
  int seconds = static_cast<int>(run_time) % 60;

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

void Run::check_for_input() {
  if (IsKeyPressed(KEY_P)) {
    if (state == RunState::PLAYING) {
      state = RunState::PAUSED;
    } else if (state == RunState::PAUSED) {
      state = RunState::PLAYING;
    }
  }
}
