#include "items/item.hpp"
#include <unordered_map>

class Inventory {

public:
  std::unordered_map<Item, int> items;
  void pickup_item(Item &item);
};
