cmake_minimum_required(VERSION 3.17)
project(Epic_Spell_Wars)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_executable(Epic_Spell_Wars
        src/cards_functions.cpp include/cards_functions.h)
