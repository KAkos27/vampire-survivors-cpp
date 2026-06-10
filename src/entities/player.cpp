#include "player.hpp"
#include "../abilities/bullet.hpp"
#include "../abilities/fire_aura.hpp"
#include "../abilities/heal.hpp"
#include "../abilities/meteor.hpp"
#include "enemy.hpp"
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

const float BASE_HEALTH = 200;
const float BASE_SPEED = 100;
const float BASE_DAMAGE = 30;

Player::Player(float x, float y) {
  init_stats(BASE_HEALTH, BASE_DAMAGE, BASE_SPEED);
  collider_radius = 15;
  position = {x, y};

  experience = {1, 0, 200};
  leveled_up = false;
  is_alive = true;

  abilities.push_back(std::make_unique<Heal>(*this, false));

  abilities.push_back(std::make_unique<FireAura>(*this, false));
  abilities.push_back(std::make_unique<Meteor>(*this, false));
  abilities.push_back(std::make_unique<Bullet>(*this, true));
}

void Player::init_stats(float health, float damage, float speed) {
  stats = {
      health, damage, speed, {health, health}, damage, speed,
  };
}

void Player::update_player(std::vector<Enemy> &enemies) {
  set_input_position();
  update_abilities(enemies);
}

void Player::draw_player() {
  draw_abilities();
  DrawCircleV(position, collider_radius, GREEN);
}

void Player::update_abilities(std::vector<Enemy> &enemies) {
  for (auto &ability : abilities) {
    if (ability->is_unlocked) {
      ability->update(enemies);
    }
  }
}

void Player::draw_abilities() {
  for (auto &ability : abilities) {
    if (ability->is_unlocked) {
      ability->draw();
    }
  }
}

void Player::set_input_position() {
  Vector2 direction = {0, 0};
  if (IsKeyDown(KEY_RIGHT))
    direction.x += 1;
  if (IsKeyDown(KEY_LEFT))
    direction.x -= 1;
  if (IsKeyDown(KEY_UP))
    direction.y -= 1;
  if (IsKeyDown(KEY_DOWN))
    direction.y += 1;

  float delta = GetFrameTime();
  direction = Vector2Normalize(direction);

  position.x += direction.x * stats.speed * delta;
  position.y += direction.y * stats.speed * delta;
}

void Player::gain_xp(float amount) {
  experience.current += amount;

  if (experience.current >= experience.xp_to_next_level) {
    float remaining = experience.current - experience.xp_to_next_level;

    experience.level++;
    experience.xp_to_next_level *= 2;
    experience.current = remaining;
    leveled_up = true;
    update_stats();
  }
}

void Player::take_damage(float amount) {
  stats.health.current -= amount;

  if (stats.health.current <= 0) {
    is_alive = false;
  }
}

void Player::update_stats() {
  float multiplier = 1.0 + (experience.level - 1.0) * 0.1;
  float health_ratio = stats.health.current / stats.health.max;

  stats.damage = stats.base_damage * multiplier;
  stats.speed = stats.base_speed * multiplier;
  stats.health.max = stats.base_health * multiplier;
  stats.health.current = stats.health.max * health_ratio;
}

void Player::upgrade_ability(AbilityId id) {
  for (auto &ability : abilities) {
    if (ability->id == id) {
      ability->upgrade();
    }
  }
}

Ability Player::get_ability(AbilityId id) {
  for (auto &ability : abilities) {
    if (ability->id == id) {
      return *ability;
    }
  }

  return *abilities[0];
}
