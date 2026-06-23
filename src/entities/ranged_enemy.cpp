#include "ranged_enemy.hpp"
#include "enemy.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

const float SPEED = 50;
const float HEALTH = 50;
const float COLLIDER_RADIUS = 15;
const float DAMAGE = 25;
const float SHOOT_TIMER = 2;

RangedEnemy::RangedEnemy(Player *player, float game_time,
                         Vector2 spawn_position)
    : Enemy(player, game_time, spawn_position) {
  calculate_difficulity(game_time);
  health = {HEALTH * difficulity, HEALTH * difficulity};
  damage = DAMAGE * difficulity;
  speed = SPEED;
  collider_radius = COLLIDER_RADIUS;
  xp_drop = 175 * difficulity;
  base_color = PURPLE;
  color = base_color;

  in_range = false;
  range = 300;
  projectile_speed = 100;
  projectile_radius = 7.5;
  shoot_timer = SHOOT_TIMER;
}

void RangedEnemy::update_enemy() {
  follow_player();
  check_for_in_range();
  shoot();
  update_projectiles();
  delete_dead_projectiles();
  check_for_projectile_hit();
  check_for_player_hit();
  flash_enemy();
}

void RangedEnemy::draw_enemy() {
  Enemy::draw_enemy();
  draw_projectiles();
}

void RangedEnemy::update_projectiles() {
  for (auto &projectile : projectiles) {
    if (projectile.alive) {
      float delta = GetFrameTime();
      projectile.life_time -= delta;

      if (projectile.life_time <= 0) {
        projectile.alive = false;
      }

      projectile.position = Vector2Add(
          projectile.position, Vector2Scale(projectile.velocity, delta));
    }
  }
}

void RangedEnemy::draw_projectiles() {
  for (auto &projectile : projectiles) {
    if (projectile.alive) {
      DrawCircleV(projectile.position, projectile_radius, MAROON);
    }
  }
}

void RangedEnemy::shoot() {
  float delta = GetFrameTime();
  shoot_timer -= delta;

  if (in_range && shoot_timer <= 0) {
    Vector2 direction = Vector2Subtract(player->position, position);
    Vector2 velocity =
        Vector2Scale(Vector2Normalize(direction), projectile_speed);
    projectiles.push_back({position, velocity, 5, true});
    shoot_timer = SHOOT_TIMER;
  }
}

void RangedEnemy::check_for_projectile_hit() {
  for (auto &projectile : projectiles) {
    bool is_colliding =
        CheckCollisionCircles(projectile.position, projectile_radius,
                              player->position, player->collider_radius);
    if (is_colliding) {
      projectile.alive = false;
      player->take_damage(damage);
    }
  }
}

void RangedEnemy::check_for_in_range() {
  in_range = CheckCollisionCircles(player->position, player->collider_radius,
                                   position, range);
}

void RangedEnemy::follow_player() {
  if (!in_range) {
    Enemy::follow_player();
  }
}

void RangedEnemy::delete_dead_projectiles() {
  projectiles.erase(
      std::remove_if(projectiles.begin(), projectiles.end(),
                     [](const EnemyProjectile &p) { return !p.alive; }),
      projectiles.end());
}
