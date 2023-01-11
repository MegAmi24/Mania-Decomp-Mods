cmake_minimum_required(VERSION 3.7)

project(MegAmisDevTools)
set(MOD_NAME MegAmisDevTools CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "MegAmisDevTools" CACHE STRING "The name of the built library")

add_library(MegAmisDevTools SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Objects/DebugMode.c
    ${MOD_NAME}/Objects/MegAmiMenu.c
    ${MOD_NAME}/Objects/Player.c
)

target_include_directories(MegAmisDevTools PRIVATE
    ${MOD_NAME}/
    ${MOD_NAME}/Objects/
    GameAPI/C/
)

set_target_properties(MegAmisDevTools PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)