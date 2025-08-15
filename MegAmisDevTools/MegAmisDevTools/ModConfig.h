#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
    int8 defaultLeader;
    int8 defaultSidekick;
} ModConfig;

extern ModConfig config;

#endif // !MOD_CONFIG_H
