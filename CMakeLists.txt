cmake_minimum_required(VERSION 3.24)
project(project_game_of_life C)

set(CMAKE_C_STANDARD 17)

include_directories(.)

add_executable(project_game_of_life
        main.c)
