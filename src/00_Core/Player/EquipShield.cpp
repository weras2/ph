#include "Player/EquipShield.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Item/ItemManager.hpp"
#include "Player/PlayerControl.hpp"
#include "nds/g3d/sbc.h"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

extern "C" {
void func_ov000_020c0e24(UnkStruct_ov000_020c0c08 *param1, unk32 param2);
void func_ov000_020b1d3c(Vec3p *param1);
void func_ov000_020b41c4(ModelRender *param1);
void func_020197fc(void *param1, s32 param2);
}
extern s16 data_02053f54[];
extern const Vec3p data_ov000_020dd364;
extern unk8 data_027e037c[];

ARM void EquipShield::vfunc_00() {}

ARM ItemFlag EquipShield::GetId() const {
    return ItemFlag_WoodenShield;
}

ARM bool EquipShield::IsUsable(unk32 param1) const {
    if (gPlayerControl->mUsingEquipItem) {
        return false;
    }
    return EquipItem::IsUsable(1);
}

ARM void EquipShield::func_ov000_020c070c(u32 param1, Vec3p *param2, unk32 param3) {
    mUnk_0b = this->IsUsable(1);
    mUnk_18 = param3;
    if (!mUnk_0b) {
        return;
    }
    if ((s32) param1 < 0) {
        return;
    }
    data_027e0ffc.func_ov000_020ceacc((u16) param1, param2, 0);
}

THUMB void EquipShield::vfunc_10() {}

ARM void EquipShield::vfunc_18() {
    mUnk_0a = true;
    func_ov000_020c0e24(mUnk_14, 0);
    mUnk_0b = false;
    mUnk_0c = mUnk_0c | ((s32) gItemManager->GetActiveFairyLevel(FairyId_Wisdom) >= 1);
    if (!mUnk_0c) {
        return;
    }
    func_ov000_020c0e24(mUnk_20, 0);
    func_ov000_020c0e24(mUnk_24, 0);
    func_ov000_020c0e24(mUnk_28, 0);
}

ARM void EquipShield::vfunc_1c() {
    mUnk_0a = false;
}

ARM void EquipShield::vfunc_30() {
    mUnk_14->func_ov000_020c0e04();
    if (mUnk_0c && !mUnk_0b) {
        if (mUnk_20->mUnk_0c.func_0202e58c()) {
            mUnk_0c = false;
        } else {
            mUnk_20->func_ov000_020c0e04();
            mUnk_24->func_ov000_020c0e04();
            mUnk_28->func_ov000_020c0e04();
        }
    }
    mUnk_09 = false;
}

ARM void EquipShield::vfunc_38(unk32 param1) {
    if (this->GetAmmo() > 0 && gItemManager->HasItem(ItemFlag_WoodenShield) && mUnk_0d && mUnk_0e != 0) {
        if (this->IsInUse()) {
            G3d_RestoreMtx_inline(30);
        } else {
            G3d_RestoreMtx_inline(28);
            Mat3p rot;
            Mat3p_InitZRotation(&rot, data_02053f54[0], data_02053f54[1]);
            G3d_MtxMult33_inline(&rot);
            Vec3p trans = data_ov000_020dd364;
            PushGeometryCommand(0x1c, &trans, 3);
        }

        Vec3p pos;
        func_ov000_020b1d3c(&pos);
        s16 alpha = mUnk_0e;
        if (alpha >= 0) {
            func_020197fc(mUnk_10->GetLcdcAddress(), alpha);
        } else {
            func_020197fc(mUnk_10->GetLcdcAddress(), 31);
        }

        if ((!this->IsInUse() && mUnk_0e < 31) || mUnk_0e == 0) {
            PushGeometryCommand(0x17, data_027e037c + 0x4c, 12);
        } else {
            func_ov000_020b41c4(mUnk_10);
        }

        if (mUnk_0c) {
            u16 angle = mUnk_04;
            s32 sin   = SIN(angle);
            s32 cos   = COS(angle);
            pos.x += MUL_Q20(sin, FLOAT_TO_Q20(0.2));
            pos.z += MUL_Q20(cos, FLOAT_TO_Q20(0.2));
            mUnk_1c->func_ov000_020b413c(mUnk_04, &pos);
        }
    }
    mUnk_0e = 31;
}

ARM bool EquipShield::GetHitbox(Cylinder *hitbox) const {
    Vec3p pos;
    ((EquipShield *) this)->func_ov000_020be99c(&pos);
    if (!mUnk_09) {
        return false;
    }
    q20 offset    = 0x19a;
    hitbox->pos.x = pos.x + MUL_Q20(SIN((u16) mUnk_04), offset);
    hitbox->pos.y = pos.y;
    hitbox->pos.z = pos.z + MUL_Q20(COS((u16) mUnk_04), offset);
    hitbox->size  = FLOAT_TO_Q20(0.5) - offset;
    return true;
}
