#pragma once

#include "enemy.hpp"
#include <raylib.h>

class BasicEnemy : public Enemy {

public:
  BasicEnemy(Player *player, float game_time, Vector2 spawn_position);
  void update_enemy() override;
};
