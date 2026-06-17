#include "basic_enemy.hpp"
#include "../run.hpp"
#include "player.hpp"
#include <raylib.h>
#include <raymath.h>

const float SPEED = 50;
const float HEALTH = 100;
const float COLLIDER_RADIUS = 15;
const float DAMAGE = 25;
const float ATTACK_TIMER = 1;
const float HURT_TIMER = 0.15;

BasicEnemy::BasicEnemy(Player *player, float game_time, Vector2 spawn_position)
    : player(player) {
  calculate_difficulity(game_time);
  health = {HEALTH * difficulity, HEALTH * difficulity};
  damage = DAMAGE * difficulity;
  speed = SPEED;
  collider_radius = COLLIDER_RADIUS;
  xp_drop = 175 * difficulity;
  position = spawn_position;
  alive = true;
  color = RED;
  hurt = false;
  hurt_timer = HURT_TIMER;
  attack_timer = ATTACK_TIMER;
}

void BasicEnemy::calculate_difficulity(float game_time) {
  float eleapsed_minutes = (BASE_RUN_TIME - game_time) / 60;
  difficulity = 1.0 + eleapsed_minutes * 0.5;
}

void BasicEnemy::update_enemy() {
  follow_player();
  check_for_player_hit();
  flash_enemy();
}

void BasicEnemy::draw_enemy() { DrawCircleV(position, collider_radius, color); }

void BasicEnemy::follow_player() {
  Vector2 direction = Vector2Subtract(player->position, position);

  float delta = GetFrameTime();
  Vector2 velocity = Vector2Scale(Vector2Normalize(direction), speed * delta);
  position = Vector2Add(position, velocity);
}

void BasicEnemy::check_for_player_hit() {
  bool is_colliding = CheckCollisionCircles(
      position, collider_radius, player->position, player->collider_radius);

  float delta = GetFrameTime();
  attack_timer -= delta;

  if (is_colliding && attack_timer <= 0) {
    player->take_damage(damage);
    attack_timer = ATTACK_TIMER;
  }
}

void BasicEnemy::take_damage(float damage) {
  TraceLog(LOG_INFO, "enemy taken damage: %f", damage);
  health.current -= damage;
  hurt = true;

  if (health.current <= 0) {
    alive = false;
    player->gain_xp(xp_drop);
  }
}

void BasicEnemy::flash_enemy() {
  if (!hurt) {
    return;
  }

  float delta = GetFrameTime();
  hurt_timer -= delta;
  color = WHITE;

  if (hurt_timer <= 0) {
    color = RED;
    hurt = false;
    hurt_timer = HURT_TIMER;
  }
}
