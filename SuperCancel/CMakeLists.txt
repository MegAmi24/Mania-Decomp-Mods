cmake_minimum_required(VERSION 3.7)

project(SuperCancel)
set(MOD_NAME SuperCancel CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "SuperCancel" CACHE STRING "The name of the built library")

add_library(SuperCancel SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/Player.c
    ${MOD_NAME}/HUD.c
)

target_include_directories(SuperCancel PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(SuperCancel PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)