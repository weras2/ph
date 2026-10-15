#include "Actor/ActorManager.hpp"
#include "Actor/ActorShopItem.hpp"
#include "Actor/ActorSpawner.hpp"
#include "DTCM/UnkStruct_027e0d38.hpp"
#include "Game/Game.hpp"
#include "Item/ItemManager.hpp"
#include "Item/ItemModelLoader.hpp"
#include "Player/Bhio.hpp"
#include "Player/EquipBomb.hpp"
#include "Player/EquipBombchu.hpp"
#include "Player/EquipBoomerang.hpp"
#include "Player/EquipBow.hpp"
#include "Player/EquipHammer.hpp"
#include "Player/EquipPotion.hpp"
#include "Player/EquipRope.hpp"
#include "Player/EquipScoop.hpp"
#include "Player/EquipShield.hpp"
#include "Player/EquipSword.hpp"
#include "Render/ModelRender.hpp"

struct ItemModelName {
    /* 00 */ char mName[0x10];
};

extern const ItemModelName data_ov000_020dc574[];
extern const ItemModelName data_ov000_020dc674[];
extern char data_ov004_02110520[];

extern "C" {
void Fill32(unk32, u32 *, unk32);
void Fill16(int value, unsigned short *dst, int size);
u32 *func_0201e24c(void *param1, const void *param2);
void func_ov000_020b8720();
void func_ov000_020b8754();
}

THUMB ItemManager::ItemManager() {
    mEquippedItem        = ItemFlag_None;
    mForcedItem          = ItemFlag_None;
    mHourglassSandFrames = 36000;
    mEquippedFairy       = 0;
    mNumRupees           = 0;
    mQuiverSize          = 0;
    mBombBagSize         = 0;
    mBombchuBagSize      = 0;
    mUnk_0ba             = 0;
    mFanfareSfx          = 0;
    mUnk_124             = NULL;
    Fill32(0, mItemFlags.flags, sizeof(mItemFlags));
    Fill32(0, &mSalvagedTreasureFlags, sizeof(mSalvagedTreasureFlags));
    Fill32(0, (u32 *) &mShipPartPricesShown, sizeof(mShipPartPricesShown));
    Fill32(0, mTreasurePriceShownFlags, sizeof(mTreasurePriceShownFlags));
    mMuteNextFanfare = false;
    mUnk_14d         = 0;

    mEquipItems =
        (EquipItem * (*) [ItemFlag_EQUIP_COUNT]) SysObject::operator new[](sizeof(*mEquipItems), data_027e0ce0[1], 4);
    Fill32(0, (u32 *) mEquipItems, sizeof(*mEquipItems));
    mAmmo = (u16(*)[ItemFlag_EQUIP_COUNT]) SysObject::operator new[](sizeof(*mAmmo), data_027e0ce0[1], 4);
    Fill16(0, (u16 *) mAmmo, sizeof(*mAmmo));
    if (gGame.mModeId == 6) {
        (*mAmmo)[0] = 0;
        (*mAmmo)[1] = 1;
        mItemFlags.flags[0] |= 2;
    }

    for (s32 i = 0; i < ShipPart_COUNT; i++) {
        mEquippedShipParts[i] = 0;
        for (s32 j = 0; j < ShipType_COUNT; j++) {
            mShipParts[i][j] = -1;
        }
    }
    for (s32 i = 0; i < Treasure_COUNT; i++) {
        mTreasure[i] = -1;
    }
    for (s32 i = 0; i < FishType_COUNT; i++) {
        mFishCount[i] = 0;
        mFishSize[i]  = 0;
    }
}

THUMB void ItemManager::Init() {
    mFanfareItemModel = new(data_027e0ce0[1], 4) ActorShopItemCollectable_Unk1(0x4000, 0x1000, 0xc00, 0x500, 0, 0x068a0000);

    u8 *items = gItemModelLoader->func_ov000_020bb34c(2);
    for (s32 i = 0; i < ItemModelId_COUNT; i++) {
        mItemModels[i] = (ItemModel *) (items + *func_0201e24c(items + 8, &data_ov000_020dc574[i]));
    }
    gItemModelLoader->func_ov000_020bb390(6);
    gItemModelLoader->func_ov000_020bb390(7);
    gItemModelLoader->func_ov000_020bb390(8);
    gItemModelLoader->func_ov000_020bb390(9);

    if (gItemModelLoader->mDungeonItems != 0) {
        u8 *dungeonItems = gItemModelLoader->func_ov000_020bb34c(3);
        for (s32 i = 0; i < DungeonItemModelId_COUNT; i++) {
            mDungeonItemModels[i] = (ItemModel *) (dungeonItems + *func_0201e24c(dungeonItems + 8, &data_ov000_020dc674[i]));
        }
        gItemModelLoader->func_ov000_020bb390(10);
        gItemModelLoader->func_ov000_020bb390(11);
    } else {
        Fill32(0, (u32 *) mDungeonItemModels, sizeof(mDungeonItemModels));
    }

    mUnk_114     = new(data_027e0ce0[1], 4) ModelRender(NULL);
    mFanfareItem = 0;
    mUnk_124     = new(data_027e0ce0[1], 4) Bhio();
    mUnk_124->vfunc_20(0, data_ov004_02110520, 'IMNG', 'ROOT', 0, 0);

    if (data_027e0d38->mUnk_14 == 1) {
        func_ov004_02107650();
        return;
    }
    switch (data_027e0d38->func_ov000_02078b40()) {
        case 3:
            InitEquipItems();
            break;
        case 2:
            func_ov004_02107648();
            break;
        case 4:
            func_ov004_02107650();
            break;
        default:
            InitEquipItems();
            break;
    }
    mEquipLoadTimer = 1;
    mUnk_14d        = 0;
}

THUMB ItemManager::~ItemManager() {
    SysObject::operator delete[](mAmmo);
    SysObject::operator delete[](mEquipItems);
}

THUMB void ItemManager::InitEquipItems() {
    (*mEquipItems)[ItemFlag_OshusSword]   = new(data_027e0ce0[1], 4) EquipSword();
    (*mEquipItems)[ItemFlag_WoodenShield] = new(data_027e0ce0[1], 4) EquipShield();
    (*mEquipItems)[3]                     = new(data_027e0ce0[1], 4) EquipScoop();
    (*mEquipItems)[4]                     = new(data_027e0ce0[1], 4) EquipBomb();
    (*mEquipItems)[5]                     = new(data_027e0ce0[1], 4) EquipBow();
    (*mEquipItems)[2]                     = new(data_027e0ce0[1], 4) EquipBoomerang();
    (*mEquipItems)[7]                     = new(data_027e0ce0[1], 4) EquipBombchu();
    (*mEquipItems)[6]                     = new(data_027e0ce0[1], 4) EquipRope();
    (*mEquipItems)[8]                     = new(data_027e0ce0[1], 4) EquipHammer();
    (*mEquipItems)[9]                     = new(data_027e0ce0[1], 4) EquipPotionA();
    (*mEquipItems)[10]                    = new(data_027e0ce0[1], 4) EquipPotionB();
    func_ov004_02107698();
}

THUMB void ItemManager::func_ov004_02107648() {
    func_ov004_02107698();
}

THUMB void ItemManager::func_ov004_02107650() {
    (*mEquipItems)[ItemFlag_OshusSword]   = new(data_027e0ce0[1], 4) EquipSword();
    (*mEquipItems)[ItemFlag_WoodenShield] = new(data_027e0ce0[1], 4) EquipShield();
    func_ov004_02107698();
}

THUMB void ItemManager::func_ov004_02107698() {
    for (s32 i = 0; i < ItemFlag_EQUIP_COUNT; i++) {
        EquipItem *item = (*mEquipItems)[i];
        if (item != NULL) {
            item->vfunc_10();
        }
    }
}

THUMB void ItemManager::func_ov004_021076bc() {
    UnequipPotion();
    if (mUnk_124 != NULL) {
        delete mUnk_124;
    }
    for (s32 i = 0; i < FairyId_COUNT; i++) {
        mFairies[i] = NULL;
    }
    for (s32 i = ItemFlag_EQUIP_COUNT - 1; i >= 0; i--) {
        if ((*mEquipItems)[i] != NULL) {
            delete(*mEquipItems)[i];
            (*mEquipItems)[i] = NULL;
        }
    }
    if (mUnk_114 != NULL) {
        delete mUnk_114;
        mUnk_114 = NULL;
    }
    if (mFanfareItemModel != NULL) {
        delete mFanfareItemModel;
        mFanfareItemModel = NULL;
    }
    func_ov000_020b8754();
}

THUMB void ItemManager::SpawnFairies() {
    for (s32 i = 0; i < FairyId_COUNT; i++) {
        mFairies[i] = NULL;
    }
    if (data_027e0d38->mUnk_14 == 1) {
        return;
    }
    func_ov000_020b8720();
    if (data_027e0d38->func_ov000_02078b40() == 2) {
        return;
    }
    ActorSpawnOptions options;
    mFairies[FairyId_Courage] = (ActorNaviBase *) gActorManager->FindActorById(
        gActorSpawner->Spawn(ActorTypeId_Navi, (Vec3p *) &gVec3p_ZERO, &options, NULL));
    mFairies[FairyId_Power] = (ActorNaviBase *) gActorManager->FindActorById(
        gActorSpawner->Spawn(ActorTypeId_ForceNavi, (Vec3p *) &gVec3p_ZERO, &options, NULL));
    mFairies[FairyId_Wisdom] = (ActorNaviBase *) gActorManager->FindActorById(
        gActorSpawner->Spawn(ActorTypeId_WisdomNavi, (Vec3p *) &gVec3p_ZERO, &options, NULL));
}
