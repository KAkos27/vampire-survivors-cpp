cmake_minimum_required(VERSION 3.16)
project(vampire_survivors)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

add_executable(vampire_survivors
    src/main.cpp
    src/game.cpp

    src/entities/player.cpp
    src/entities/enemy.cpp
    src/entities/enemy_spawner.cpp

    src/abilities/bullet.cpp
)

target_link_libraries(vampire_survivors raylib)
