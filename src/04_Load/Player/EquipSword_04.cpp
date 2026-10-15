#include "Item/ItemModelLoader.hpp"
#include "Player/EquipSword.hpp"
#include "Unknown/UnkStruct_ov000_020e5868.hpp"

extern char data_ov004_0210f918[];
extern char data_ov004_0210f8f0[];
extern char data_ov004_0210f904[];
extern char data_ov004_0210f92c[];

THUMB EquipSword::EquipSword() :
    mUnk_0c(new(data_027e0ce0[1], 4) ModelRender(NULL)),
    mUnk_10(new(data_027e0ce0[1], 4) ModelRender(NULL)),
    mUnk_14(NULL),
    mUnk_18(NULL),
    mUnk_1c(NULL),
    mUnk_20(NULL),
    mUnk_24(NULL),
    mUnk_28(NULL),
    mUnk_38(-1),
    mUnk_3c(-1),
    mUnk_40(-1),
    mUnk_44(-1),
    mUnk_48(-1),
    mUnk_4c(0),
    mUnk_50(0),
    mUnk_54(0),
    mUnk_56(0),
    mUnk_58(0),
    mUnk_5a(0),
    mUnk_5c(31),
    mUnk_60(0),
    mUnk_64(0),
    mUnk_68(NULL) {
    mUnk_6c[0] = 0;
    mUnk_6c[1] = 0;
    mUnk_6e    = 0;
    if (gItemModelLoader->HasUnk_18()) {
        mUnk_14 = new(data_027e0ce0[1], 4) ModelRender(gItemModelLoader->func_ov000_020bb3f4(data_ov004_0210f918));
        mUnk_18 = new(data_027e0ce0[1], 4) ModelRender(gItemModelLoader->func_ov000_020bb3f4(data_ov004_0210f8f0));

        mUnk_1c = new(data_027e0ce0[1], 4) UnkStruct_ov004_0210b6a8(
            gItemModelLoader->func_ov000_020bb414((unk32) data_ov004_0210f904), (ItemModel *) mUnk_14->GetLcdcAddress(), 4);
        mUnk_1c->mUnk_0c.mUnk_04 = 0x1000;
        mUnk_20                  = new(data_027e0ce0[1], 4) UnkStruct_ov004_0210b67c(
            gItemModelLoader->func_ov000_020bb420((unk32) data_ov004_0210f904), (ItemModel *) mUnk_14->GetLcdcAddress(), 4);
        mUnk_20->mUnk_0c.mUnk_04 = 0x1000;
        mUnk_14->vfunc_24(mUnk_1c);
        mUnk_14->vfunc_24(mUnk_20);

        mUnk_24 = new(data_027e0ce0[1], 4) UnkStruct_ov004_0210b6a8(
            gItemModelLoader->func_ov000_020bb414((unk32) data_ov004_0210f92c), (ItemModel *) mUnk_18->GetLcdcAddress(), 4);
        mUnk_24->mUnk_0c.mUnk_04 = 0x1000;
        mUnk_28                  = new(data_027e0ce0[1], 4) UnkStruct_ov000_020e5868(
            gItemModelLoader->func_ov000_020bb42c((unk32) data_ov004_0210f92c), (ItemModel *) mUnk_18->GetLcdcAddress(), 4);
        mUnk_28->mUnk_0c.mUnk_04 = 0x1000;
        mUnk_18->vfunc_24(mUnk_24);
        mUnk_18->vfunc_24(mUnk_28);
    }
}

THUMB EquipSword::~EquipSword() {
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
    if (mUnk_18 != NULL) {
        delete mUnk_18;
    }
    if (mUnk_14 != NULL) {
        delete mUnk_14;
    }
    if (mUnk_10 != NULL) {
        delete mUnk_10;
    }
    if (mUnk_0c != NULL) {
        delete mUnk_0c;
    }
}
