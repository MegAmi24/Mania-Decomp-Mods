#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
    bool32 costLives;
} ModConfig;

extern ModConfig config;

#endif // !MOD_CONFIG_H