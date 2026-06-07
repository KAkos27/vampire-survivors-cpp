#pragma once
#include <raylib.h>

class Player {
public:
  void update_player();
  Player(float x, float y);

private:
  Vector2 position;
  void set_input_position();
};
