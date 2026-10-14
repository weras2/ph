#include "Player/EquipHammer.hpp"

THUMB EquipHammer::EquipHammer() {
    mState       = EQUIP_HAMMER_STATE_IDLE;
    mChargeTimer = 40;
    mUnk_24      = 0;
    mUnk_28      = 0x1000;
}

THUMB EquipHammer::~EquipHammer() {}

THUMB void EquipHammer::vfunc_10() {}

ARM ItemFlag EquipHammer::GetId() const {
    return ItemFlag_Hammer;
}

ARM bool EquipHammer::GetHitbox(Cylinder *hitbox) const {
    if (IsInUse() && mUnk_24 > 0 && mState > EQUIP_HAMMER_STATE_IDLE) {
        Vec3p pos;
        pos           = mUnk_0c;
        hitbox->pos.x = pos.x;
        hitbox->pos.y = pos.y;
        hitbox->pos.z = pos.z;
        hitbox->size  = MUL_Q20(mUnk_28, 0x4cd);
        return true;
    }
    return false;
}

ARM s32 EquipHammer::vfunc_4c() const {
    return 0x333;
}
