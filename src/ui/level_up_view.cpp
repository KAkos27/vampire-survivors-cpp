#include "level_up_view.hpp"
#include "raygui.h"

int LevelUpView::update_view(const LevelUpEvent &level_up_event,
                             Player &player) {
  for (std::size_t i = 0; i < level_up_event.ability_candidate_ids.size();
       i++) {
    if (draw_button(i, player, level_up_event.ability_candidate_ids[i])) {
      return i;
    }
  }
  return -1;
}

bool LevelUpView::draw_button(std::size_t index, Player &player, AbilityId id) {
  float gap = index * 50;
  Ability *ability = player.get_ability(id);
  const char *helper_text = ability->is_unlocked ? "upgrade" : "unlock";

  return GuiButton({40, 100 + gap, 720, 32},
                   TextFormat("%s (%s)", ability->name, helper_text));
}
