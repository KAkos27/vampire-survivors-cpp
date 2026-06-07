#include "bullet.hpp"
#include <algorithm>
#include <raylib.h>
#include <raymath.h>

const float COOLDOWN = 1.5;
const float RADIUS = 1.5;
const float DAMAGE_MULTIPLIER = 0.8;
const float SPEED = 500;

Bullet::Bullet(Player &player) : player(player) {
  cooldown = COOLDOWN;
  radius = RADIUS;
  damage_multiplier = DAMAGE_MULTIPLIER;
  speed = SPEED;
}

void Bullet::update(std::vector<Enemy> &enemies) {
  shoot(enemies);
  update_projectiles(enemies);
  check_for_collisions(enemies);
  delete_dead_projectiles();
}

void Bullet::shoot(std::vector<Enemy> &enemies) {
  cooldown -= GetFrameTime();

  if (cooldown > 0 || enemies.empty()) {
    return;
  }

  cooldown = COOLDOWN;

  Enemy *nearest = &enemies[0];
  for (auto &enemy : enemies) {
    float current_distance = Vector2Distance(player.position, enemy.position);
    float nearest_distance =
        Vector2Distance(player.position, nearest->position);

    if (current_distance < nearest_distance) {
      nearest = &enemy;
    }
  }

  Vector2 direction =
      Vector2Normalize(Vector2Subtract(nearest->position, player.position));
  projectiles.push_back({
      player.position,
      Vector2Scale(direction, speed),
      true,
  });
}

void Bullet::update_projectiles(std::vector<Enemy> &enemies) {
  for (auto &projectile : projectiles) {
    float delta = GetFrameTime();
    projectile.position = Vector2Add(projectile.position,
                                     Vector2Scale(projectile.velocity, delta));
    DrawCircleV(projectile.position, radius, BLUE);
  }
}

void Bullet::check_for_collisions(std::vector<Enemy> &enemies) {
  for (auto &projectile : projectiles) {
    for (auto &enemy : enemies) {

      bool is_colliding = CheckCollisionCircles(
          projectile.position, radius, enemy.position, enemy.collider_radius);
      if (is_colliding) {
        TraceLog(LOG_INFO, "dam");
        enemy.take_damage(player.damage * damage_multiplier);
        projectile.alive = false;
        break;
      }
    }
  }
}

void Bullet::delete_dead_projectiles() {
  projectiles.erase(
      std::remove_if(projectiles.begin(), projectiles.end(),
                     [](const Projectile &p) { return !p.alive; }),
      projectiles.end());
}
