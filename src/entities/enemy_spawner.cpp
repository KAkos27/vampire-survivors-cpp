#include "enemy_spawner.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

const float SPAWN_TIMER = 1;

EnemySpawner::EnemySpawner(Player &player) : player(player) {
  spawn_timer = SPAWN_TIMER;
}

void EnemySpawner::spawn_enemies(float game_time) {
  float delta = GetFrameTime();
  spawn_timer -= delta;

  if (spawn_timer <= 0) {
    enemies.push_back(Enemy(&player, game_time));
    spawn_timer = SPAWN_TIMER;
  }
}

void EnemySpawner::update_enemies(float game_time) {
  spawn_enemies(game_time);
  delete_dead_enemies();

  for (auto &enemy : enemies) {
    enemy.update_enemy();
  }

  separate_enemies();
}

void EnemySpawner::draw_enemies() {
  for (auto &enemy : enemies) {
    enemy.draw_enemy();
  }
}

void EnemySpawner::separate_enemies() {
  for (size_t i = 0; i < enemies.size(); i++) {
    for (size_t j = i + 1; j < enemies.size(); j++) {
      Enemy &a = enemies[i];
      Enemy &b = enemies[j];

      if (a.alive && b.alive) {
        Vector2 diff = Vector2Subtract(a.position, b.position);
        float distance = Vector2Length(diff);

        float minDistance = a.collider_radius + b.collider_radius;

        if (distance > 0.0f && distance < minDistance) {
          Vector2 pushDir = Vector2Scale(diff, 1.0f / distance);

          float overlap = minDistance - distance;

          Vector2 push = Vector2Scale(pushDir, overlap * 0.5f);

          a.position = Vector2Add(a.position, push);
          b.position = Vector2Subtract(b.position, push);
        }
      }
    }
  }
}

void EnemySpawner::delete_dead_enemies() {
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                               [](const Enemy &e) { return !e.alive; }),
                enemies.end());
}
