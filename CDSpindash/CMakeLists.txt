cmake_minimum_required(VERSION 3.7)

project(CDSpindash)
set(MOD_NAME CDSpindash CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "CDSpindash" CACHE STRING "The name of the built library")

add_library(CDSpindash SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Player.c
    ${MOD_NAME}/Misc.c
)

target_include_directories(CDSpindash PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(CDSpindash PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)