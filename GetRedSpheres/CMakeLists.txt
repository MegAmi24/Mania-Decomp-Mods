cmake_minimum_required(VERSION 3.7)

project(GetRedSpheres)
set(MOD_NAME GetRedSpheres CACHE STRING "The mod directory to look into")

set(OUTPUT_NAME "GetRedSpheres" CACHE STRING "The name of the built library")

add_library(GetRedSpheres SHARED
    GameAPI/C/GameAPI/Game.c
    ${MOD_NAME}/dllmain.c
    ${MOD_NAME}/BSS_Message.c
    ${MOD_NAME}/BSS_HUD.c
    ${MOD_NAME}/BSS_Setup.c
    ${MOD_NAME}/BSS_Collectable.c
)

target_include_directories(GetRedSpheres PRIVATE
    ${MOD_NAME}/
    GameAPI/C/
)

set_target_properties(GetRedSpheres PROPERTIES OUTPUT_NAME ${OUTPUT_NAME})

unset(MOD_NAME CACHE)
unset(OUTPUT_NAME CACHE)