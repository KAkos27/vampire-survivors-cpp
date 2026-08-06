#pragma once

#include <memory>
#include <raylib.h>

class Item {

public:
  Vector2 position;
  const char *name;
  float collider_radius;

  Item(Vector2 position, const char *name);
  void draw_item();
  virtual std::unique_ptr<Item> clone(Vector2 position) = 0;
  virtual ~Item() = default;
};
