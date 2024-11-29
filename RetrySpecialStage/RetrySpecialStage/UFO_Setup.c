#include "GameAPI/Game.h"
#include "UFO_Setup.h"
#include "Misc.h"
#include "ModConfig.h"

ObjectUFO_Setup *UFO_Setup;

bool32 UFO_Setup_State_FinishFadeout_Hook(bool32 skippedState)
{
    RSDK_THIS(UFO_Setup);

    if (self->timer >= 1024) {
        for (int32 l = 0; l < LAYER_COUNT; ++l) {
            TileLayer *layer = RSDK.GetTileLayer(l);
            if (layer)
                layer->drawGroup[0] = DRAWGROUP_COUNT;
        }

        for (int32 l = 0; l < SCENEENTITY_COUNT; ++l) {
            Entity *entity = RSDK_GET_ENTITY_GEN(l);
            if (entity->classID != self->classID)
                destroyEntity(entity);
        }

#if MANIA_USE_PLUS
        bool32 costLives = config.costLives && globals->gameMode != MODE_ENCORE;
#else
        bool32 costLives = config.costLives;
#endif

        bool32 hasLives = true;

        if (costLives) {
            SaveRAM *saveRAM = SaveGame_GetSaveRAM();
            hasLives         = saveRAM->lives > 1;
        }

        if (!UFO_Setup->timedOut || !hasLives) {
            UFO_Setup_ShowClearScreen();
            return true;
        }

        String msg;
        INIT_STRING(msg);

        char txt[0x50] = "WOULD YOU LIKE TO RETRY?";
        if (costLives && hasLives) {
            SaveRAM *saveRAM = SaveGame_GetSaveRAM();
            sprintf_s(txt, (int32)sizeof(txt), "WOULD YOU LIKE TO RETRY?\nTHIS WILL COST 1 LIFE.\nCURRENT LIVES: %d", saveRAM->lives);
        }

        RSDK.InitString(&msg, txt, 0);
        EntityUIDialog *dialog = UIDialog_CreateDialogYesNo(&msg, UFO_Setup_RetryDLG_CB, UFO_Setup_CancelDLG_CB, true, true);
        if (dialog)
            dialog->entityPtr = (Entity *)self;

        self->state = StateMachine_None;
    }
    else {
        self->timer += 8;
    }

    return true;
}

void UFO_Setup_RetryDLG_CB(void)
{
#if MANIA_USE_PLUS
    if (config.costLives && globals->gameMode != MODE_ENCORE) {
#else
    if (config.costLives) {
#endif
        SaveRAM *saveRAM = SaveGame_GetSaveRAM();
        saveRAM->lives--;
    }

    RSDK.LoadScene();
}

void UFO_Setup_CancelDLG_CB(void)
{
    Entity *storeEntity = SceneInfo->entity;
    SceneInfo->entity   = RSDK_GET_ENTITY_GEN(SLOT_UFO_SETUP);
    UFO_Setup_ShowClearScreen();
    SceneInfo->entity = storeEntity;
}

void UFO_Setup_ShowClearScreen(void)
{
    RSDK_THIS(UFO_Setup);

    if (UFO_Setup->resetToTitle) {
        RSDK.SetScene("Presentation", "Title Screen");
        RSDK.LoadScene();
    }
    else {
        ObjectUIBackground *UIBackground = Mod.FindObject("UIBackground");
        ObjectSpecialClear *SpecialClear = Mod.FindObject("SpecialClear");

        RSDK.ResetEntitySlot(0, UIBackground->classID, NULL);
        RSDK.ResetEntitySlot(1, SpecialClear->classID, NULL);

        RSDK.AddDrawListRef(DRAWGROUP_COUNT - 2, 1);

#if MANIA_USE_PLUS
        if (globals->gameMode == MODE_ENCORE)
            UIBackground->activeColors = &UIBackground->bgColors[18];
#endif

        self->visible = false;
        self->state   = StateMachine_None;
    }
}
