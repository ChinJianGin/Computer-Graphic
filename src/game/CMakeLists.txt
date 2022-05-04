cmake_minimum_required(VERSION 3.17)

include_directories(${CMAKE_SOURCE_DIR})

project(game)

add_library(game ./src/Game.cpp ./src/Scene.cpp ./src/Actor.cpp ./src/Player.cpp ./src/Projectile.cpp ./src/ProjectileSystem.cpp ./src/Enemy.cpp ./src/NormalEnemy.cpp ./src/EliteEnemy.cpp ./src/BossEnemy.cpp)