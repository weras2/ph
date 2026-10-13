#include "Actor/ActorManager.hpp"
#include "DTCM/UnkStruct_027e077c.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "Message/MsgProc.hpp"
#include "Player/EquipBombchu.hpp"
#include "Player/PlayerBase.hpp"

extern void *data_027e0d3c;
extern unk32 data_02063e4c;

extern "C" {
unk32 func_ov000_02079470(void *param1, Vec3p *param2, unk32 param3, unk32 param4, unk32 *param5, unk32 *param6, unk32 param7,
                          unk32 param8);
void func_020313c8(unk32 *param1, unk32 param2, unk32 param3, u32 param4, UnkStruct_01ffbe34 *param5);
void func_ov000_0208967c(UnkStruct_027e0f64_04 *param1, unk32 param2, Vec3p *param3, const Vec3p *param4, unk32 param5,
                         unk32 param6);
}

static inline bool Vec3p_IsZero(Vec3p *vec) {
    return vec->x == 0 && vec->y == 0 && vec->z == 0;
}

THUMB EquipBombchu::EquipBombchu() {
    mUnk_14 = 0;
    mUnk_18 = 0;
    mUnk_1c = (TilePos *) new(data_027e0ce0[1], 4) EquipBombchu_Unk1[100];
}

ARM EquipBombchu_Unk1::EquipBombchu_Unk1() {
    mUnk_0 = 0;
    mUnk_1 = 0;
}

THUMB EquipBombchu::~EquipBombchu() {
    if (mUnk_1c != NULL) {
        delete[] (EquipBombchu_Unk1 *) mUnk_1c;
    }
}

ARM void EquipBombchu::func_ov014_0213eba4() {
    Vec3p vel;
    vel.x = gPlayerVel.x;
    vel.y = gPlayerVel.y;
    vel.z = gPlayerVel.z;
    if (!Vec3p_IsZero(&vel)) {
        this->func_ov014_0213ec64();
    }
    if (mUnk_14 == 0) {
        return;
    }
    if (mUnk_14 != 1) {
        return;
    }
    func_ov000_0208967c(data_027e0f64->mUnk_4, 7, &mUnk_20, &gVec3p_ZERO, 0, 1);
}

ARM void EquipBombchu::func_ov014_0213ec40() {
    Actor *bombchu = this->func_ov014_0213ed74();
    if (bombchu != NULL) {
        *((u8 *) bombchu + 0x17e) = true;
    }
    mUnk_14 = 0;
}

ARM void EquipBombchu::func_ov014_0213ec64() {
    Actor *bombchu = this->func_ov014_0213ed74();
    if (bombchu != NULL) {
        *((u8 *) bombchu + 0x17e) = false;
    }
    if (data_027e0f64->mUnk_4->mUnk_15c == 54) {
        data_027e0f64->mUnk_4->func_ov000_0208726c(0);
    }
    mUnk_14 = 0;
}

ARM ItemFlag EquipBombchu::GetId() const {
    return ItemFlag_BombchuBag;
}

ARM void EquipBombchu::vfunc_34(unk16 *param1) {
    u16 buttons = *param1;
    if (!(buttons & 4) && !(buttons & 8)) {
        return;
    }
    unk32 x;
    unk32 y;
    if (!func_ov000_02079470(data_027e0d3c, &mUnk_38, 0, 0, &x, &y, 1, 0) || !mUnk_46) {
        return;
    }
    if (data_027e077c.mUnk_0 != 13) {
        return;
    }
    UnkStruct_01ffbe34 sprite;
    func_01ffbe34(&sprite);
    sprite.mUnk_04 = 2;
    func_020313c8(&data_02063e4c, x, y, 11, &sprite);
}

ARM Actor *EquipBombchu::func_ov014_0213ed74() const {
    return gActorManager->GetActor((ActorRef *) &mBombchuRef);
}

ARM void *EquipBombchu::func_ov014_0213ed94(s32 param1) {
    return &mUnk_1c[param1];
}

THUMB void EquipBombchu::func_ov014_0213eda0() {
    mUnk_18 = 0;
    mUnk_47 = true;
    mUnk_48 = false;
    mUnk_46 = false;
    mUnk_44 = 0;
}
