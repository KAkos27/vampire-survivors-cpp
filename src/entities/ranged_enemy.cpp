#include "ranged_enemy.hpp"
#include "../run.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

const float SPEED = 50;
const float HEALTH = 50;
const float COLLIDER_RADIUS = 15;
const float DAMAGE = 25;
const float ATTACK_TIMER = 1;
const float SHOOT_TIMER = 2;
const float HURT_TIMER = 0.15;

RangedEnemy::RangedEnemy(Player *player, float game_time,
                         Vector2 spawn_position)
    : player(player) {
  calculate_difficulity(game_time);
  health = {HEALTH * difficulity, HEALTH * difficulity};
  damage = DAMAGE * difficulity;
  speed = SPEED;
  collider_radius = COLLIDER_RADIUS;
  xp_drop = 175 * difficulity;
  position = spawn_position;
  alive = true;
  color = PURPLE;
  hurt = false;
  in_range = false;
  hurt_timer = HURT_TIMER;
  attack_timer = ATTACK_TIMER;

  range = 300;
  projectile_speed = 100;
  projectile_radius = 7.5;
  shoot_timer = SHOOT_TIMER;
}

void RangedEnemy::calculate_difficulity(float game_time) {
  float eleapsed_minutes = (BASE_RUN_TIME - game_time) / 60;
  difficulity = 1.0 + eleapsed_minutes * 0.5;
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
  DrawCircleV(position, collider_radius, color);
  // DrawCircleLinesV(position, range, color);
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
    float delta = GetFrameTime();
    Vector2 direction = Vector2Subtract(player->position, position);
    Vector2 velocity = Vector2Scale(Vector2Normalize(direction), speed * delta);
    position = Vector2Add(position, velocity);
  }
}

void RangedEnemy::check_for_player_hit() {
  bool is_colliding = CheckCollisionCircles(
      position, collider_radius, player->position, player->collider_radius);

  float delta = GetFrameTime();
  attack_timer -= delta;

  if (is_colliding && attack_timer <= 0) {
    player->take_damage(damage);
    attack_timer = ATTACK_TIMER;
  }
}

void RangedEnemy::take_damage(float damage) {
  TraceLog(LOG_INFO, "enemy taken damage: %f", damage);
  health.current -= damage;
  hurt = true;

  if (health.current <= 0) {
    alive = false;
    player->gain_xp(xp_drop);
  }
}

void RangedEnemy::flash_enemy() {
  if (!hurt) {
    return;
  }

  float delta = GetFrameTime();
  hurt_timer -= delta;
  color = WHITE;

  if (hurt_timer <= 0) {
    color = PURPLE;
    hurt = false;
    hurt_timer = HURT_TIMER;
  }
}

void RangedEnemy::delete_dead_projectiles() {
  projectiles.erase(
      std::remove_if(projectiles.begin(), projectiles.end(),
                     [](const EnemyProjectile &p) { return !p.alive; }),
      projectiles.end());
}
