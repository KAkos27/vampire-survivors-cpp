#include "level_up_event.hpp"
#include "../utils/random.hpp"
#include "raygui.h"
#include <raylib.h>

LevelUpEvent::LevelUpEvent(Player &player) : player(player) {}

void LevelUpEvent::set_event() {
  been_selected = false;
  ability_candidates_ids.clear();

  while (ability_candidates_ids.size() != 3) {
    int index = random_int(0, player.abilities.size() - 1);
    bool contains = false;

    for (auto &ability : ability_candidates_ids) {
      if (ability == player.abilities[index]->id) {
        contains = true;
      }
    }

    if (!contains) {
      ability_candidates_ids.push_back(player.abilities[index]->id);
    }
  }
}

void LevelUpEvent::update_event() {
  for (int i = 0; i < ability_candidates_ids.size(); i++) {
    bool clicked = draw_button(i);
    if (clicked) {
      Ability ability = player.get_ability(ability_candidates_ids[i]);
      player.upgrade_ability(ability_candidates_ids[i]);
      been_selected = true;
    }
  }
}

bool LevelUpEvent::draw_button(int index) {
  float gap = index * 50;
  Ability ability = player.get_ability(ability_candidates_ids[index]);
  const char *helper_text = ability.is_unlocked ? "upgrade" : "unlock";

  return GuiButton({40, 100 + gap, 720, 32},
                   TextFormat("%s (%s)", ability.name, helper_text));
}
