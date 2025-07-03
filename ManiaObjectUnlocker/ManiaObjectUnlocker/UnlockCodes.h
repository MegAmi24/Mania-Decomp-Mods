#ifndef UNLOCKCODES_H
#define UNLOCKCODES_H

#include "GameAPI/Game.h"

#define FileIO                                          FILE
#define fOpen(path, mode)                               fopen(path, mode)
#define fRead(buffer, elementSize, elementCount, file)  fread(buffer, elementSize, elementCount, file)
#define fGets(buffer, maxCount, file)                   fgets(buffer, maxCount, file)
#define fSeek(file, offset, whence)                     fseek(file, offset, whence)
#define fTell(file)                                     ftell(file)
#define fClose(file)                                    fclose(file)
#define fWrite(buffer, elementSize, elementCount, file) fwrite(buffer, elementSize, elementCount, file)

#if defined __ANDROID__
#undef fOpen
FileIO *fOpen(const char *path, const char *mode);
#endif

#define MAX_LEN (256)

#define UNLOCK_MAX (0x100)

typedef struct {
    const char *code;   // Patch line in Codes.lst
    const char *unlock; // Unlock name
} UnlockCode;

extern char activeUnlocks[UNLOCK_MAX][MAX_LEN];
extern int32 unlockedCount;

void Trim(char *str);
void InitUnlocks(void);
bool32 CheckUnlock(const char *unlock);

#endif //! UNLOCKCODES_H
