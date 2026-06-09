#include "fire_aura.hpp"
#include "ability.hpp"
#include <raylib.h>
#include <vector>

const float TICK_TIME = 1;

FireAura::FireAura(Player &player, bool unlocked) : player(player) {
  this->is_unlocked = unlocked;

  name = "Fire aura";
  id = FIRE_AURA;
  damage_muliplier = 0.5;
  radius = 100;
  tick_time = TICK_TIME;
}

void FireAura::update(std::vector<Enemy> &enemies) { deal_damage(enemies); }

void FireAura::draw() { DrawCircleV(player.position, radius, ORANGE); }

void FireAura::deal_damage(std::vector<Enemy> &enemies) {
  float delta = GetFrameTime();
  tick_time -= delta;

  if (tick_time > 0) {
    return;
  }

  tick_time = TICK_TIME;

  for (auto &enemy : enemies) {
    bool is_colliding = CheckCollisionCircles(
        enemy.position, enemy.collider_radius, player.position, radius);

    if (is_colliding) {
      enemy.take_damage(player.stats.damage * damage_muliplier);
    }
  }
}
