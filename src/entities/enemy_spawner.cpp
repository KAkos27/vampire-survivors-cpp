#include "enemy_spawner.hpp"
#include "../utils/random.hpp"
#include "basic_enemy.hpp"
#include "player.hpp"
#include <memory>
#include <raylib.h>
#include <raymath.h>

const float SPAWN_TIMER = 0.5;

EnemySpawner::EnemySpawner(Player &player) : player(player) {
  spawn_timer = SPAWN_TIMER;
}

void EnemySpawner::spawn_enemies(float game_time, Camera2D camera) {
  float delta = GetFrameTime();
  spawn_timer -= delta;

  if (spawn_timer <= 0) {
    enemies.push_back(std::make_unique<BasicEnemy>(
        &player, game_time, get_random_position(camera)));
    spawn_timer = SPAWN_TIMER;
  }
}

Vector2 EnemySpawner::get_random_position(Camera2D camera) {
  const float margin = 200;
  Vector2 topLeft = GetScreenToWorld2D({0.0f, 0.0f}, camera);

  Vector2 bottomRight =
      GetScreenToWorld2D({static_cast<float>(GetScreenWidth()),
                          static_cast<float>(GetScreenHeight())},
                         camera);

  int side = random_int(0, 3);

  switch (side) {
  case 0: {
    float x = random_float(topLeft.x, bottomRight.x);
    float y = topLeft.y - margin;
    return {x, y};
  }
  case 1: {
    float x = random_float(topLeft.x, bottomRight.x);
    float y = bottomRight.y + margin;
    return {x, y};
  }
  case 2: {
    float x = topLeft.x - margin;
    float y = random_float(topLeft.y, bottomRight.y);
    return {x, y};
  }
  default: {
    float x = bottomRight.x + margin;
    float y = random_float(topLeft.y, bottomRight.y);
    return {x, y};
  }
  }
};

void EnemySpawner::update_enemies(float game_time, Camera2D camera) {
  spawn_enemies(game_time, camera);
  delete_dead_enemies();

  for (auto &enemy : enemies) {
    enemy->update_enemy();
  }

  separate_enemies();
}

void EnemySpawner::draw_enemies() {
  for (auto &enemy : enemies) {
    enemy->draw_enemy();
  }
}

void EnemySpawner::separate_enemies() {
  for (std::size_t i = 0; i < enemies.size(); i++) {
    for (std::size_t j = i + 1; j < enemies.size(); j++) {
      Enemy *a = enemies[i].get();
      Enemy *b = enemies[j].get();

      if (a->alive && b->alive) {
        Vector2 diff = Vector2Subtract(a->position, b->position);
        float distance = Vector2Length(diff);

        float minDistance = a->collider_radius + b->collider_radius;

        if (distance > 0.0 && distance < minDistance) {
          Vector2 pushDir = Vector2Scale(diff, 1.0 / distance);

          float overlap = minDistance - distance;

          Vector2 push = Vector2Scale(pushDir, overlap * 0.5);

          a->position = Vector2Add(a->position, push);
          b->position = Vector2Subtract(b->position, push);
        }
      }
    }
  }
}

void EnemySpawner::delete_dead_enemies() {
  enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
                               [](const auto &e) { return !e->alive; }),
                enemies.end());
}
