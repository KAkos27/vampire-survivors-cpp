#include "bullet.hpp"
#include "ability.hpp"
#include <algorithm>
#include <cstddef>
#include <raylib.h>
#include <raymath.h>

const float PROJECTILE_DELAY = 0.25;
const float PROJECTILE_LIFE_TIME = 5.0;

Bullet::Bullet(Player &player, bool unlocked) : player(player) {
  name = "Bullet";
  id = AbilityId::BULLET;
  is_unlocked = unlocked;
  level = 1;
  stats = get_current_stats();
  radius = 3;
  speed = 500;
  projecitle_delay = PROJECTILE_DELAY;
  projectiles_left = 0;
}

void Bullet::update(std::vector<Enemy> &enemies) {
  shoot(enemies);
  update_projectiles();
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
    return create_stats(1, 1.5, 0.8);
  case 2:
    return create_stats(2, 1.5, 0.9);
  case 3:
    return create_stats(3, 1, 0.9);
  case 4:
    return create_stats(4, 0.8, 1);
  default:
    return create_stats(5, 0.8, 1.2);
  }
}

BulletStats Bullet::create_stats(std::size_t count, float cooldown,
                                 float damage_multiplier) {
  return {count, cooldown, cooldown, damage_multiplier};
}

void Bullet::shoot(std::vector<Enemy> &enemies) {
  float delta = GetFrameTime();

  stats.cooldown -= delta;
  projecitle_delay -= delta;

  if (projectiles_left == 0) {

    if (stats.cooldown > 0 || enemies.empty()) {
      return;
    }

    projectiles_left = stats.projecitle_count;
    stats.cooldown = stats.base_cooldown;
    projecitle_delay = 0;
  }

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

  if (projecitle_delay <= 0 && projectiles_left > 0) {
    projectiles.push_back({
        player.position,
        Vector2Scale(direction, speed),
        PROJECTILE_LIFE_TIME,
        true,
    });
    projectiles_left--;
    projecitle_delay = PROJECTILE_DELAY;
  }
}

void Bullet::update_projectiles() {
  for (auto &projectile : projectiles) {
    float delta = GetFrameTime();
    projectile.life_time -= delta;

    if (projectile.life_time <= 0) {
      projectile.alive = false;
    }

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
