#include "enemy.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

const float SPEED = 50;
const float HEALTH = 100;
const float COLLIDER_RADIUS = 15;

Enemy::Enemy(Player *player) : player(player) {
  speed = SPEED;
  collider_radius = COLLIDER_RADIUS;
  position = {200, 200};
  alive = true;
  health = {HEALTH, HEALTH};
}

void Enemy::update_enemy() {
  follow_player();
  check_for_player_hit();
  DrawCircleV(position, collider_radius, RED);
}

void Enemy::follow_player() {
  Vector2 direction = Vector2Subtract(player->position, position);

  float delta = GetFrameTime();
  Vector2 velocity = Vector2Scale(Vector2Normalize(direction), speed * delta);
  position = Vector2Add(position, velocity);
}

void Enemy::check_for_player_hit() {
  bool is_colliding = CheckCollisionCircles(
      position, collider_radius, player->position, player->collider_radius);

  if (is_colliding) {
    TraceLog(LOG_INFO, "Collision happened");
  }
}

void Enemy::take_damage(float damage) {
  health.current -= damage;

  if (health.current <= 0) {
    alive = false;
  }
}
