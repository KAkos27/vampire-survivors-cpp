#include "item.hpp"
#include <raylib.h>

class RingOfHealth : public Item {

public:
  RingOfHealth(Vector2 position);
  std::unique_ptr<Item> clone(Vector2 position) override;
};
