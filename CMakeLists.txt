cmake_minimum_required(VERSION 3.21)
project(Epic-Spell-Wars)

set(CMAKE_CXX_STANDARD 17)

add_executable(Epic-Spell-Wars ./card/card.cpp ./round/round.cpp ./game/game.cpp)
