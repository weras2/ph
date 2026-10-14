#include "Player/EquipItem.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "Item/ItemManager.hpp"
#include "Player/PlayerBase.hpp"

struct EquipItem_Sprite {
    /* 00 */ unk32 mUnk_00[6];
    /* 18 */
};

extern "C" {
void func_ov000_020d0a30(EquipItem_Sprite *param1, s32 param2, s32 param3, s32 param4, s32 param5);
void func_ov000_020d0b7c(EquipItem_Sprite *param1, s32 param2, s32 param3, q20 param4, q20 param5, s16 param6, s32 param7,
                         s32 param8);
bool func_01ffe468(UnkStruct_027e0f64_04 *param1, Vec3p *param2, s32 *param3, s32 *param4, bool param5);
}

ARM void EquipItem::vfunc_00() {}

ARM void EquipItem::vfunc_1c() {}

ARM bool EquipItem::IsUsable(unk32 param1) const {
    return GetAmmo() > 0;
}

ARM bool EquipItem::IsInUse() const {
    return mInUse;
}

ARM bool EquipItem::UpdateInUse(unk32 param1) {
    bool inUse = false;
    if (param1 != 0) {
        bool usable = true;
        if (GetAmmo() <= 0) {
            ItemFlag forced = gItemManager->mForcedItem;
            if (forced != GetId()) {
                usable = false;
            }
        }
        if (usable) {
            inUse = true;
        }
    }
    return mInUse = inUse;
}

ARM u32 EquipItem::vfunc_2c() {
    return 0;
}

ARM void EquipItem::vfunc_34(unk16 *param1) {}

ARM unk32 EquipItem::vfunc_40() const {
    return 0;
}

ARM unk32 EquipItem::vfunc_44(unk32 param1) const {
    return 0;
}

ARM unk32 EquipItem::vfunc_48(unk32 param1) const {
    return 0;
}

ARM s32 EquipItem::vfunc_4c() const {
    return 0;
}

ARM Vec3p *EquipItem::GetPlayerPos() {
    return &gPlayerPos;
}

ARM void EquipItem::func_ov000_020be99c(Vec3p *param1) {
    Cylinder hitbox;
    gPlayer->vfunc_10(&hitbox);
    param1->x = hitbox.pos.x;
    param1->y = hitbox.pos.y;
    param1->z = hitbox.pos.z;
}

ARM void EquipItem::func_ov000_020be9e4(Vec3p param3, s16 param4) {
    EquipItem_Sprite sprite;
    func_ov000_020d0a30(&sprite, 0x53, 2, 2, 2);
    s16 angle = param4;
    q20 scale = MUL_Q20(MUL_Q20(COS((u16) (angle * 0xaab)), 0x266) + 0xb33, 0x20);
    Vec3p pos;
    pos.x = param3.x;
    pos.y = param3.y + 0x666;
    pos.z = param3.z;
    s32 x;
    s32 y;
    if (!func_01ffe468(data_027e0f64->mUnk_4, &pos, &x, &y, false)) {
        return;
    }
    func_ov000_020d0b7c(&sprite, x, y, scale, scale, angle * 0x2d8, 0, 0);
}

ARM s32 EquipItem::GetAmmo() const {
    ItemManager *itemManager = gItemManager;
    return itemManager->GetAmmo(GetId());
}

ARM void EquipItem::GiveAmmo(u32 amount) {
    ItemManager *itemManager = gItemManager;
    itemManager->GiveAmmo(GetId(), amount);
}

ARM bool EquipItem::GetHitbox(Cylinder *hitbox) const {
    hitbox->pos.x = 0;
    hitbox->pos.y = 0;
    hitbox->pos.z = 0;
    hitbox->size  = 0;
    return false;
}
