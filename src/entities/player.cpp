#include "player.hpp"
#include "../abilities/bullet.hpp"
#include "../abilities/fire_aura.hpp"
#include "../abilities/meteor.hpp"
#include "enemy.hpp"
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

const float SPEED = 100;
const float DAMAGE = 30;
const float COLLIDER_RADIUS = 15;

Player::Player(float x, float y) {
  speed = SPEED;
  damage = DAMAGE;
  collider_radius = COLLIDER_RADIUS;
  position = {x, y};

  abilities.push_back(std::make_unique<FireAura>(*this));
  abilities.push_back(std::make_unique<Meteor>(*this));
  // abilities.push_back(std::make_unique<Bullet>(*this));
}

void Player::update_player(std::vector<Enemy> &enemies) {
  set_input_position();
  update_abilities(enemies);
  DrawCircleV(position, collider_radius, GREEN);
}

void Player::update_abilities(std::vector<Enemy> &enemies) {
  for (auto &ability : abilities) {
    ability->update(enemies);
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

  position.x += direction.x * speed * delta;
  position.y += direction.y * speed * delta;
}
