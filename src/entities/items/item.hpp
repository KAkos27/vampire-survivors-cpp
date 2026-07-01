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

class SomeOtherItem : public Item {
public:
  SomeOtherItem(Vector2 position, const char *name);
  std::unique_ptr<Item> clone(Vector2 position) override {
    return std::make_unique<SomeOtherItem>(position, "Some other item");
  }
};

class SomeItem : public Item {
public:
  SomeItem(Vector2 position, const char *name);
  std::unique_ptr<Item> clone(Vector2 position) override {
    return std::make_unique<SomeItem>(position, "Some item");
  }
};
