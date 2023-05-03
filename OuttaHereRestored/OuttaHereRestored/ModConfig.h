#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
    bool32 sonicCanOuttaHere;
    bool32 tailsCanOuttaHere;
    bool32 knuxCanOuttaHere;
#if MANIA_USE_PLUS
    bool32 mightyCanOuttaHere;
    bool32 rayCanOuttaHere;
#endif
    int8 sidekickCanOuttaHere;
    int32 sonicAnimID;
    int32 superSonicAnimID;
    int32 tailsAnimID;
    int32 knuxAnimID;
#if MANIA_USE_PLUS
    int32 mightyAnimID;
    int32 rayAnimID;
#endif
    int32 sidekickAnimID;
    bool32 useBinAnim;
    bool32 useVoiceLines;
    bool32 useFrameID;
} ModConfig;

extern ModConfig config;

#endif // !MOD_CONFIG_H