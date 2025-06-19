#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "Platform.h"

ObjectPlatform *Platform;

void Platform_StageLoad(void)
{
    if (CheckUnlock("PlatformGHZ"))
        Platform->aniFrames = RSDK.LoadSpriteAnimation("GHZ/Platform.bin", SCOPE_STAGE);
    else if (CheckUnlock("PlatformAIZ"))
        Platform->aniFrames = RSDK.LoadSpriteAnimation("AIZ/Platform.bin", SCOPE_STAGE);

    Mod.Super(Platform->classID, SUPER_STAGELOAD, NULL);
}
