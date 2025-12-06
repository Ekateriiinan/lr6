cmake_minimum_required(VERSION 3.10)
project(BalagurFate3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(balagur_fate3
    main.cpp
    npc.cpp
    npc_factory.cpp
    visitor.cpp
    observer.cpp
    dungeon_editor.cpp
    battle_system.cpp
)

target_include_directories(balagur_fate3 PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})