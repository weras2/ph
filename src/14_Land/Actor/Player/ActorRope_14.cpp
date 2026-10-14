#include "Actor/Player/ActorArrow.hpp"
#include "Actor/Player/ActorRope.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Player/EquipRope.hpp"
#include "Player/PlayerControl.hpp"
#include "Player/PlayerLinkBase.hpp"
#include "Render/ModelRender.hpp"
#include "Save/AdventureFlags.hpp"
#include "System/SysNew.hpp"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

extern u32 **data_027e0fe0[];

extern "C" {
void func_ov000_020b3ea8(void *param1);
void func_ov000_0207a1a4(Actor_UnkStruct_0a4 *param1, u32 param2, bool param3);
void func_0202b4e4(Vec3p *param1, Vec3p *param2, s32 param3, s32 param4, s32 param5);
void func_ov000_0208967c(UnkStruct_027e0f64_04 *param1, unk32 param2, Vec3p *param3, const Vec3p *param4, unk32 param5,
                         unk32 param6);
}

static inline void AddPoint(ActorRope_PointList *list, Vec3p *point) {
    func_ov014_0213e544(list, point);
}

ActorType ActorRope::gType(ActorTypeId_GrapplingHook, (ActorCreateFunc) ActorRope::Create, NULL);

ARM ActorRope *ActorRope::Create() {
    return new(*data_027e0fe0[0], 4) ActorRope();
}

ARM void ActorRope::func_ov014_0212382c(Vec4p *vec) {
    vec->x = 0;
    vec->y = 0x333;
    vec->z = 0;
    vec->w = 0x800 - 0x333;
}

ARM q20 ActorRope::func_ov014_0212384c() {
    return 0x733;
}

ARM ActorRope::~ActorRope() {
    if (gPlayerLink != NULL) {
        ActorArrow::GetEquipRope()->func_ov014_0213db34();
    }
    func_ov000_020b3ea8(mUnk_158);
}

ARM s32 ActorRope::func_ov014_021238f0() {
    return mPos.y < mUnk_180.y ? mPos.y : mUnk_180.y;
}

ARM void ActorRope::func_ov014_02123904() {
    data_027e0ffc.func_ov000_020ceacc(0xf2, &mPos, 0);
    data_027e0e58->func_ov000_0207c1b0(4, &mPos, 1, 0, 0);
    func_ov014_02123960();
}

ARM bool ActorRope::func_ov014_02123960() {
    if (mUnk_164 <= ActorArrow::GetEquipRope()->func_ov014_0213dda0()) {
        mUnk_16c = true;
    }
    return func_ov014_02123e48(1);
}

ARM void ActorRope::vfunc_14(u32 param1) {
    if (func_ov00_020c313c(param1)) {
        if (mUnk_16b == 2) {
            mUnk_16b = 0;
        }
        EquipRope *rope = ActorArrow::GetEquipRope();
        mPrevPos.x      = mPos.x;
        mPrevPos.y      = mPos.y;
        mPrevPos.z      = mPos.z;
        Vec3p pos       = mPos;

        switch (mUnk_130) {
            case 0:
                func_ov057_0219a6b8();
                break;
            case 1:
                func_ov057_0219a850();
                break;
            case 2:
                if (!rope->func_ov014_0213e328()) {
                    mAlive = false;
                }
                func_ov014_02123e1c(0xb33);
                break;
            case 3:
                if (!rope->func_ov014_0213d4c8() && !rope->func_ov014_0213d6e0()) {
                    func_ov014_02123e48(4);
                } else {
                    if (!rope->func_ov014_0213e328()) {
                        mAlive = false;
                    }
                    Vec3p_Add(&mPos, &mVel, &mPos);
                    rope->func_ov014_0213d404((unk32 *) &mUnk_180);
                }
                break;
            case 4:
                break;
        }

        mUnk_16a = mUnk_16a && gPlayerControl->IsNotTouching();
        if (mUnk_16a && rope->func_ov014_0213d6e0()) {
            Vec3p target;
            rope->func_ov014_0213d404((unk32 *) &target);
            func_0202b4e4(&pos, &target, 0x800, 0, 0x7fffffff);
            func_ov000_0208967c(data_027e0f64->mUnk_4, 6, &pos, &mVel, 0, 0);
        }
    }

    mUnk_0a4.func_ov000_0207a1c8(param1, &mPos);
    bool visible;
    if (param1) {
        visible = mUnk_0a4.mUnk_01;
    } else {
        visible = mUnk_0a4.mUnk_00;
    }
    if (visible) {
        return;
    }
    mUnk_18c.func_ov000_0207a1c8(param1, &mUnk_180);
    bool ropeVisible;
    if (param1) {
        ropeVisible = mUnk_18c.mUnk_01;
    } else {
        ropeVisible = mUnk_18c.mUnk_00;
    }
    func_ov000_0207a1a4(&mUnk_0a4, param1, ropeVisible);
}

ARM void ActorRope::vfunc_18(u32 param1) {
    if (gAdventureFlags->func_ov00_02097738()) {
        switch (mUnk_130) {
            case 2:
                vfunc_14(param1);
                break;
            case 3:
                if (ActorArrow::GetEquipRope()->func_ov014_0213d4c8()) {
                    vfunc_14(param1);
                } else {
                    mAlive = false;
                    return;
                }
                break;
        }
    }
    if (!gAdventureFlags->func_ov00_02097738()) {
        gAdventureFlags->func_ov00_02097750();
    }
}

ARM void ActorRope::func_ov014_02123c54(s32 param1) {
    if ((mUnk_130 == 2 && param1 == 1) || (mUnk_130 == 3 && param1 == 0)) {
        EquipRope_Unk_18 *point = &ActorArrow::GetEquipRope()->mUnk_18[param1];
        if (func_ov014_02123cd0(&point->vec, 0) && mUnk_16d) {
            if (point->mUnk_19 == 2) {
                mUnk_16d = false;
            }
        }
        Vec3p_Add(&mPos, &mVel, &mPos);
    }
}

ARM bool ActorRope::func_ov014_02123cd0(Vec3p *param1, s32 param2) {
    Vec3p diff;
    Vec3p_Sub(param1, &mPos, &diff);
    if (param2 != 0) {
        diff.x = MUL_Q20(diff.x, 0x800);
        diff.y = MUL_Q20(diff.y, 0x800);
        diff.z = MUL_Q20(diff.z, 0x800);
        if (Vec3p_SetLength(&diff, 0x13b2, &mVel)) {
            mAngle = FX_Atan2Idx(diff.x, diff.z);
            return false;
        }
    } else {
        if (Vec3p_SetLength(&diff, MUL_Q20(ActorArrow::GetEquipRope()->mUnk_74, 0xe66), &mVel)) {
            mAngle = (s16) FX_Atan2Idx(diff.x, diff.z) - 0x8000;
            return false;
        }
    }
    return true;
}

ARM bool ActorRope::func_ov014_02123e1c(s32 param1) {
    EquipRope *rope = ActorArrow::GetEquipRope();
    mUnk_180.x      = rope->mUnk_18[0].vec.x;
    mUnk_180.y      = rope->mUnk_18[0].vec.y;
    mUnk_180.z      = rope->mUnk_18[0].vec.z;
    return true;
}

ARM bool ActorRope::func_ov014_02123e48(s32 state) {
    mUnk_130 = state;
    switch (state) {
        case 0:
            mUnk_164 = 0;
            break;
        case 1: {
            ActorArrow::GetEquipRope()->mUnk_74 = 0;
            s32 count                           = ActorArrow::GetEquipRope()->func_ov014_0213dda0();
            s16 max                             = mUnk_164 - 1;
            s32 value                           = max;
            if (count <= max) {
                value = count;
            }
            mUnk_166 = value;
        } break;
        case 2:
        case 3:
            if (!ActorArrow::GetEquipRope()->func_ov014_0213d9ac()) {
                mAlive = false;
            } else {
                mVel.x = 0;
                mVel.y = 0;
                mVel.z = 0;
            }
            break;
        case 4:
            ActorArrow::GetEquipRope()->func_ov014_0213dba4(&mPos);
            mAlive = false;
            break;
    }
    return true;
}

ARM void ActorRope::vfunc_20(bool param1) {
    bool visible;
    if (param1) {
        visible = mUnk_0a4.mUnk_01;
    } else {
        visible = mUnk_0a4.mUnk_00;
    }
    if (!visible || mUnk_130 == 4) {
        return;
    }

    EquipRope *rope = ActorArrow::GetEquipRope();
    if (mUnk_16d) {
        ((ModelRender *) mUnk_158)->func_ov000_020b413c(mAngle, &mPos);
    }

    ActorRope_PointList list;
    list.mCount = 0;
    AddPoint(&list, &mUnk_180);

    s16 max   = rope->func_ov014_0213dda0() + 1;
    s16 count = mUnk_164;
    if (count >= max) {
        count = max;
    }
    if (count > 0) {
        AddPoint(&list, &rope->mUnk_18[0].vec);
    }
    if (mUnk_16b) {
        AddPoint(&list, &mUnk_174);
        mUnk_16b = 2;
    }
    if (count > 1) {
        AddPoint(&list, &rope->mUnk_18[1].vec);
    }
    AddPoint(&list, &mPos);
    func_ov014_0213e55c(&list);
}

THUMB void ActorRope::vfunc_10(u32 param1) {
    mAlive = func_ov014_02123e48(4);
}
#pragma thumb off
