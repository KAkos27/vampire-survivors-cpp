#pragma once

#include "../entities/enemies/enemy.hpp"
#include "../entities/player.hpp"
#include "ability.hpp"
#include <cstddef>
#include <raylib.h>
#include <vector>

struct Projectile {
  Vector2 position;
  Vector2 velocity;
  float life_time;
  bool alive;
};

struct BulletStats {
  std::size_t projecitle_count;
  float base_cooldown;
  float cooldown;
  float damage_multiplier;
};

class Bullet : public Ability {

public:
  Bullet(Player &player, bool unlocked);
  void update(std::vector<std::unique_ptr<Enemy>> &enemies) override;
  void draw() override;
  void upgrade() override;

private:
  Player &player;
  std::vector<Projectile> projectiles;
  BulletStats stats;
  std::size_t projectiles_left;
  float radius;
  float speed;
  float projecitle_delay;
  void shoot(std::vector<std::unique_ptr<Enemy>> &enemies);
  void check_for_collisions(std::vector<std::unique_ptr<Enemy>> &enemies);
  void update_projectiles();
  void delete_dead_projectiles();
  BulletStats get_current_stats();
  BulletStats create_stats(std::size_t count, float cooldown,
                           float damage_multiplier);
};
