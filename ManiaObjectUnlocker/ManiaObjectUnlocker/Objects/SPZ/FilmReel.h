#ifndef OBJ_FILMREEL_H
#define OBJ_FILMREEL_H

#include "GameAPI/Game.h"

// Object Class
typedef struct {
    RSDK_OBJECT
    Hitbox hitboxWheel;
    Vector2 offsetPos;
    uint16 aniFrames;
    uint16 sfxUnravel;
    uint16 sfxLanding;
} ObjectFilmReel;

// Entity Class
typedef struct {
    RSDK_ENTITY
    Vector2 pathSize;
    uint8 spinDirection;
    Vector2 drawPos;
    Vector2 endPos;
    Vector2 lastPos;
    Vector2 moveOffset;
    int32 spinAngle;
    int32 unused;
    int32 spinSpeed;
    int32 pathFlags;
    int32 pathDir;
    int32 lineDir;
    bool32 moveCamera;
    Animator reelAnimator;
    Animator celluoidAnimator;
    Animator edgeAnimator;
    Animator pinAnimator;
} EntityFilmReel;

// Object Struct
extern ObjectFilmReel *FilmReel;

// Standard Entity Events
void FilmReel_StageLoad(void);

#endif //! OBJ_FILMREEL_H
