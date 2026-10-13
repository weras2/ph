#include "Actor/Player/ActorBoomerang.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Item/ItemManager.hpp"
#include "Map/MapManager.hpp"
#include "Player/EquipBoomerang.hpp"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

EquipBoomerang *GetEquipBoomerang();

extern void func_ov000_020b7e6c(s32 *param1);
extern "C" void func_ov000_020b7df0(void *param1);
extern "C" void func_ov014_02123134(Cylinder *param1);

struct ActorBoomerang_TargetFlags {
    u32 mValue;
};

struct ActorBoomerang_TargetInfo {
    /* 00 */ unk8 mUnk_00[0xc];
    /* 0c */ ActorBoomerang_TargetFlags mFlags;
};

class ActorBoomerang_Target {
public:
    /* 00 (vtable) */
    /* 04 */ unk8 mUnk_04[0x10];
    /* 14 */ TilePos mTile;

    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08();
    /* 0c */ virtual void vfunc_0c();
    /* 10 */ virtual void vfunc_10();
    /* 14 */ virtual void vfunc_14();
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual s32 vfunc_1c();
    /* 20 */ virtual void vfunc_20();
    /* 24 */ virtual void vfunc_24();
    /* 28 */ virtual void vfunc_28();
    /* 2c */ virtual void vfunc_2c();
    /* 30 */ virtual void vfunc_30();
    /* 34 */ virtual void vfunc_34();
    /* 38 */ virtual void vfunc_38();
    /* 3c */ virtual void vfunc_3c();
    /* 40 */ virtual void vfunc_40();
    /* 44 */ virtual void vfunc_44();
    /* 48 */ virtual void vfunc_48();
    /* 4c */ virtual void vfunc_4c();
    /* 50 */ virtual void vfunc_50();
    /* 54 */ virtual ActorBoomerang_TargetInfo *vfunc_54();
};

ARM bool ActorBoomerang_Unk_0219a15c::vfunc_18(s32 *param1) {
    ActorBoomerang_Target *target   = (ActorBoomerang_Target *) param1;
    ActorBoomerang_TargetInfo *info = target->vfunc_54();
    ActorBoomerang_TargetFlags flags;
    if (info == NULL) {
        flags.mValue = 0;
    } else {
        flags = info->mFlags;
    }
    if (((flags.mValue >> 9) & 3) == 2) {
        mUnk_c = 1;
    }

    s32 type = target->vfunc_1c();
    if (type == 16 || type == 23 || type == 59) {
        TilePos tile = target->mTile;
        ::GetEquipBoomerang()->func_ov053_021990f0(tile);
    }
    return UnkStruct_ov000_020beba8::vfunc_18(param1);
}

ARM ActorBoomerang::ActorBoomerang() :
    mUnk_158(gItemManager->GetItemModel(ItemModelId_Boomerang)) {
    mHitbox.pos.x = 0;
    mHitbox.pos.y = -0x19a;
    mHitbox.pos.z = 0;
    mHitbox.size  = 0x666;

    mUnk_0a4.mUnk_04.pos.x = 0;
    mUnk_0a4.mUnk_04.pos.y = -0x19a;
    mUnk_0a4.mUnk_04.pos.z = 0;
    mUnk_0a4.mUnk_04.size  = 0x1666;

    mUnk_168 = true;
}

ARM ActorBoomerang_170::~ActorBoomerang_170() {
    func_ov000_020b7e6c((s32 *) this);
    func_ov000_020b7df0(this);
}

ARM bool ActorBoomerang::Init() {
    mUnk_125        = 8;
    mUnk_16c        = 0;
    mUnk_09c.mUnk_0 = 0xcf;
    this->func_ov014_0212357c(0);
    q20 sin = SIN(mAngle);
    q20 cos = COS(mAngle);
    q20 x   = MUL_Q20(sin, FLOAT_TO_Q20(0.5));
    q20 z   = MUL_Q20(cos, FLOAT_TO_Q20(0.5));
    mVel.x  = x;
    mVel.y  = 0;
    mVel.z  = z;
    return true;
}

ARM ActorBoomerang_170::ActorBoomerang_170() {
    mUnk_0 = 0;
    mUnk_4 = -1;
    mUnk_8 = 0;
}

ARM bool ActorBoomerang::func_ov053_02199c48(u16 param1) {
    Vec3p pos;
    pos.x = mPos.x;
    pos.y = mPos.y;
    pos.z = mPos.z;
    Vec3p prev;
    prev.x = mPrevPos.x;
    prev.y = mPrevPos.y;
    prev.z = mPrevPos.z;
    return gMapManager->func_01ffbe78((UnkStruct *) &mUnk_0b8, &pos, &prev, (Sphere *) &mUnk_08c, mRef.id, param1,
                                      (unk32) mUnk_09c.mUnk_4, 0);
}

ARM void ActorBoomerang::func_ov053_02199cc8(Vec3p *param1) {
    static ActorBoomerang_Unk_0219a15c sUnk;

    mUnk_09c.mUnk_4 = &sUnk;
    sUnk.mUnk_c     = 0;
    sUnk.mUnk_8     = 0;

    bool hit;
    {
        Vec3p pos;
        pos.x = mPos.x;
        pos.y = mPos.y;
        pos.z = mPos.z;
        hit   = mPos.y < gMapManager->MapData_vfunc_68(&pos, false);
    }
    func_ov014_02123134(&mUnk_08c);
    if (!hit) {
        hit = this->func_ov053_02199c48(0x84);
    }
    if (!hit) {
        mUnk_08c.size = 0;
        hit           = this->func_ov053_02199c48(0x4b);
    }
    if (hit) {
        data_027e0ffc.func_ov000_020ceacc(0x19d, &mPos, 0);
        mVel.x = 0;
        mVel.y = 0;
        mVel.z = 0;
        ::GetEquipBoomerang()->func_ov053_02199038();
        this->func_ov014_021230a8(&mPos);
        this->func_ov014_0212357c(1);
    }

    if (sUnk.mUnk_c != 0) {
        this->func_ov014_0212322c();
    }

    if (mUnk_166 < 0 || ::GetEquipBoomerang()->mUnk_1c == 0) {
        this->func_ov014_0212357c(1);
        return;
    }

    mUnk_166--;
    Vec3p target = ::GetEquipBoomerang()->func_ov053_0219902c(mUnk_164)->mPos;
    if (mUnk_166 > 0 && Vec3p_Distance(&mPos, &target) > 0x555) {
        this->func_ov014_021235bc(&target, 1);
        *param1 = target;
        return;
    }

    mUnk_166 = 45;
    mUnk_164++;
    EquipBoomerang *boomerang = ::GetEquipBoomerang();
    u16 index                 = mUnk_164;
    if (index >= boomerang->mUnk_1c) {
        mUnk_166 = -1;
        return;
    }
    EquipBoomerang_Point *point = ::GetEquipBoomerang()->func_ov053_0219902c(index);
    target.x                    = point->mPos.x;
    target.y                    = point->mPos.y;
    target.z                    = point->mPos.z;
    this->func_ov014_021235bc(&target, 1);
    *param1 = target;
}
