#include "GameAPI/Game.h"
#include "BSS_Setup.h"
#include "BSS_Collectable.h"
#include "ModConfig.h"

ObjectBSS_Setup *BSS_Setup;

void BSS_Setup_StageLoad(void)
{
    Mod.Super(BSS_Setup->classID, SUPER_STAGELOAD, NULL);

    if (config.alwaysGetRed || GET_CHARACTER_ID(1) == ID_KNUCKLES) {
        // Swap Blue and Red Spheres
        for (int32 x = 0; x < 0x400; ++x) {
            if (BSS_Setup->playField[x] == BSS_SPHERE_BLUE)
                BSS_Setup->playField[x] = BSS_SPHERE_RED;
            else if (BSS_Setup->playField[x] == BSS_SPHERE_RED)
                BSS_Setup->playField[x] = BSS_SPHERE_BLUE;
        }
    }
}