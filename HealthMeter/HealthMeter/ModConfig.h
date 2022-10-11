#ifndef MOD_CONFIG_H
#define MOD_CONFIG_H

#include "GameAPI/Game.h"

typedef struct {
    uint8 StartingHealth;
    uint8 MaxHealth;
} ModConfig;

extern ModConfig config;

#endif // !MOD_CONFIG_H