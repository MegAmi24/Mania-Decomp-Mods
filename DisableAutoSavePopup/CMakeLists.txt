cmake_minimum_required(VERSION 3.7)

project(DisableAutoSavePopup)
set(MOD_NAME DisableAutoSavePopup CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "DisableAutoSavePopup" CACHE STRING "The name of the built library")

add_library(DisableAutoSavePopup SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
)

target_include_directories(DisableAutoSavePopup PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(DisableAutoSavePopup PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)