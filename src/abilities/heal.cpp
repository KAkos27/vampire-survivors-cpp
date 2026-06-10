#include "heal.hpp"
#include "ability.hpp"

Heal::Heal(Player &player, bool unlocked) : player(player) {
  name = "Heal";
  id = HEAL;
  unlocked = false;
}

void Heal::upgrade() { player.stats.health.current += 25; }
