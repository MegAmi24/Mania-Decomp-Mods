cmake_minimum_required(VERSION 3.7)

project(DunkeyLives)
set(MOD_NAME DunkeyLives CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "DunkeyLives" CACHE STRING "The name of the built library")

add_library(DunkeyLives SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/PullChain.c
)

target_include_directories(DunkeyLives PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(DunkeyLives PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)