#include "enemy.hpp"
#include "../../run/run.hpp"
#include "../../utils/random.hpp"
#include "../items/ring_of_health.hpp"
#include "../items/ring_of_speed.hpp"
#include "../player.hpp"
#include <cstddef>
#include <memory>
#include <raylib.h>
#include <raymath.h>

const float ATTACK_TIMER = 1;
const float HURT_TIMER = 0.15;

Enemy::Enemy(Player *player, float game_time, Vector2 spawn_position)
    : player(player) {
  calculate_difficulity(game_time);
  position = spawn_position;
  alive = true;
  hurt = false;
  hurt_timer = HURT_TIMER;
  attack_timer = ATTACK_TIMER;

  drops.push_back({std::make_unique<RingOfHealth>(Vector2Zero()), 50});
  drops.push_back({std::make_unique<RingOfSpeed>(Vector2Zero()), 50});
}

void Enemy::draw_enemy() { DrawCircleV(position, collider_radius, color); }

void Enemy::take_damage(float damage) {
  health.current -= damage;
  hurt = true;

  if (health.current <= 0) {
    alive = false;
    player->gain_xp(xp_drop);
  }
}

std::unique_ptr<Item> Enemy::roll_drop() {
  float roll = random_float(0, 100);
  float cumulative = 0;

  for (auto &drop : drops) {
    cumulative += drop.drop_chance;

    if (roll < cumulative) {
      return drop.item->clone(position);
    }
  }

  return nullptr;
}

void Enemy::check_for_player_hit() {
  bool is_colliding = CheckCollisionCircles(
      position, collider_radius, player->position, player->collider_radius);

  attack_timer -= GetFrameTime();

  if (is_colliding && attack_timer <= 0) {
    player->take_damage(damage);
    attack_timer = ATTACK_TIMER;
  }
}
void Enemy::flash_enemy() {
  if (!hurt) {
    return;
  }

  hurt_timer -= GetFrameTime();
  color = WHITE;

  if (hurt_timer <= 0) {
    color = base_color;
    hurt = false;
    hurt_timer = HURT_TIMER;
  }
}

void Enemy::calculate_difficulity(float game_time) {
  float eleapsed_minutes = (BASE_RUN_TIME - game_time) / 60;
  difficulity = 1.0 + eleapsed_minutes * 0.5;
}

void Enemy::follow_player() {
  Vector2 direction = Vector2Subtract(player->position, position);

  float delta = GetFrameTime();
  Vector2 velocity = Vector2Scale(Vector2Normalize(direction), speed * delta);
  position = Vector2Add(position, velocity);
}
