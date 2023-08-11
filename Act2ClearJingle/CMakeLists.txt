cmake_minimum_required(VERSION 3.7)

project(Act2ClearJingle)
set(MOD_NAME Act2ClearJingle CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "Act2ClearJingle" CACHE STRING "The name of the built library")

add_library(Act2ClearJingle SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Zone.c
)

target_include_directories(Act2ClearJingle PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(Act2ClearJingle PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)