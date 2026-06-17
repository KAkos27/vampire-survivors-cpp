#include "fire_aura.hpp"
#include "ability.hpp"
#include <raylib.h>
#include <vector>

FireAura::FireAura(Player &player, bool unlocked) : player(player) {
  name = "Fire aura";
  id = AbilityId::FIRE_AURA;
  is_unlocked = unlocked;
  level = 1;
  stats = get_current_stats();
}

void FireAura::update(std::vector<std::unique_ptr<Enemy>> &enemies) {
  deal_damage(enemies);
}

void FireAura::draw() { DrawCircleV(player.position, stats.radius, ORANGE); }

void FireAura::upgrade() {
  if (!is_unlocked) {
    is_unlocked = true;
    return;
  }
  level++;
  stats = get_current_stats();
}

FireAuraStats FireAura::get_current_stats() {
  switch (level) {
  case 1:
    return create_stats(100, 0.5, 1);
  case 2:
    return create_stats(120, 0.5, 1);
  case 3:
    return create_stats(130, 0.7, 0.75);
  case 4:
    return create_stats(130, 0.7, 0.75);
  default:
    return create_stats(150, 0.85, 0.5);
  }
}

FireAuraStats FireAura::create_stats(float radius, float damage_muliplier,
                                     float tick_time) {
  return {radius, damage_muliplier, tick_time, tick_time};
}

void FireAura::deal_damage(std::vector<std::unique_ptr<Enemy>> &enemies) {
  float delta = GetFrameTime();
  stats.tick_time -= delta;

  if (stats.tick_time > 0) {
    return;
  }

  stats.tick_time = stats.base_tick_time;

  for (auto &enemy : enemies) {
    bool is_colliding = CheckCollisionCircles(
        enemy->position, enemy->collider_radius, player.position, stats.radius);

    if (is_colliding) {
      enemy->take_damage(player.stats.damage * stats.damage_muliplier);
    }
  }
}
