#include "Item/ItemManager.hpp"
#include "Item/ItemModelLoader.hpp"
#include "Player/EquipShield.hpp"
#include "Unknown/UnkStruct_ov000_020e5868.hpp"

extern const ItemManager_Unk1 data_ov004_0210f940;
extern char data_ov004_0210f954[];
extern char data_ov004_0210f968[];
extern char data_ov004_0210f97c[];
extern char data_ov004_0210f990[];

THUMB EquipShield::EquipShield() :
    mUnk_09(0),
    mUnk_0a(0),
    mUnk_0b(0),
    mUnk_0c(0),
    mUnk_0d(1),
    mUnk_0e(31),
    mUnk_10(NULL),
    mUnk_14(NULL) {
    ItemModel *model = gItemManager->GetItemModel(ItemModelId_WoodenShield);
    mUnk_10          = new(data_027e0ce0[1], 4) ModelRender(model);
    unk32 anim       = (unk32) gItemManager->func_ov00_020ad538(&data_ov004_0210f940);
    mUnk_14          = new(data_027e0ce0[1], 4) UnkStruct_ov004_0210b6a8(anim, model, 4);
    mUnk_14->func_ov000_020c0e5c(1);
    mUnk_10->vfunc_24(mUnk_14);

    if (gItemModelLoader->HasUnk_18()) {
        ItemModel *dungeonModel = gItemModelLoader->func_ov000_020bb3f4(data_ov004_0210f954);
        mUnk_1c                 = new(data_027e0ce0[1], 4) ModelRender(dungeonModel);
        unk32 anim1             = gItemModelLoader->func_ov000_020bb414((unk32) data_ov004_0210f968);
        mUnk_20                 = new(data_027e0ce0[1], 4) UnkStruct_ov004_0210b6a8(anim1, dungeonModel, 4);
        mUnk_20->func_ov000_020c0e5c(1);
        unk32 anim2 = gItemModelLoader->func_ov000_020bb420((unk32) data_ov004_0210f97c);
        mUnk_24     = new(data_027e0ce0[1], 4) UnkStruct_ov004_0210b67c(anim2, dungeonModel, 4);
        mUnk_20->func_ov000_020c0e5c(1);
        mUnk_28 = new(data_027e0ce0[1], 4) UnkStruct_ov000_020e5868(
            gItemModelLoader->func_ov000_020bb42c((unk32) data_ov004_0210f990), (ItemModel *) mUnk_1c->GetLcdcAddress(), 4);
        mUnk_1c->vfunc_24(mUnk_20);
        mUnk_1c->vfunc_24(mUnk_24);
        mUnk_1c->vfunc_24(mUnk_28);
    } else {
        mUnk_1c = NULL;
        mUnk_20 = NULL;
        mUnk_24 = NULL;
        mUnk_28 = NULL;
    }
}

THUMB EquipShield::~EquipShield() {
    if (mUnk_28 != NULL) {
        delete mUnk_28;
    }
    if (mUnk_24 != NULL) {
        delete mUnk_24;
    }
    if (mUnk_20 != NULL) {
        delete mUnk_20;
    }
    if (mUnk_1c != NULL) {
        delete mUnk_1c;
    }
    if (mUnk_14 != NULL) {
        delete mUnk_14;
    }
    if (mUnk_10 != NULL) {
        delete mUnk_10;
    }
}
