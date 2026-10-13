#include "Player/EquipPotion.hpp"
#include "DTCM/UnkStruct_027e0c54.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "DTCM/UnkStruct_027e103c.hpp"
#include "Item/ItemManager.hpp"
#include "Map/MapManager.hpp"
#include "Player/LinkStateItem.hpp"
#include "Player/PlayerBase.hpp"
#include "Player/PlayerControlData.hpp"
#include "Save/AdventureFlags.hpp"
#include "Unknown/UnkStruct_020eec68.hpp"
#include "Unknown/UnkStruct_020eec9c.hpp"
#include "nds/g3d/sbc.h"

struct UnkStruct_ov000_02087d34 {
    /* 00 */ s32 mUnk_00;
    /* 04 */ s32 mUnk_04;
    /* 08 */ s32 mUnk_08;
    /* 0c */ s32 mUnk_0c;
    /* 10 */ s32 mUnk_10;
    /* 14 */ s32 mUnk_14;
    /* 18 */ s32 mUnk_18;
    /* 1c */ s32 mUnk_1c;
    /* 20 */ s32 mUnk_20;
    /* 24 */ s32 mUnk_24;
    /* 28 */ s32 mUnk_28;
    /* 2c */ s32 mUnk_2c;
    /* 30 */ s32 mUnk_30;
    /* 34 */ s32 mUnk_34;
    /* 38 */ s32 mUnk_38;
    /* 3c */ s32 mUnk_3c;
    /* 40 */ s32 mUnk_40;
    /* 44 */ s32 mUnk_44;
    /* 48 */ s32 mUnk_48;
    /* 4c */ s32 mUnk_4c;
    /* 50 */ s32 mUnk_50;
    /* 54 */ s32 mUnk_54;
    /* 58 */ s32 mUnk_58;
    /* 5c */ s32 mUnk_5c;
    /* 60 */ u8 mUnk_60;
    /* 61 */ u8 mUnk_61;
    /* 62 */ u8 mUnk_62;
    /* 63 */ u8 mUnk_63;
    /* 64 */ u8 mUnk_64;
    /* 65 */
};

extern "C" {
void func_ov000_020b41c4(ModelRender *param1);
void func_ov000_02087d34(UnkStruct_027e0f64_04 *param1, UnkStruct_ov000_02087d34 *param2);
s32 func_ov000_020c0d68(unk32 param1);
void func_02019570(void *param1, s32 param2, s32 param3);
void func_ov000_020d71a0(UnkStruct_020eec68 *param1);
}

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

ARM void EquipPotion::vfunc_00() {}

ARM void EquipPotion::vfunc_18() {}

ARM void EquipPotion::vfunc_1c() {
    data_027e103c->func_ov005_02103ff0();
    switch (gItemManager->mPotions[mUnk_0c]) {
        case Potion_Red:
            gPlayer->AddHealth(24);
            break;
        case Potion_Purple:
            gPlayer->AddHealth(32);
            break;
        case Potion_Yellow:
            gPlayer->AddHealth(1000);
            break;
    }
    gItemManager->SetPotion(mUnk_0c, Potion_None);
    gItemManager->EquipPreviousItem();
}

ARM void EquipPotion::vfunc_30() {}

ARM void EquipPotion::vfunc_38(unk32 param1) {
    ModelRender model(NULL);
    s32 material;
    switch (gItemManager->mPotions[mUnk_0c]) {
        case Potion_Red:
            model.Init_RenderObject(gItemManager->GetItemModel(ItemModelId_RedPotion));
            material = model.GetMaterialIndex("mat_rev_bin_2");
            break;
        case Potion_Purple:
            model.Init_RenderObject(gItemManager->GetItemModel(ItemModelId_PurplePotion));
            material = model.GetMaterialIndex("mat_rev_binP_2");
            break;
        case Potion_Yellow:
            model.Init_RenderObject(gItemManager->GetItemModel(ItemModelId_YellowPotion));
            material = model.GetMaterialIndex("mat_rev_binY_2");
            break;
    }
    if (func_ov000_020c0d68(gPlayerControlData->mUnk_138) < 0x4b000) {
        func_02019570(model.GetLcdcAddress(), material, 31);
    } else {
        func_02019570(model.GetLcdcAddress(), material, 0);
    }
    G3d_RestoreMtx_inline(29);
    func_ov000_020b41c4(&model);
}

ARM void LinkStateItem::func_ov055_021993b8() {
    mUnk_5c    = -1;
    mUnk_25[4] = 0;

    UnkStruct_ov000_0209a50c info;
    info.mUnk_04 = -1;
    info.mUnk_09 = 50;
    info.mUnk_0a = 3;
    info.mUnk_0b = 3;
    info.mUnk_16 = false;

    Vec3p pos    = *this->GetPlayerPos();
    info.mUnk_20 = pos.x;
    info.mUnk_24 = pos.y;
    info.mUnk_28 = pos.z;

    UnkStruct_ov000_02087d34 src;
    func_ov000_02087d34(data_027e0f64->mUnk_4, &src);
    src.mUnk_04 = 5;

    bool canDrink = false;
    if (!data_027e0c54.mUnk_0) {
        bool clear  = true;
        Vec3p front = {pos.x, pos.y, pos.z + FLOAT_TO_Q20(2.0)};
        s32 limit   = pos.y + FLOAT_TO_Q20(1.5);
        if (gMapManager->func_ov00_02083f44(&front, true) < limit) {
            Vec3p front2 = {pos.x, pos.y, pos.z + FLOAT_TO_Q20(3.0)};
            if (gMapManager->func_ov00_02083f44(&front2, true) < limit) {
                clear = false;
            }
        }
        if (clear) {
            canDrink = true;
        }
    }
    src.mUnk_10                                         = canDrink ? FLOAT_TO_Q20(2.0) : 0x105b;
    src.mUnk_0c                                         = 0x38e;
    src.mUnk_18                                         = 0xf000;
    src.mUnk_1c                                         = 0;
    src.mUnk_20                                         = FLOAT_TO_Q20(1.0);
    src.mUnk_24                                         = 0;
    *(UnkStruct_ov000_02087d34 *) ((u8 *) &info + 0x2c) = src;
    info.mUnk_14                                        = 1;
    info.mUnk_94                                        = 0x5c;

    mUnk_5c = gAdventureFlags->func_ov00_02097810(&info);
    data_027e103c->func_ov000_020cf9dc(1, 1);
    data_027e103c->mUnk_2a = 1;
}

static LinkStateBase_UnkStruct1 data_ov055_02199890 = {0x4c, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(126.0)}};

ARM void LinkStateItem::func_ov055_02199654() {
    if (!gAdventureFlags->func_ov00_02097b9c(mUnk_5c)) {
        return;
    }
    UnkStruct_ov000_02087d34 src;
    func_ov000_02087d34(data_027e0f64->mUnk_4, &src);
    s16 angle = src.mUnk_14;
    this->TurnTo(angle, angle, 0xe39);
    if (!mUnk_25[4]) {
        this->func_ov00_020a8a4c(&data_ov055_02199890, 0);
        mUnk_25[4] = 1;
    } else if (this->func_ov00_020a8b3c(0)) {
        gAdventureFlags->func_ov00_02097bcc(mUnk_5c);
        mUnk_5c = -1;
        this->ChangeLinkState(LinkStateId_Move);
        return;
    } else {
        if (this->func_ov00_020a8b04(0x44000, false)) {
            data_ov000_020eec9c.func_ov000_020d7a84(0x11c, this->GetPlayerPos());
        } else if (this->func_ov00_020a8b04(0x5f000, false)) {
            data_ov000_020eec9c.func_ov000_020d7a84(0x11b, this->GetPlayerPos());
        }
        this->func_ov00_020a8b04(0x4b000, false);
    }
    func_ov000_020d71a0(&data_ov000_020eec68);
}
