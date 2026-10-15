#pragma once

#include "global.h"
#include "types.h"

#include "Save/SaveItemManager.hpp"
#include "System/SysNew.hpp"

class PlayerManager : public SysObject {
public:
    /* 00 */ s16 mMaxHealth;
    /* 02 */ s16 mHealth;
    /* 04 */ s16 mMaxShipHealth;
    /* 06 */ s16 mShipHealth;
    /* 08 */ s16 mSalvageArmHealth;
    /* 0a */ u16 mFlags;
    /* 0c */ unk16 mUnk_0c;
    /* 0e */ unk8 mUnk_0e;
    /* 0f */ unk8 mUnk_0f;
    /* 10 */

    void Save(SaveItemManager *save);
    void IncreaseMaxHealth(s16 amount);
    void UpdateShipMaxHealth();

    static void Create();
    static void Destroy();
    PlayerManager();
    ~PlayerManager();
    void Init(bool param1);
    void func_ov004_02108008();
};

extern PlayerManager *gPlayerManager;
