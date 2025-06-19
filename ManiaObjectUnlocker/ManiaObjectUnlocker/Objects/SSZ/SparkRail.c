#include "GameAPI/Game.h"
#include "UnlockCodes.h"
#include "SparkRail.h"

ObjectSparkRail *SparkRail;

void SparkRail_StageLoad(void)
{
    Mod.Super(SparkRail->classID, SUPER_STAGELOAD, NULL);

    if (CheckUnlock("SparkRailSSZ1"))
        SparkRail->aniFrames = RSDK.LoadSpriteAnimation("SSZ1/Spark.bin", SCOPE_STAGE);
}
