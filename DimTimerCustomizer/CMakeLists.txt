cmake_minimum_required(VERSION 3.7)

project(DimTimerCustomizer)
set(MOD_NAME DimTimerCustomizer CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "DimTimerCustomizer" CACHE STRING "The name of the built library")

add_library(DimTimerCustomizer SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
)

target_include_directories(DimTimerCustomizer PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(DimTimerCustomizer PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)