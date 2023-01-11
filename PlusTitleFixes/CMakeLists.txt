cmake_minimum_required(VERSION 3.7)

project(PlusTitleFixes)
set(MOD_NAME PlusTitleFixes CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "PlusTitleFixes" CACHE STRING "The name of the built library")

add_library(PlusTitleFixes SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/TitleSetup.c
)

target_include_directories(PlusTitleFixes PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(PlusTitleFixes PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)