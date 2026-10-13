#include "Player/EquipBow.hpp"
#include "Actor/ActorSpawner.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Item/ItemManager.hpp"
#include "Player/LinkStateItem.hpp"
#include "Player/PlayerBase.hpp"
#include "Player/PlayerControl.hpp"
#include "System/Random.hpp"
#include "nds/g3d/sbc.h"

extern "C" {
void func_ov000_020b17ec(Mat4x3p *param1, Vec3p param2, s32 param3, s32 param4, s32 param5);
void func_ov000_020b41c4(ModelRender *param1);
bool IsXzDistWithin(Vec3p *param1, Vec3p *param2, s32 dist);
bool func_ov000_02087f08(UnkStruct_027e0f64_04 *param1, unk32 param2);
void func_ov000_0208967c(UnkStruct_027e0f64_04 *param1, unk32 param2, Vec3p *param3, const Vec3p *param4, unk32 param5,
                         unk32 param6);
}

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

ARM void EquipBow::vfunc_00() {
    gModelRenderBow.Init_RenderObject(gItemManager->GetItemModel(ItemModelId_Bow));
    gModelRenderArrow.Init_RenderObject(gItemManager->GetItemModel(ItemModelId_Arrow));
}

ModelRender EquipBow::gModelRenderBow(0);
ModelRender EquipBow::gModelRenderArrow(0);
static Mat4x3p data_ov056_021994d0;
static const Vec3p data_ov056_0219931c = {0x400, -0x333, -0xcd};

ARM bool EquipBow::IsUsable(unk32 param1) const {
    if (this->GetAmmo() > 0 || gItemManager->mForcedItem == ItemFlag_Bow) {
        return true;
    }
    return false;
}

ARM void EquipBow::vfunc_18() {
    func_ov000_020b17ec(&data_ov056_021994d0, data_ov056_0219931c, 0x4eef, 0x38e, 0x2aab);
    mUnk_0a = false;
    mUnk_0b = false;
    mUnk_0c = false;
}

ARM void EquipBow::vfunc_30() {
    this->IsInUse();
}

static LinkStateItem *GetLinkStateItem();

ARM void EquipBow::vfunc_38(unk32 param1) {
    if (!this->IsInUse()) {
        return;
    }
    if (mUnk_0b) {
        return;
    }
    G3d_RestoreMtx_inline(30);
    func_ov000_020b41c4(&gModelRenderBow);
    if (!GetLinkStateItem()->func_ov056_021992f8() || !mUnk_0a) {
        return;
    }
    if (this->GetAmmo() <= 0 && gItemManager->mForcedItem != ItemFlag_Bow) {
        return;
    }
    G3d_RestoreMtx_inline(29);
    G3d_MtxMult43_inline(&data_ov056_021994d0);
    func_ov000_020b41c4(&gModelRenderArrow);
}

ARM static LinkStateItem *GetLinkStateItem() {
    return (LinkStateItem *) GetLinkState(LinkStateId_Item);
}

ARM bool EquipBow::func_ov056_02198ee8() {
    bool wasDrawn = mUnk_0a;
    mUnk_0a       = true;
    if (!wasDrawn && (this->GetAmmo() > 0 || gItemManager->mForcedItem == ItemFlag_Bow)) {
        data_027e0ffc.func_ov000_020cebcc(0xdf, mUnk_04, 0);
    }
    return wasDrawn;
}

ARM void EquipBow::func_ov056_02198f48(u16 param1) {
    mUnk_0a = false;
    if (this->GetAmmo() <= 0 && gItemManager->mForcedItem != ItemFlag_Bow) {
        return;
    }
    if (mUnk_0b || mUnk_0c) {
        return;
    }

    Vec3p pos = *this->GetPlayerPos();
    pos.y += 0x800;
    ActorSpawnOptions options;
    options.mUnk_1c.id         = 1;
    options.mAngle             = mUnk_04;
    options.mUnk_00.mUnk_00[0] = (u8) param1;
    u16 variant                = gRandom.Next(0, 2) == 0;
    if (variant) {
        variant = mUnk_09;
    }
    options.mUnk_00.mUnk_00[1] = variant;
    if (gActorSpawner->Spawn(ActorTypeId_Arrow, &pos, &options, NULL) >= 0 && gItemManager->mForcedItem != ItemFlag_Bow) {
        this->GiveAmmo(-1);
    }
    data_027e0ffc.func_ov000_020cebcc(0xe0, mUnk_04, 0);
}

static LinkStateBase_UnkStruct1 data_ov056_021993e0 = {0x2e, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(30.0)}};
static LinkStateBase_UnkStruct1 data_ov056_021993f0 = {0x2f, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(5.0)}};

ARM void LinkStateItem::func_ov056_021990c0() {
    this->func_ov00_020a89bc(&data_ov056_021993e0, 1);
    mUnk_2c   = 0;
    mUnk_44.x = gVec3p_ZERO.x;
    mUnk_44.y = gVec3p_ZERO.y;
    mUnk_44.z = gVec3p_ZERO.z;
    gPlayerControl->ResetAim();
    mUnk_25[5] = 0;
}

EquipBow *GetEquipBow();

ARM void LinkStateItem::func_ov056_0219911c() {
    if (data_ov056_021993e0.mUnk_00 == this->Get_PlayerControlData_Unk100()) {
        EquipBow *bow = GetEquipBow();
        if (mUnk_2c > 5 && (gPlayerControl->CheckTouching(1) ? false : true)) {
            bow->mUnk_04 = *(s16 *) this->GetPlayerAngle();
            bow->func_ov056_02198f48(0x80);
            this->func_ov00_020a89bc(&data_ov056_021993f0, 1);
            mUnk_2c = 1;
            return;
        }

        Vec3p target;
        if (gPlayerControl->func_ov00_020b0e54(&target, &mUnk_44)) {
            bow->mUnk_0c = IsXzDistWithin(&target, this->GetPlayerPos(), 0x800);
            this->LookAt(&target);
            if (!GetEquipBow()->func_ov056_02198ee8()) {
                mUnk_2c = 1;
            }
            mUnk_25[5] = 1;
        }
        if (mUnk_2c > 0) {
            mUnk_2c++;
        }
    } else if (this->func_ov00_020a8b3c(1)) {
        if (mUnk_2c > 0) {
            mUnk_2c--;
        } else {
            this->func_ov00_020a89bc(&data_ov056_021993e0, 1);
        }
    }

    if (!mUnk_25[5]) {
        return;
    }
    if (!func_ov000_02087f08(data_027e0f64->mUnk_4, 5)) {
        return;
    }
    Vec3p aimPos;
    Vec3p_Add(&mUnk_44, &gPlayerPos, &aimPos);
    func_ov000_0208967c(data_027e0f64->mUnk_4, 5, &aimPos, &gVec3p_ZERO, 0, 0);
}

ARM EquipBow *GetEquipBow() {
    return (EquipBow *) ItemManager::GetEquipItemUnchecked(ItemFlag_Bow);
}

ARM bool LinkStateItem::func_ov056_021992f8() {
    return data_ov056_021993e0.mUnk_00 == this->Get_PlayerControlData_Unk120();
}
