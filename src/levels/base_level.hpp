#pragma once

#include <vector>

enum class BossID {
  BASE_BOSS,
};

struct BossSpawn {
  BossID id;
  float spawn_time;
  bool spawned;
};

class BaseLevel {

public:
  BaseLevel();
  std::vector<BossSpawn> boss_spawns;
};
