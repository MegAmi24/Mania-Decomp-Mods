cmake_minimum_required(VERSION 3.7)

project(S2DebugPause)
set(MOD_NAME S2DebugPause CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "S2DebugPause" CACHE STRING "The name of the built library")

add_library(S2DebugPause SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/DebugMode.c
)

target_include_directories(S2DebugPause PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(S2DebugPause PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)