cmake_minimum_required(VERSION 3.16)
project(vampire_survivors)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

add_executable(vampire_survivors
    src/main.cpp
    src/game.cpp
    src/run.cpp

    src/utils/random.cpp

    src/ui/level_up_event.cpp
    src/ui/ray_gui_impl.cpp

    src/entities/player.cpp
    src/entities/enemy.cpp
    src/entities/enemy_spawner.cpp

    src/abilities/bullet.cpp
    src/abilities/fire_aura.cpp
    src/abilities/meteor.cpp
    src/abilities/heal.cpp
)

target_link_libraries(vampire_survivors raylib)

target_include_directories(vampire_survivors PRIVATE
    src/external/raygui/src
)

target_compile_options(vampire_survivors PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
