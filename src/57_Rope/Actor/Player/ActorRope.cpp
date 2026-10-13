#include "Actor/Player/ActorRope.hpp"
#include "DTCM/UnkStruct_027e0f6c.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Item/ItemManager.hpp"
#include "Map/MapManager.hpp"
#include "Player/EquipRope.hpp"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

ActorRope_Unk_0219a3b0 gUnk_0219a3b0;

EquipRope *GetEquipRope();

ARM bool ActorRope_Unk_0219a3b0::vfunc_08(UnkStruct_ov000_020beba8_08 *param1) {
    u32 flags;
    UnkStruct_027e0f6c::func_ov000_02093a1c(&flags, data_027e0f6c, param1->mUnk_00);
    if (((flags >> 7) & 3) == 2) {
        return false;
    }
    return UnkStruct_ov000_020beba8::vfunc_08(param1);
}

struct ActorRope_MapObject {
    /* 00 */ unk32 mUnk_00;
    /* 04 */ u32 mFlags;
    /* 08 */ unk8 mUnk_08[0xc];
    /* 14 */ TilePos mTile;
};

ARM bool ActorRope_Unk_0219a3b0::vfunc_10(s32 *param1) {
    ActorRope_MapObject *obj = (ActorRope_MapObject *) param1;
    if (obj->mFlags & 0x20) {
        TilePos tile = obj->mTile;
        if (GetEquipRope()->func_ov057_0219922c(tile)) {
            return false;
        }
    }
    return UnkStruct_ov000_020beba8::vfunc_10(param1);
}

ARM ActorRope::ActorRope() :
    mUnk_158(gItemManager->GetItemModel(ItemModelId_RopeTop)),
    mUnk_16b(0),
    mUnk_16c(0),
    mUnk_16d(1),
    mUnk_18c(0, FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(1.0)) {
    func_ov014_0212382c((Vec4p *) &mUnk_08c);
    q20 size     = func_ov014_0212384c();
    mHitbox.pos  = gVec3p_ZERO;
    mHitbox.size = size;
    mUnk_16e     = -1;
    mUnk_164     = 0;
    mUnk_166     = 0;

    mUnk_0a4.mUnk_04.pos  = gVec3p_ZERO;
    mUnk_0a4.mUnk_04.size = mHitbox.size + FLOAT_TO_Q20(1.0);
    mUnk_18c.mUnk_04.pos  = gVec3p_ZERO;
    mUnk_18c.mUnk_04.size = mHitbox.size + FLOAT_TO_Q20(1.0);
}

ARM bool ActorRope::Init() {
    this->func_ov014_02123e48(0);
    mUnk_168        = 45;
    mUnk_09c.mUnk_4 = &gUnk_0219a3b0;
    mUnk_16a        = 1;
    GetEquipRope()->func_ov014_0213d404(&mUnk_180);
    return true;
}

ARM q20 ActorRope::func_ov057_0219a5ac() {
    EquipRope *rope = GetEquipRope();
    Vec3p target;
    while (rope->func_ov057_0219939c(&target, mUnk_164)) {
        q20 dist = Vec3p_Distance(&mPos, &target);
        if (mUnk_168 != 0 && dist > 0x666) {
            this->func_ov014_02123cd0(&target, 1);
            mUnk_170 = mAngle - 0x8000;
            return dist;
        }
        mUnk_168 = 45;
        mUnk_164++;
    }
    s32 count = rope->func_ov014_0213dda0();
    if (count >= 1 && mUnk_164 > count) {
        rope->mUnk_69 = true;
        this->func_ov014_02123e1c();
    }
    this->func_ov014_02123e48(1);
    return 0;
}

ARM void ActorRope::func_ov057_0219a6b8() {
    EquipRope *rope = GetEquipRope();
    Vec3p_Add(&mPos, &mVel, &mPos);
    data_027e0ffc.func_ov000_020cec60(0xed, &mPos, (Actor *) mRef.id, 0);
    rope->func_ov014_0213d404(&mUnk_180);
    gUnk_0219a3b0.mUnk_8 = 0;

    Vec3p pos;
    pos.x = mPos.x;
    pos.y = mPos.y;
    pos.z = mPos.z;
    Vec3p prev;
    prev.x = mPrevPos.x;
    prev.y = mPrevPos.y;
    prev.z = mPrevPos.z;
    if (gMapManager->func_01ffbe78((UnkStruct *) &mUnk_0b8, &pos, &prev, (Sphere *) &mUnk_08c, mRef.id, mUnk_09c.mUnk_0,
                                   (unk32) mUnk_09c.mUnk_4, 1)) {
        this->func_ov014_02123904();
        return;
    }
    mUnk_168--;
    if (mUnk_040.id != -1) {
        mPos.x = mPrevPos.x;
        mPos.y = mPrevPos.y;
        mPos.z = mPrevPos.z;
        this->func_ov014_02123960();
    } else {
        q20 dist = this->func_ov057_0219a5ac();
        if (dist > 0) {
            s32 index = mUnk_164;
            if ((u16) mUnk_164 <= 1 && rope->mUnk_18[index].mType == 4 && dist < FLOAT_TO_Q20(1.0)) {
                return;
            }
            u32 ref[2];
            Actor::func_ov00_020c23c4((ActorRef *) ref, this);
        }
    }
}

ARM void ActorRope::func_ov057_0219a850() {
    EquipRope *rope = GetEquipRope();
    Vec3p target;
    if (!rope->func_ov057_0219939c(&target, mUnk_166)) {
        this->func_ov014_02123e48(4);
    }
    if (Vec3p_Distance(&mPos, &target) <= 0xe66) {
        mPos.x = target.x;
        mPos.y = target.y;
        mPos.z = target.z;
        if (mUnk_166 == -1) {
            this->func_ov014_02123e48(4);
        } else if (mUnk_16c) {
            mUnk_166--;
        } else if (rope->mUnk_69) {
            this->func_ov014_02123e48(2);
        } else {
            this->func_ov014_02123e48(3);
        }
    } else {
        this->func_ov014_02123cd0(&target, 0);
        Vec3p_Add(&mPos, &mVel, &mPos);
    }
    data_027e0ffc.func_ov000_020cec60(0xed, &mPos, (Actor *) mRef.id, 0);
}

ARM ActorRope_Unk_0219a3b0::~ActorRope_Unk_0219a3b0() {}
