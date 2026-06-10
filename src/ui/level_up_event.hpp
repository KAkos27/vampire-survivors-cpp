#pragma once

#include "../abilities/ability.hpp"
#include "../entities/player.hpp"
#include <cstddef>
#include <vector>

class LevelUpEvent {

public:
  LevelUpEvent(Player &player);
  bool been_selected;
  void set_event();
  void update_event();

private:
  Player &player;
  std::vector<AbilityId> ability_candidate_ids;
  bool draw_button(std::size_t index);
};
