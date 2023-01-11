cmake_minimum_required(VERSION 3.7)

project(NoBonusStages)
set(MOD_NAME NoBonusStages CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "NoBonusStages" CACHE STRING "The name of the built library")

add_library(NoBonusStages SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/StarPost.c
)

target_include_directories(NoBonusStages PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(NoBonusStages PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)