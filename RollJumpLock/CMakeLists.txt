cmake_minimum_required(VERSION 3.7)

project(RollJumpLock)
set(MOD_NAME RollJumpLock CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "RollJumpLock" CACHE STRING "The name of the built library")

add_library(RollJumpLock SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Player.c
)

target_include_directories(RollJumpLock PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(RollJumpLock PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)