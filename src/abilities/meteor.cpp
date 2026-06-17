#include "meteor.hpp"
#include "../utils/random.hpp"
#include "ability.hpp"
#include <raylib.h>
#include <vector>

Meteor::Meteor(Player &player, bool unlocked) : player(player) {
  name = "Meteor";
  id = AbilityId::METEOR;
  is_unlocked = unlocked;
  level = 1;
  stats = get_current_stats();
}

void Meteor::update(std::vector<std::unique_ptr<Enemy>> &enemies) {
  strike_meteor(enemies);
  handle_crater_duration();
  delete_dead_craters();
  deal_crater_damage(enemies);
}

void Meteor::upgrade() {
  if (!is_unlocked) {
    is_unlocked = true;
    return;
  }
  level++;
  stats = get_current_stats();
}

MeteorStats Meteor::get_current_stats() {
  switch (level) {
  case 1:
    return create_stats(4, 0.7, 50, 0.25, 5, 1);
  case 2:
    return create_stats(3, 0.7, 60, 0.3, 5, 1);
  case 3:
    return create_stats(3, 0.8, 75, 0.3, 6, 0.5);
  case 4:
    return create_stats(2.5, 0.8, 100, 0.4, 6, 0.5);
  default:
    return create_stats(1.5, 0.85, 100, 0.6, 8, 0.5);
  }
}

void Meteor::strike_meteor(std::vector<std::unique_ptr<Enemy>> &enemies) {
  float delta = GetFrameTime();
  stats.cooldown -= delta;

  if (enemies.empty()) {
    return;
  }

  if (stats.cooldown <= 0) {
    int index = random_int(0, enemies.size() - 1);

    enemies[index]->take_damage(30);
    craters.push_back({enemies[index]->position, stats.crater_duration, true});

    stats.cooldown = stats.base_cooldown;
  }
}

void Meteor::draw() {
  for (auto &crater : craters) {
    DrawCircleV(crater.position, stats.crater_radius, GOLD);
  }
}

void Meteor::deal_crater_damage(std::vector<std::unique_ptr<Enemy>> &enemies) {
  float delta = GetFrameTime();
  stats.crater_damage_tick_timer -= delta;

  if (stats.crater_damage_tick_timer > 0)
    return;

  stats.crater_damage_tick_timer = stats.base_crater_damage_tick_timer;

  for (auto &crater : craters) {
    for (auto &enemy : enemies) {
      bool is_colliding =
          CheckCollisionCircles(enemy->position, enemy->collider_radius,
                                crater.position, stats.crater_radius);
      if (is_colliding) {
        enemy->take_damage(stats.crater_damage_multiplier *
                           player.stats.damage);
      }
    }
  }
}

void Meteor::handle_crater_duration() {
  float delta = GetFrameTime();

  for (auto &crater : craters) {
    crater.duration -= delta;

    if (crater.duration <= 0) {
      crater.alive = false;
    }
  }
}

MeteorStats Meteor::create_stats(float cooldown, float damage_multiplier,
                                 float crater_radius,
                                 float crater_damage_multiplier,
                                 float crater_duration,
                                 float crater_damage_tick_timer) {
  return {
      cooldown,
      cooldown,
      damage_multiplier,
      crater_radius,
      crater_damage_multiplier,
      crater_duration,
      crater_damage_tick_timer,
      crater_damage_tick_timer,
  };
}

void Meteor::delete_dead_craters() {
  craters.erase(std::remove_if(craters.begin(), craters.end(),
                               [](const MeteorCrater &c) { return !c.alive; }),
                craters.end());
}
