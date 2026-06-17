#include "level_up_event.hpp"
#include "../utils/random.hpp"
#include "raygui.h"
#include <cstddef>
#include <raylib.h>

LevelUpEvent::LevelUpEvent(Player &player) : player(player) {
  been_selected = false;
}

void LevelUpEvent::set_event() {
  been_selected = false;
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

void LevelUpEvent::update_event() {
  for (std::size_t i = 0; i < ability_candidate_ids.size(); i++) {
    bool clicked = draw_button(i);
    if (clicked) {
      player.upgrade_ability(ability_candidate_ids[i]);
      been_selected = true;
      player.leveled_up--;
    }
  }
}

bool LevelUpEvent::draw_button(std::size_t index) {
  float gap = index * 50;
  Ability *ability = player.get_ability(ability_candidate_ids[index]);
  const char *helper_text = ability->is_unlocked ? "upgrade" : "unlock";

  return GuiButton({40, 100 + gap, 720, 32},
                   TextFormat("%s (%s)", ability->name, helper_text));
}
