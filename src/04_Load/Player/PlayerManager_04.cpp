#include "DTCM/UnkStruct_027e0d38.hpp"
#include "Game/Game.hpp"
#include "Item/ItemManager.hpp"
#include "Item/ItemModelLoader.hpp"
#include "Message/MsgProc.hpp"
#include "Player/PlayerControl.hpp"
#include "Player/PlayerLink.hpp"
#include "Player/PlayerManager.hpp"

struct UnkStruct_ov000_020e9e98 {
    /* 00 */ unk8 mUnk_00[0x10];
    /* 10 */ u8 mMaxHealth;
    /* 11 */ u8 mHealth;
    /* 12 */ u8 mSalvageArmHealth;
    /* 13 */ unk8 mUnk_13[0x13];
    /* 26 */ u16 mFlags;
};

extern "C" {
extern s16 sDefaultMaxHealth;
extern s16 sDefaultMaxShipHealth;
extern const s16 data_ov000_020dc7ca;
extern UnkStruct_ov000_020e9e98 data_ov000_020e9e98;
extern u16 data_ov000_020e9e94[];
extern unk32 data_ov009_0211f530;

void Copy16(const void *src, void *dst, u32 size);
void func_ov009_02115fe4(unk32 *param1);
void func_ov009_0211bfe0();
void func_ov009_0211c0d8();
void func_ov009_0211c0fc();
void func_ov009_0211c004();
void func_ov009_02116070(unk32 *param1);
void func_ov012_021192f4();
void func_ov015_0213cf30();
void func_ov015_02139510();
void func_ov015_0213cf78();
s32 func_ov000_0209d758(UnkClass_data_027e0f7c *param1, s32 param2);
}

THUMB void PlayerManager::Create() {
    gPlayerManager = new(data_027e0ce0[1], 4) PlayerManager();
}

THUMB void PlayerManager::Destroy() {
    delete gPlayerManager;
    gPlayerManager = NULL;
}

THUMB PlayerManager::PlayerManager() {
    s16 health        = sDefaultMaxHealth;
    mMaxHealth        = health;
    mHealth           = health;
    s16 shipHealth    = sDefaultMaxShipHealth;
    mMaxShipHealth    = shipHealth;
    mShipHealth       = shipHealth;
    mSalvageArmHealth = 5;
    mFlags            = 0;
    mUnk_0c           = 0;
    mUnk_0e           = 0;
    mUnk_0f           = 0;
    PlayerControl::Create();
    ItemManager::Create();
    if (gGame.mModeId == 2) {
        mMaxHealth        = data_ov000_020e9e98.mMaxHealth;
        mHealth           = data_ov000_020e9e98.mHealth;
        mSalvageArmHealth = data_ov000_020e9e98.mSalvageArmHealth;
        mFlags            = data_ov000_020e9e98.mFlags;
        Copy16(data_ov000_020e9e94, &mUnk_0c, 4);
        gItemManager->Load(&gSaveItemManager);
    }
    gPlayerControl->func_ov00_020aef30();
    gItemManager->ClearPrevEquippedItem();
    UpdateShipMaxHealth();
    mShipHealth = mMaxShipHealth;
}

THUMB PlayerManager::~PlayerManager() {
    ItemManager::Destroy();
    PlayerControl::Destroy();
}

THUMB void PlayerManager::Init(bool param1) {
    if (param1) {
        mHealth = data_ov000_020dc7ca;
    } else if (mHealth <= 0) {
        mHealth = 1;
    }
    ItemModelLoader::Create();
    if (gGame.mModeId == 2) {
        func_ov009_02115fe4(&data_ov009_0211f530);
        func_ov009_0211bfe0();
        func_ov009_0211c0d8();
    }
    switch (data_027e0d38->func_ov000_02078b40()) {
        case 4:
            func_ov012_021192f4();
            break;
        case 2:
            if (param1) {
                mShipHealth = mMaxShipHealth;
            }
            func_ov015_0213cf30();
            func_ov015_02139510();
            break;
        case 0: {
            s32 result = func_ov000_0209d758(data_027e0f7c, data_027e0d38->mUnk_0c.func_ov000_020a5e9c());
            if (result != 7 && result != 9) {
                mShipHealth = mMaxShipHealth;
            }
            PlayerLink::Create();
            break;
        }
        default:
            PlayerLink::Create();
            break;
    }
    gItemManager->Init();
    gPlayerControl->Init();
}

THUMB void PlayerManager::func_ov004_02108008() {
    PlayerControl::func_ov004_0210b1f0();
    gPlayerControl->func_ov004_0210b1d0();
    gItemManager->func_ov004_021076bc();
    if (gGame.mModeId == 2) {
        func_ov009_0211c0fc();
        func_ov009_0211c004();
        func_ov009_02116070(&data_ov009_0211f530);
    }
    ItemModelLoader::Destroy();
    if (data_027e0d38->func_ov000_02078b40() == 2) {
        func_ov015_0213cf78();
    }
}
