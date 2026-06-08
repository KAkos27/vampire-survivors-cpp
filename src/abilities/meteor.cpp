#include "meteor.hpp"
#include "../utils/random.hpp"
#include <raylib.h>
#include <vector>

const float COOLDOWN = 3;
const float CRATER_DURATION = 5;
const float CRATER_DAMAGE_TICK_TIMER = 1;

Meteor::Meteor(Player &player) : player(player) {
  cooldown = COOLDOWN;
  damage_multiplier = 0.8;

  crater_radius = 50;
  crater_damage_multiplier = 0.25;
  crater_duration = CRATER_DURATION;
  crater_damage_tick_timer = CRATER_DAMAGE_TICK_TIMER;
}

void Meteor::update(std::vector<Enemy> &enemies) {
  strike_meteor(enemies);
  handle_crater_duration();
  delete_dead_craters();
  deal_crater_damage(enemies);
  draw_craters();
}

void Meteor::strike_meteor(std::vector<Enemy> &enemies) {
  float delta = GetFrameTime();
  cooldown -= delta;

  if (enemies.empty()) {
    return;
  }

  if (cooldown <= 0) {
    int index = random_int(0, enemies.size() - 1);

    enemies[index].take_damage(30);
    craters.push_back({enemies[index].position, crater_duration, true});

    cooldown = COOLDOWN;
  }
}

void Meteor::draw_craters() {
  for (auto &crater : craters) {
    DrawCircleV(crater.position, crater_radius, ORANGE);
  }
}

void Meteor::deal_crater_damage(std::vector<Enemy> &enemies) {
  float delta = GetFrameTime();
  crater_damage_tick_timer -= delta;

  if (crater_damage_tick_timer > 0)
    return;

  crater_damage_tick_timer = CRATER_DAMAGE_TICK_TIMER;

  for (auto &crater : craters) {
    for (auto &enemy : enemies) {
      bool is_colliding =
          CheckCollisionCircles(enemy.position, enemy.collider_radius,
                                crater.position, crater_radius);
      if (is_colliding) {
        enemy.take_damage(crater_damage_multiplier * player.damage);
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

void Meteor::delete_dead_craters() {
  craters.erase(std::remove_if(craters.begin(), craters.end(),
                               [](const MeteorCrater &c) { return !c.alive; }),
                craters.end());
}
