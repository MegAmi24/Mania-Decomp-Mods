cmake_minimum_required(VERSION 3.7)

project(MKItemBox)
set(MOD_NAME MKItemBox CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "MKItemBox" CACHE STRING "The name of the built library")

add_library(MKItemBox SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/ItemBox.c
)

target_include_directories(MKItemBox PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(MKItemBox PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)