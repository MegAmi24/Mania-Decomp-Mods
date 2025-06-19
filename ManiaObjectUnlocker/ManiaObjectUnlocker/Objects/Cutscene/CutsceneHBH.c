#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "CutsceneHBH.h"

ObjectCutsceneHBH *CutsceneHBH;

void CutsceneHBH_Create(void *data)
{
    RSDK_THIS(CutsceneHBH);

    switch (self->characterID) {
        case HBH_GUNNER:
            if (CheckUnlock("CutsceneHBHSPZ1Boss"))
                self->aniFrames = RSDK.LoadSpriteAnimation("SPZ1/Boss.bin", SCOPE_STAGE);
            break;

        case HBH_SHINOBI:
            if (CheckUnlock("CutsceneHBHShinobi"))
                self->aniFrames = RSDK.LoadSpriteAnimation("PSZ2/Shinobi.bin", SCOPE_STAGE);
            break;

        case HBH_MYSTIC:
            if (CheckUnlock("CutsceneHBHHeavyMystic"))
                self->aniFrames = RSDK.LoadSpriteAnimation("MSZ/HeavyMystic.bin", SCOPE_STAGE);
            break;

        case HBH_RIDER:
            if (CheckUnlock("CutsceneHBHHeavyRider"))
                self->aniFrames = RSDK.LoadSpriteAnimation("LRZ3/HeavyRider.bin", SCOPE_STAGE);
            break;

        case HBH_KING:
            if (CheckUnlock("CutsceneHBHHeavyKing"))
                self->aniFrames = RSDK.LoadSpriteAnimation("LRZ3/HeavyKing.bin", SCOPE_STAGE);
            break;

        case HBH_ROGUE_FANG:
            if (CheckUnlock("CutsceneHBHRoguesFang"))
                self->aniFrames = RSDK.LoadSpriteAnimation("MSZ/Rogues.bin", SCOPE_STAGE);
            break;

        case HBH_ROGUE_BEAN:
            if (CheckUnlock("CutsceneHBHRoguesBean"))
                self->aniFrames = RSDK.LoadSpriteAnimation("MSZ/Rogues.bin", SCOPE_STAGE);
            break;

        case HBH_ROGUE_BARK:
            if (CheckUnlock("CutsceneHBHRoguesBark"))
                self->aniFrames = RSDK.LoadSpriteAnimation("MSZ/Rogues.bin", SCOPE_STAGE);
            break;

        default: break;
    }

    Mod.Super(CutsceneHBH->classID, SUPER_CREATE, data);
}
