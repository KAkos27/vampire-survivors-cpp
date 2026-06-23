#include "heal.hpp"
#include "ability.hpp"
#include <iostream>
#include <vector>

Heal::Heal(Player &player, bool unlocked) : player(player) {
  name = "Heal";
  id = AbilityId::HEAL;
  is_unlocked = unlocked;
  heal_amount = 25.0;
}

void Heal::update(std::vector<std::unique_ptr<Enemy>> &enemies) {
  if (enemies.empty()) {
    return;
  }
  std::cout << enemies[0]->health.current << '\n';
}

void Heal::draw() {}

void Heal::upgrade() { player.heal(heal_amount); }
