#include "ring_of_health.hpp"
#include "item.hpp"
#include <memory>
#include <raylib.h>

static constexpr const char *NAME = "Ring of Health";

RingOfHealth::RingOfHealth(Vector2 position) : Item(position, NAME) {}

std::unique_ptr<Item> RingOfHealth::clone(Vector2 position) {
  return std::make_unique<RingOfHealth>(position);
}
