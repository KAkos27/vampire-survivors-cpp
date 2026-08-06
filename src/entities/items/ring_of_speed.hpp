#include "item.hpp"
#include <raylib.h>

class RingOfSpeed : public Item {

public:
  RingOfSpeed(Vector2 position);
  std::unique_ptr<Item> clone(Vector2 position) override;
};
