#include "bullet.hpp"
#include "ability.hpp"
#include <algorithm>
#include <raylib.h>
#include <raymath.h>

Bullet::Bullet(Player &player, bool unlocked) : player(player) {
  name = "Bullet";
  id = BULLET;
  is_unlocked = unlocked;
  level = 1;
  stats = get_current_stats();
  radius = 3;
  speed = 500;
}

void Bullet::update(std::vector<Enemy> &enemies) {
  shoot(enemies);
  update_projectiles(enemies);
  check_for_collisions(enemies);
  delete_dead_projectiles();
}

void Bullet::draw() {
  for (auto &projectile : projectiles) {
    DrawCircleV(projectile.position, radius, BLUE);
  }
}

void Bullet::upgrade() {
  if (!is_unlocked) {
    is_unlocked = true;
    return;
  }
  level++;
  stats = get_current_stats();
}

BulletStats Bullet::get_current_stats() {
  switch (level) {
  case 1:
    return create_stats(1.5, 0.8);
  case 2:
    return create_stats(1.5, 0.9);
  case 3:
    return create_stats(1, 0.9);
  case 4:
    return create_stats(0.8, 1);
  default:
    return create_stats(0.5, 1.2);
  }
}

BulletStats Bullet::create_stats(float cooldown, float damage_multiplier) {
  return {cooldown, cooldown, damage_multiplier};
}

void Bullet::shoot(std::vector<Enemy> &enemies) {
  stats.cooldown -= GetFrameTime();

  if (stats.cooldown > 0 || enemies.empty()) {
    return;
  }

  stats.cooldown = stats.base_cooldown;

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
  }
}

void Bullet::check_for_collisions(std::vector<Enemy> &enemies) {
  for (auto &projectile : projectiles) {
    for (auto &enemy : enemies) {

      bool is_colliding = CheckCollisionCircles(
          projectile.position, radius, enemy.position, enemy.collider_radius);
      if (is_colliding) {
        enemy.take_damage(player.stats.damage * stats.damage_multiplier);
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
