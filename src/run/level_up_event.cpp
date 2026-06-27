#include "level_up_event.hpp"
#include "../utils/random.hpp"
#include "raygui.h"
#include <cstddef>
#include <raylib.h>

LevelUpEvent::LevelUpEvent(Player &player) : player(player) {
  completed = false;
}

void LevelUpEvent::set_event() {
  completed = false;
  ability_candidate_ids.clear();

  for (auto &ability : player.abilities) {
    bool is_low_level = ability->level < MAX_ABILITY_LEVEL;

    if (is_low_level && ability->id != AbilityId::HEAL) {
      ability_candidate_ids.push_back(ability->id);
    }
  }

  shuffle_vector(ability_candidate_ids);

  if (ability_candidate_ids.size() > 3) {
    ability_candidate_ids.resize(3);
  }

  while (ability_candidate_ids.size() != 3) {
    ability_candidate_ids.push_back(AbilityId::HEAL);
  }
}

void LevelUpEvent::select_option(int i) {
  player.upgrade_ability(ability_candidate_ids[i]);
  completed = true;
  player.leveled_up--;
}
