#include "GameAPI/Game.h"
#include "StarPost.h"

ObjectStarPost *StarPost;

void StarPost_Update(void)
{
    RSDK_THIS(StarPost);
    Mod.Super(StarPost->classID, SUPER_UPDATE, NULL);
    if (self->bonusStageID > 0)
        self->bonusStageID = 0;
}
