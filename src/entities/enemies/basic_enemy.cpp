#include "basic_enemy.hpp"
#include "../player.hpp"
#include "enemy.hpp"
#include <raylib.h>
#include <raymath.h>

// const float SPEED = 50;
// const float HEALTH = 100;
// const float COLLIDER_RADIUS = 15;
// const float DAMAGE = 25;
// const float ATTACK_TIMER = 1;
// const float HURT_TIMER = 0.15;

BasicEnemy::BasicEnemy(Player *player, float game_time, Vector2 spawn_position)
    : Enemy(player, game_time, spawn_position) {
  health = {100 * difficulity, 100 * difficulity};
  damage = 25 * difficulity;
  speed = 50;
  collider_radius = 15;
  xp_drop = 175 * difficulity;
  base_color = RED;
  color = base_color;
}

void BasicEnemy::update_enemy() {
  follow_player();
  check_for_player_hit();
  flash_enemy();
}
