#include "item.hpp"
#include <raylib.h>

const float COLLIDER_RADIUS = 7.5;

Item::Item(Vector2 position, const char *name) {
  this->position = position;
  this->name = name;

  collider_radius = COLLIDER_RADIUS;
}

void Item::draw_item() { DrawCircleV(position, collider_radius, BLUE); }
