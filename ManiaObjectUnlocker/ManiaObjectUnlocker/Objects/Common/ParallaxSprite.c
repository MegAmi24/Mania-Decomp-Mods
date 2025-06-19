#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "ParallaxSprite.h"

ObjectParallaxSprite *ParallaxSprite;

void ParallaxSprite_StageLoad(void)
{
    if (CheckUnlock("ParallaxSpriteLRZ2"))
        ParallaxSprite->aniFrames = RSDK.LoadSpriteAnimation("LRZ2/LRZParallax.bin", SCOPE_STAGE);
    else if (CheckUnlock("ParallaxSpriteOOZ"))
        ParallaxSprite->aniFrames = RSDK.LoadSpriteAnimation("OOZ/OOZParallax.bin", SCOPE_STAGE);

    Mod.Super(ParallaxSprite->classID, SUPER_STAGELOAD, NULL);
}
