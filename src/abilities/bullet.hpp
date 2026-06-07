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

class Bullet : public Ability {

public:
  Bullet(Player &player);
  void update(std::vector<Enemy> &enemies) override;

private:
  Player &player;
  Vector2 bullet_position;
  std::vector<Projectile> projectiles;
  float cooldown;
  float radius;
  float damage_multiplier;
  float speed;
  void shoot(std::vector<Enemy> &enemies);
  void update_projectiles(std::vector<Enemy> &enemies);
  void check_for_collisions(std::vector<Enemy> &enemies);
  void delete_dead_projectiles();
};
