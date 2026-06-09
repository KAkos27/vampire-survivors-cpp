#pragma once

#include "../entities/enemy.hpp"
#include "../entities/player.hpp"
#include "ability.hpp"
#include <raylib.h>
#include <vector>

struct Projectile {
  Vector2 position;
  Vector2 velocity;
  bool alive;
};

struct BulletStats {
  float base_cooldown;
  float cooldown;
  float damage_multiplier;
};

class Bullet : public Ability {

public:
  Bullet(Player &player, bool unlocked);
  void update(std::vector<Enemy> &enemies) override;
  void draw() override;
  void upgrade() override;

private:
  Player &player;
  Vector2 bullet_position;
  std::vector<Projectile> projectiles;
  BulletStats stats;
  float radius;
  float speed;
  void shoot(std::vector<Enemy> &enemies);
  void update_projectiles(std::vector<Enemy> &enemies);
  void check_for_collisions(std::vector<Enemy> &enemies);
  void delete_dead_projectiles();
  BulletStats get_current_stats();
  BulletStats create_stats(float cooldown, float damage_multiplier);
};
