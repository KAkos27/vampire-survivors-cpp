#pragma once

#include "../entities/player.hpp"
#include "../run/level_up_event.hpp"
#include <cstddef>

class LevelUpView {
public:
  int update_view(const LevelUpEvent &level_up_event, Player &player);

private:
  bool draw_button(std::size_t index, Player &player, AbilityId id);
};
