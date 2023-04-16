#include "GameAPI/Game.h"
#include "BSS_Collectable.h"
#include "ModConfig.h"

ObjectBSS_Collectable *BSS_Collectable;

void BSS_Collectable_Create(void *data)
{
    RSDK_THIS(BSS_Collectable);

    Mod.Super(BSS_Collectable->classID, SUPER_CREATE, NULL);

    if ((config.alwaysGetRed || GET_CHARACTER_ID(1) == ID_KNUCKLES) && !SceneInfo->inEditor) {
        // Swap Blue and Red Sphere sprites
        RSDK.SetSpriteAnimation(BSS_Collectable->aniFrames, 1, &BSS_Collectable->sphereAnimator[BSS_SPHERE_BLUE], true, 0);
        RSDK.SetSpriteAnimation(BSS_Collectable->aniFrames, 0, &BSS_Collectable->sphereAnimator[BSS_SPHERE_RED], true, 0);
    }
}