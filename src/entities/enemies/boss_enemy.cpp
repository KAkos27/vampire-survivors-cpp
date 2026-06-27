#include "boss_enemy.hpp"
#include "../player.hpp"
#include "enemy.hpp"
#include <raylib.h>
#include <raymath.h>

// const float SPEED = 50;
// const float HEALTH = 100;
// const float COLLIDER_RADIUS = 15;
// const float DAMAGE = 25;

BossEnemy::BossEnemy(Player *player, float game_time, Vector2 spawn_position)
    : Enemy(player, game_time, spawn_position) {
  health = {100 * difficulity, 100 * difficulity};
  damage = 25 * difficulity;
  speed = 50;
  collider_radius = 30;
  xp_drop = 175 * difficulity;
  base_color = MAROON;
  color = base_color;
}

void BossEnemy::update_enemy() {
  follow_player();
  check_for_player_hit();
  flash_enemy();
}
