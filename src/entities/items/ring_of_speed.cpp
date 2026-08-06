#include "ring_of_speed.hpp"
#include "item.hpp"
#include <memory>
#include <raylib.h>

static constexpr const char *NAME = "Ring of Speed";

RingOfSpeed::RingOfSpeed(Vector2 position) : Item(position, NAME) {}

std::unique_ptr<Item> RingOfSpeed::clone(Vector2 position) {
  return std::make_unique<RingOfSpeed>(position);
}
