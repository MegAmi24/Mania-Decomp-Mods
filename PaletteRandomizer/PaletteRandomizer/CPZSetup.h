#ifndef OBJ_CPZSETUP_H
#define OBJ_CPZSETUP_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    uint16 aniTiles;
    TileLayer *background;
    TABLE(int32 deformation[64], { 1, 2, 1, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 2, 0, 0, 2, 0, 3, 2, 2, 3, 2, 2, 1, 3, 0, 0, 1, 0, 1, 3,
                                   1, 2, 1, 3, 1, 2, 2, 1, 2, 3, 1, 2, 1, 2, 0, 0, 2, 0, 3, 2, 2, 3, 2, 2, 1, 3, 0, 0, 1, 0, 1, 3 });
    int32 bgTowerLightPalIndex;
    int32 rainbowLightPalIndex;
    int32 chemLiquidPalIndex1;
    int32 chemLiquidPalIndex2;
    int32 chemLiquidPalIndex3;
    uint16 aniTileFrame;
    void *outro;
} ObjectCPZSetup;

// Entity Class
typedef struct {
    RSDK_ENTITY
} EntityCPZSetup;

// Object Struct
extern ObjectCPZSetup *CPZSetup;

// Standard Entity Events
void CPZSetup_StageLoad(void);

#endif //! OBJ_CPZSETUP_H
