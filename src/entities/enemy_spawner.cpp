#include "enemy_spawner.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include <raylib.h>

const float SPAWN_TIMER = 3;

EnemySpawner::EnemySpawner(Player &player) : player(player) {
  spawn_timer = SPAWN_TIMER;
}

void EnemySpawner::spawn_enemies() {
  float delta = GetFrameTime();
  spawn_timer -= delta;

  if (spawn_timer <= 0) {
    Enemy enemy(&player);
    enemies.push_back(enemy);
    spawn_timer = SPAWN_TIMER;
  }
}

void EnemySpawner::update_enemies() {
  spawn_enemies();
  delete_dead_enemies();

  for (auto &enemy : enemies) {
    enemy.update_enemy();
  }
}

void EnemySpawner::draw_enemies() {
  for (auto &enemy : enemies) {
    enemy.draw_enemy();
  }
}

void EnemySpawner::delete_dead_enemies() {
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                               [](const Enemy &e) { return !e.alive; }),
                enemies.end());
}
