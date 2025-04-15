#ifndef OBJ_HCZSETUP_H
#define OBJ_HCZSETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    TABLE(int32 pendulumAniTileDurations[14], { 4, 3, 2, 2, 2, 3, 3, 4, 3, 2, 2, 2, 3, 3 });
    int32 unused1;
    int32 waterlineAniTileFrame;
    int32 bgCandlesAniTileFrame;
    int32 unused2;
    uint16 bgCandlesAniTiles;
    uint16 waterlineAniTiles;
    uint16 pendulumAniTiles;
    TileLayer *background2Layer;
#if MANIA_USE_PLUS
    int32 waterslidingPlayerCount;
    bool32 playingWaterfallLoop;
    int32 waterfallLoopTimer;
    uint16 sfxWaterfall;
    uint16 sfxWaterfallLoop;
#endif
} ObjectHCZSetup;

// Entity Class
typedef struct {
    RSDK_ENTITY
} EntityHCZSetup;

// Object Struct
extern ObjectHCZSetup *HCZSetup;

// Standard Entity Events
void HCZSetup_StageLoad(void);

#endif //! OBJ_HCZSETUP_H
