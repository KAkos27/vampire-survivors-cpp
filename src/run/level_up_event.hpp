#pragma once

#include "../abilities/ability.hpp"
#include "../entities/player.hpp"
#include <cstddef>
#include <vector>

class LevelUpEvent {

public:
  LevelUpEvent(Player &player);
  std::vector<AbilityId> ability_candidate_ids;
  bool completed;
  void set_event();
  void update_event();
  void select_option(int index);

private:
  Player &player;
  bool draw_button(std::size_t index);
};
