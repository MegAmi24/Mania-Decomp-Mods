cmake_minimum_required(VERSION 3.7)

project(HealthMeter)
set(MOD_NAME HealthMeter CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "HealthMeter" CACHE STRING "The name of the built library")

add_library(HealthMeter SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Objects/HUD.c
    ${MOD_NAME}/Objects/ItemBox.c
    ${MOD_NAME}/Objects/Player.c
    ${MOD_NAME}/Objects/Ring.c
    ${MOD_NAME}/Objects/Misc.c
)

target_include_directories(HealthMeter PRIVATE
    ${MOD_NAME}/
    ${MOD_NAME}/Objects/
    GameAPI/C/
)

set_target_properties(HealthMeter PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)