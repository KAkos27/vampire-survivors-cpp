#pragma once

#include "enemy.hpp"
#include <raylib.h>

class BossEnemy : public Enemy {

public:
  BossEnemy(Player *player, float game_time, Vector2 spawn_position);
  void update_enemy() override;
};
