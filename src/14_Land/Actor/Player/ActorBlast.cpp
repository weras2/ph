#include "Actor/Player/ActorBlast.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Map/MapManager.hpp"
#include "Player/PlayerControl.hpp"
#include "System/SysNew.hpp"

ActorType ActorBlast::gType = ActorType(ActorTypeId_Blast, (ActorCreateFunc) ActorBlast::Create, NULL);

extern void *data_027e1038;
extern u32 **data_027e0fe0[];

extern "C" {
void func_ov000_020cef10(void *param1, Vec3p *param2);
void func_ov000_02088000(UnkStruct_027e0f64_04 *param1, unk32 param2);
void func_ov000_0208967c(UnkStruct_027e0f64_04 *param1, unk32 param2, Vec3p *param3, const Vec3p *param4, unk32 param5,
                         unk32 param6);
}

class ActorBlast_MapObject {
public:
    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08();
    /* 0c */ virtual void vfunc_0c();
    /* 10 */ virtual void vfunc_10();
    /* 14 */ virtual void vfunc_14();
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual void vfunc_1c();
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
    /* 54 */ virtual ActorBlast_MapObject *vfunc_54();
};

class ActorBlast_MapObjectInfo {
public:
    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08();
    /* 0c */ virtual void vfunc_0c();
    /* 10 */ virtual void vfunc_10();
    /* 14 */ virtual void vfunc_14();
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual void vfunc_1c();
    /* 20 */ virtual void vfunc_20();
    /* 24 */ virtual void vfunc_24();
    /* 28 */ virtual void vfunc_28();
    /* 2c */ virtual void vfunc_2c();
    /* 30 */ virtual void vfunc_30();
    /* 34 */ virtual void vfunc_34();
    /* 38 */ virtual void vfunc_38();
    /* 3c */ virtual void GetPos(Vec3p *pos);
};

ARM ActorBlast *ActorBlast::Create() {
    ActorBlast *blast = new(*data_027e0fe0[0], 4) ActorBlast();
    return blast;
}

ARM bool ActorBlast_Unk1::vfunc_10(s32 *param1) {
    ActorBlast_MapObject *obj      = (ActorBlast_MapObject *) param1;
    ActorBlast_MapObjectInfo *info = (ActorBlast_MapObjectInfo *) obj->vfunc_54();
    Vec3p pos;
    if (info == NULL) {
        pos.x = 0;
        pos.y = 0;
        pos.z = 0;
    } else {
        info->GetPos(&pos);
    }
    if (pos.x == 0 && pos.y == 0 && pos.z == 0) {
        return false;
    }
    if (pos.y - mBlast->mPos.y > FLOAT_TO_Q20(0.5)) {
        return false;
    }
    return UnkStruct_ov000_020beba8::vfunc_10(param1);
}

static inline void SetCylinder(Cylinder *cylinder, Vec3p *pos, q20 size) {
    cylinder->pos.x = pos->x;
    cylinder->pos.y = pos->y;
    cylinder->pos.z = pos->z;
    cylinder->size  = size;
}

ARM ActorBlast::ActorBlast() {
    mUnk_15c = 0xa00;
    SetCylinder(&mHitbox, (Vec3p *) &gVec3p_ZERO, 0xa00);
    SetCylinder(&mUnk_08c, (Vec3p *) &gVec3p_ZERO, mUnk_15c);
    SetCylinder(&mUnk_0a4.mUnk_04, (Vec3p *) &gVec3p_ZERO, FLOAT_TO_Q20(2.0));
}

ARM ActorBlast::~ActorBlast() {}

ARM bool ActorBlast::Init() {
    mUnk_125 = 12;
    mUnk_160 = 24;
    mPos.y += FLOAT_TO_Q20(0.5);
    mUnk_09c.mUnk_0 = 0xcf;
    data_027e0ffc.func_ov000_020ceacc(0x1ad, &mPos, 0);
    func_ov000_020cef10(data_027e1038, &mPos);
    func_ov000_02088000(data_027e0f64->mUnk_4, 8);

    if (data_027e0f64->mUnk_4->mUnk_15c == 29) {
        data_027e0e58->func_ov000_0207c1b0(0x268, &mPos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x269, &mPos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x26a, &mPos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x26b, &mPos, 2, 0, 0);
    } else if (mUnk_020.mUnk_00[0] != 0) {
        data_027e0e58->func_ov000_0207c1b0(0x1fe, &mPos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x1ff, &mPos, 2, 0, 0);
    } else {
        data_027e0e58->func_ov000_0207c1b0(0x203, &mPos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x204, &mPos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x205, &mPos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x206, &mPos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x207, &mPos, 2, 0, 0);
    }
    mUnk_158 = mUnk_020.mUnk_00[1] != 0;
    return true;
}

ARM void ActorBlast::vfunc_14(u32 param1) {
    if (this->func_ov00_020c313c(param1)) {
        mPrevPos.x = mPos.x;
        mPrevPos.y = mPos.y;
        mPrevPos.z = mPos.z;

        mUnk_15c += 0x19a;
        if (mUnk_15c <= FLOAT_TO_Q20(1.0)) {
            mHitbox.size  = mUnk_15c;
            mUnk_08c.size = mUnk_15c;
        } else {
            mUnk_15c     = FLOAT_TO_Q20(1.0);
            mHitbox.size = -1;
        }

        u32 ref[2];
        Actor::func_ov00_020c23c4((ActorRef *) ref, this);
        mUnk_158 = mUnk_158 && gPlayerControl->IsNotTouching();
        if (mUnk_158) {
            func_ov000_0208967c(data_027e0f64->mUnk_4, 7, &mPos, &mVel, 0, 0);
        }

        mUnk_160--;
        if (mUnk_160 <= 0) {
            mAlive = false;
        } else {
            if (this->XzDistanceToLink() < FLOAT_TO_Q20(1.0)) {
                mUnk_124 = 4;
            } else {
                mUnk_124 = 2;
            }
            this->func_ov00_020c1e2c(1, NULL);
        }

        ActorBlast_Unk1 hit(this);
        if (mHitbox.size > 0) {
            Vec3p prev;
            prev.x = mPrevPos.x;
            prev.y = mPrevPos.y;
            prev.z = mPrevPos.z;
            Vec3p pos;
            pos.x = mPos.x;
            pos.y = mPos.y;
            pos.z = mPos.z;
            gMapManager->func_01ffbe78((UnkStruct *) &hit.mUnk_10, &pos, &prev, (Sphere *) &mUnk_08c, mRef.id, 4, (unk32) &hit,
                                       0);
        }
    }
    mUnk_0a4.func_ov000_0207a1c8(param1, &mPos);
}

ARM ActorBlast_Unk1::~ActorBlast_Unk1() {}

ARM void ActorBlast::vfunc_18(u32 param1) {
    if (this->func_ov00_020c313c(param1)) {
        mUnk_15c += 0x19a;
        if (mUnk_15c > FLOAT_TO_Q20(1.0)) {
            mUnk_15c = FLOAT_TO_Q20(1.0);
        }
        mUnk_158 = mUnk_158 && gPlayerControl->IsNotTouching();
        mUnk_160--;
        if (mUnk_160 <= 0) {
            mAlive = false;
        }
    }
    mUnk_0a4.func_ov000_0207a1c8(param1, &mPos);
}
