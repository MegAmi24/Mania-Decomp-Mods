cmake_minimum_required(VERSION 3.7)

project(OuttaHereRestored)
set(MOD_NAME OuttaHereRestored CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "OuttaHereRestored" CACHE STRING "The name of the built library")

add_library(OuttaHereRestored SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Player.c
)

target_include_directories(OuttaHereRestored PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(OuttaHereRestored PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)