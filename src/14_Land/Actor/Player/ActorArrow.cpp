#include "Actor/Player/ActorArrow.hpp"
#include "Actor/ActorManager.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "DTCM/UnkStruct_027e0fd4.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Item/ItemManager.hpp"
#include "Player/EquipShield.hpp"
#include "Player/PlayerBase.hpp"
#include "Player/PlayerControl.hpp"
#include "Render/ModelRender.hpp"
#include "System/SysNew.hpp"
#include "Unknown/UnkStruct_ov000_020beba8.hpp"
#include "nds/g3d/sbc.h"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

extern u32 **data_027e0fe0[];
extern u32 data_ov000_020e9370[];

extern "C" {
bool func_ov000_0208ee4c(Cylinder *param1, Cylinder *param2, Vec3p *param3, s32 *param4);
void func_ov000_020a61ac(Vec3p *vec, s16 angle);
void func_ov000_020b18d8(Vec3p *param1, Vec3p *param2, s32 param3);
void func_02019570(void *param1, s32 param2, s32 param3);
void func_ov000_0208967c(UnkStruct_027e0f64_04 *param1, unk32 param2, Vec3p *param3, const Vec3p *param4, unk32 param5,
                         unk32 param6);
void func_ov005_02102c2c(u32 *param1, s32 param2, Vec3p *param3, s32 param4, s32 param5, s32 param6, u8 param7, u8 param8,
                         u8 param9, u8 param10);
}

typedef void (*ActorArrowCallback)(ActorArrow *arrow);

// ActorRef without the resetting constructor
struct ActorArrow_Ref {
    /* 0 */ s32 id;
    /* 4 */ s32 index;
};

static inline bool IsNotType10(u32 hit) {
    if ((hit & 0x1f) == 10) {
        return false;
    } else {
        return true;
    }
}

static const ActorTypeId sHitActorTypes[] = {ActorTypeId_Null};
static const Vec3p sTrailVertices[3]      = {
    {0, 0, -0x1000},
    {-0x140, 0, 0},
    {0x140, 0, 0},
};

ActorType ActorArrow::gType = ActorType(ActorTypeId_Arrow, (ActorCreateFunc) ActorArrow::Create, NULL);

ARM ActorArrow *ActorArrow::Create() {
    return new(*data_027e0fe0[0], 4) ActorArrow();
}

UnkStruct_ov000_020beba8 data_ov014_0215abec = UnkStruct_ov000_020beba8(0);
static ActorArrowCallback sCallback;

ARM void ActorArrow::func_ov014_0211fd80(unk32 param1) {
    sCallback = (ActorArrowCallback) param1;
}

ARM void ActorArrow::func_ov014_0211fd90() {
    sCallback = NULL;
}

static inline void SetCylinder(Cylinder *cylinder, Vec3p *pos, q20 size) {
    cylinder->pos.x = pos->x;
    cylinder->pos.y = pos->y;
    cylinder->pos.z = pos->z;
    cylinder->size  = size;
}

ARM ActorArrow::ActorArrow() :
    mUnk_16c(gItemManager->GetItemModel(4), 0, 0),
    mUnk_178(gItemManager->GetItemModel(5), 0, 0),
    mUnk_184((ModelRender *) &mUnk_16c),
    mUnk_188(0, 0x1000, 0, 0x1000) {
    mUnk_1ac      = 0;
    mUnk_1b2      = 0;
    mHitbox.pos   = gVec3p_ZERO;
    mHitbox.size  = 0x266;
    mUnk_08c.pos  = gVec3p_ZERO;
    mUnk_08c.size = 0x266;
    mUnk_158.x    = 0;
    mUnk_158.y    = 0;
    mUnk_158.z    = 0;
    mGravity      = 0;
}

ARM ActorArrow::~ActorArrow() {
    func_ov000_020b3ea8(&mUnk_178);
    func_ov000_020b3ea8(&mUnk_16c);
}

ARM bool ActorArrow::Init() {
    mUnk_125  = 8;
    mUnk_130  = 0;
    mUnk_1a4  = mUnk_020.mUnk_00[2] == 1 ? 120 : 60;
    u16 angle = mAngle;
    mVel.x    = MUL_Q20(SIN(angle), (mUnk_020.mUnk_00[0] << 4) + 0x400);
    mVel.y    = 0;
    mVel.z    = MUL_Q20(COS(angle), (mUnk_020.mUnk_00[0] << 4) + 0x400);
    mSpeed    = Vec3p_Length(&mVel);
    mUnk_19c  = 0;

    mUnk_0a4.mUnk_04.pos.x = mUnk_08c.pos.x;
    mUnk_0a4.mUnk_04.pos.y = mUnk_08c.pos.y;
    mUnk_0a4.mUnk_04.pos.z = mUnk_08c.pos.z;
    mUnk_0a4.mUnk_04.size  = 0x1266;

    mUnk_188.mUnk_04.pos.x = 0;
    mUnk_188.mUnk_04.pos.y = 0;
    mUnk_188.mUnk_04.pos.z = 0;
    mUnk_188.mUnk_04.size  = 0;

    mUnk_1a8 = -1;
    mUnk_1b4 = true;
    mUnk_1b5 = false;
    if (mUnk_020.mUnk_00[2] == 2) {
        mUnk_1b6 = true;
        mUnk_1b7 = true;
    } else {
        mUnk_1b6 = false;
        mUnk_1b7 = (s16) data_027e0fd4->mUnk_05a == 0;
    }
    mUnk_09c.mUnk_4 = &data_ov014_0215abec;
    return true;
}

ARM bool ActorArrow::CollidesWith(Actor *other) {
    bool result = false;
    if (other->mAlive && other->mHitbox.size >= 0 && mHitbox.size >= 0) {
        Cylinder otherHitbox;
        Cylinder hitbox;
        Vec3p vel;
        s32 unk;
        other->GetHitbox(&otherHitbox);
        GetHitbox(&hitbox);
        vel = mVel;
        if (func_ov000_0208ee4c(&otherHitbox, &hitbox, &vel, &unk)) {
            result = true;
        }
    }
    return result;
}

ARM void ActorArrow::func_ov014_021200d4() {
    mUnk_19c = MUL_Q20(mUnk_19c + mSpeed, 0xccd);
}

ARM void ActorArrow::func_ov014_02120118() {
    if (mUnk_130 != 0) {
        return;
    }
    if (mUnk_1b6) {
        mHitbox.size = 0x800;
        func_ov00_020c1fc8(PlayerCollide_Sword | PlayerCollide_Shield);
        mHitbox.size = 0x266;
    } else if (func_ov00_020c243c((ActorTypeId *) sHitActorTypes, NULL)) {
        func_ov014_02120dec(4);
    }
}

ARM bool ActorArrow::func_ov014_02120180() {
    if (mUnk_1b6) {
        Vec3p prevPos;
        Vec3p pos;
        Vec3p_Add(&mPrevPos, &mHitbox.pos, &prevPos);
        Vec3p_Add(&mPos, &mHitbox.pos, &pos);
        if (func_ov00_020c1f5c(&prevPos, &pos, mHitbox.size, &mVel, 1, 1)) {
            func_ov014_02120dec(4);
            return true;
        }
    } else {
        ActorArrow_Ref ref;
        Actor::func_ov00_020c23c4((ActorRef *) &ref, this);
        if (ref.id != -1) {
            if (mUnk_130 == 0) {
                func_ov014_021207b8((ActorRef *) &ref, 0, -0x266);
            }
            return true;
        }
    }

    Vec3p normal;
    Cylinder hitbox;
    GetHitbox(&hitbox);
    hitbox.size += 0x333;
    if (mUnk_1b7) {
        if (GetEquipRope()->func_ov014_0213dfbc(&hitbox, (s16) mAngle, &normal)) {
            GetEquipRope()->func_ov014_0213e144(&hitbox.pos, &normal, 0);
            func_ov000_020b18d8(&mVel, &normal, 0x1000);
            data_027e0ffc.func_ov000_020ceacc(0x19c, &mPos, 0);
            mAngle   = FX_Atan2Idx(mVel.x, mVel.z);
            mUnk_19c = 0;
        }
    }
    return false;
}

ARM EquipRope *ActorArrow::GetEquipRope() {
    return (EquipRope *) ItemManager::GetEquipItemUnchecked(ItemFlag_GrapplingHook);
}

void func_ov014_02120774(u32 *param1, s32 param2);

ARM void ActorArrow::vfunc_14(u32 param1) {
    if (func_ov00_020c313c(param1)) {
        mPrevPos.x = mPos.x;
        mPrevPos.y = mPos.y;
        mPrevPos.z = mPos.z;
        if (mUnk_130 != 4) {
            if (--mUnk_1a4 <= 0) {
                func_ov014_02120dec(4);
            }
        }
        if (!gPlayerControl->IsNotTouching()) {
            mUnk_1a8 = 0;
        } else if (mUnk_1a8 > 0) {
            mUnk_1a8--;
        }
        func_ov014_02120118();

        switch (mUnk_130) {
            case 0:
                if (ABS(mVel.x) > 2 || ABS(mVel.z) > 2) {
                    ApplyGravity();
                    Vec3p_Add(&mPos, &mVel, &mPos);
                    if (!mUnk_188.mUnk_00 && !mUnk_188.mUnk_01) {
                        u16 flags       = mUnk_09c.mUnk_0;
                        mUnk_09c.mUnk_0 = flags & ~4;
                        if (func_01fffd04(0)) {
                            mAlive = false;
                        }
                        mUnk_09c.mUnk_0 = flags;
                        break;
                    }
                    if (func_ov014_02120180()) {
                        break;
                    }
                    data_ov014_0215abec.mUnk_8 = 0;
                    if (func_01fffd04(0)) {
                        u32 hit;
                        func_ov014_02120774(&hit, (s32) &data_ov014_0215abec);
                        if (((hit >> 31) & 1) == 1) {
                            if (mUnk_1b4) {
                                data_027e0ffc.func_ov000_020ceacc(0x19a, &mPos, 0);
                                mUnk_184 = (ModelRender *) &mUnk_178;
                                mSpeed   = 0;
                                mUnk_1b2 = 0x1555;
                                func_ov014_02120dec(2);
                                if (sCallback != NULL) {
                                    sCallback(this);
                                }
                            }
                            func_ov014_02120da8();
                        } else {
                            Vec3p *normal = (Vec3p *) mUnk_0c4;
                            func_ov014_02120ac4((s16) FX_Atan2Idx(normal->x, normal->z), true);
                            if (sCallback != NULL) {
                                sCallback(this);
                            }
                            break;
                        }
                    } else if (mTouchingFloor) {
                        u32 hit;
                        func_ov014_02120774(&hit, (s32) &data_ov014_0215abec);
                        if (IsNotType10(hit)) {
                            Vec3p *normal = (Vec3p *) mUnk_0c4;
                            func_ov014_02120ac4((s16) FX_Atan2Idx(normal->x, normal->z), true);
                            break;
                        }
                        if (mUnk_1b4) {
                            data_027e0ffc.func_ov000_020ceacc(0x19a, &mPos, 0);
                            mUnk_184 = (ModelRender *) &mUnk_178;
                            mSpeed   = 0;
                            mUnk_1b2 = 0x1555;
                            func_ov014_02120dec(2);
                        }
                        func_ov014_02120da8();
                    }
                    func_ov014_02120d58();
                }
                break;
            case 3:
                mUnk_1ac += -0xe39;
                Vec3p_Add(&mPos, &mVel, &mPos);
                ApplyGravity();
                break;
            case 1: {
                Actor *actor = gActorManager->GetActor(&mUnk_164);
                if (actor != NULL) {
                    Vec3p offset;
                    offset.x  = mUnk_158.x;
                    offset.y  = mUnk_158.y;
                    offset.z  = mUnk_158.z;
                    s16 angle = (s16) actor->mAngle - mUnk_1ae;
                    mAngle    = mUnk_1b0 + angle;
                    func_ov000_020a61ac(&offset, angle);
                    Vec3p_Add(&offset, &actor->mPos, &mPos);
                } else {
                    u16 angle = mAngle;
                    q4 sin    = SIN(angle);
                    q4 cos    = COS(angle);
                    mVel.x    = MUL_Q20(sin, 0x400);
                    mVel.z    = MUL_Q20(cos, 0x400);
                    func_ov014_02120ac4((s16) mAngle + 0x8000, false);
                    break;
                }
                func_ov014_02120d58();
            }
            case 2:
                func_ov014_02120da8();
                break;
            case 4:
                break;
        }
        func_ov014_021200d4();
    }
    mUnk_0a4.func_ov000_0207a1c8(param1, &mPos);
    mUnk_188.func_ov000_0207a1c8(param1, &mPos);
}

ARM void func_ov014_02120774(u32 *param1, s32 param2) {
    *param1 = ((UnkStruct_ov000_020beba8 *) param2)->mUnk_8;
}

ARM void ActorArrow::vfunc_18(u32 param1) {
    if (mUnk_1b5) {
        vfunc_14(param1);
    }
}

ARM void ActorArrow::vfunc_10(u32 param1) {
    mAlive = func_ov014_02120dec(4);
}

ARM void ActorArrow::func_ov014_021207b8(ActorRef *ref, s32 param2, s32 param3) {
    if (mUnk_130 == 1) {
        return;
    }
    mUnk_164 = *ref;
    func_ov014_02120dec(1);

    Actor *actor = gActorManager->GetActor(&mUnk_164);
    if (actor != NULL) {
        mUnk_1ae = *(s16 *) &actor->mAngle;
        mUnk_1b0 = *(s16 *) &mAngle;

        Cylinder hitbox;
        Vec3p pos;
        Vec3p vel;
        pos.x = mPos.x;
        pos.y = mPos.y;
        pos.z = mPos.z;
        vel.x = mVel.x;
        vel.y = mVel.y;
        vel.z = mVel.z;
        actor->GetHitbox(&hitbox);
        q20 radius = param3 + (hitbox.size + mHitbox.size);
        Vec3p_Sub(&pos, &hitbox.pos, &pos);

        q20 a = Vec3p_Dot(&vel, &vel);
        q20 b = Vec3p_Dot(&vel, &pos);
        q20 c = Vec3p_Dot(&pos, &pos);

        s32 discriminant = MUL_Q20(b, b) - MUL_Q20(a, c - MUL_Q20(radius, radius));
        if (discriminant >= 0) {
            Vec3p_Axpy(CoDivide64By32(-(b + CoSqrt(discriminant)), a), &mVel, &mPos, &mPos);
        } else {
            Vec3p_Axpy(CoDivide64By32(-b, a), &mVel, &mPos, &mPos);
        }
        Vec3p_Sub(&mPos, &actor->mPos, &mUnk_158);
        mUnk_1a4 += param2;
    }
    mUnk_1b2 = 0x1555;
    func_ov014_02120da8();
    mUnk_184 = (ModelRender *) &mUnk_178;
    mVel     = gVec3p_ZERO;
}

ARM void ActorArrow::func_ov014_02120998(ActorRef *ref, Vec3p pos, s16 param3) {
    if (mUnk_130 == 1) {
        return;
    }
    mUnk_164 = *ref;
    func_ov014_02120dec(1);

    Actor *actor = gActorManager->GetActor(&mUnk_164);
    if (actor != NULL) {
        mUnk_1ae   = *(s16 *) &actor->mAngle;
        mUnk_1b0   = param3;
        mPos.x     = pos.x;
        mPos.y     = pos.y;
        mPos.z     = pos.z;
        mPrevPos.x = pos.x;
        mPrevPos.y = pos.y;
        mPrevPos.z = pos.z;
        Vec3p_Sub(&mPos, &actor->mPos, &mUnk_158);
    }
    mUnk_1b2 = 0x1555;
    func_ov014_02120da8();
    mUnk_184 = (ModelRender *) &mUnk_178;
    mVel     = gVec3p_ZERO;
}

ARM void func_ov014_02120a80(s32 param1, ActorArrow *arrow) {
    s16 *vec  = (s16 *) (param1 + 0x50);
    u16 angle = arrow->mAngle;
    q4 sin    = SIN(angle);
    q4 cos    = COS(angle);
    vec[0]    = -sin;
    vec[1]    = 0;
    vec[2]    = -cos;
}

ARM void ActorArrow::func_ov014_02120ac4(s16 angle, bool param2) {
    func_ov014_02120dec(3);

    Vec3p normal;
    normal.x = 0;
    normal.y = 0;
    normal.z = 0x1000;
    Vec3p vel1;
    vel1.x = mVel.x;
    vel1.y = mVel.y;
    vel1.z = mVel.z;
    Vec3p vel2;
    vel2.x = mVel.x;
    vel2.y = mVel.y;
    vel2.z = mVel.z;
    func_ov000_020a61ac(&normal, angle);
    Vec3p_Axpy(MUL_Q20(Vec3p_Dot(&vel1, &normal), -0x1800), &normal, &vel2, &vel2);
    Vec3p_Scale(&vel2, 0x400);
    mVel     = vel2;
    mUnk_184 = (ModelRender *) &mUnk_16c;

    if (param2) {
        Vec3p pos = mPos;
        mPos.x -= (SIN(mAngle) * 0x4cd + 0x800) >> 12;
        mPos.z -= (COS(mAngle) * 0x4cd + 0x800) >> 12;
        data_027e0ffc.func_ov000_020ceacc(0x19b, &pos, 0);
        data_027e0e58->func_ov000_0207c1b0(4, &pos, 2, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(5, &pos, 2, (unk32) this, (unk32) func_ov014_02120a80);
    }
    mGravity = 0;
}

ARM void ActorArrow::func_ov014_02120c98(Vec3p *param1) {
    Vec3p diff;
    Vec3p_Sub(param1, &mPos, &diff);
    s16 angle = FX_Atan2Idx(diff.x, diff.z);
    q4 sin    = SIN((u16) angle);
    q4 cos    = COS((u16) angle);
    mVel.x    = MUL_Q20(sin, 0x1000);
    mVel.z    = MUL_Q20(cos, 0x1000);
    func_ov014_02120ac4((s16) (angle + 0x8000), false);
}

ARM void ActorArrow::func_ov014_02120d58() {
    if (mUnk_1a8 > 0) {
        func_ov000_0208967c(data_027e0f64->mUnk_4, 5, &mPos, &mVel, 1, 1);
    }
}

ARM void ActorArrow::func_ov014_02120da8() {
    mVel     = gVec3p_ZERO;
    mUnk_1b2 = (-mUnk_1b2 * 15) >> 4;
    mUnk_1b4 = false;
}

ARM bool ActorArrow::func_ov014_02120dec(s32 state) {
    mUnk_130 = state;
    switch (state) {
        case 0:
            break;
        case 3:
            mUnk_19c = 0;
            mSpeed   = 0;
            mUnk_1a4 = 16;
            break;
        case 1:
        case 2:
            mUnk_1a4 = 32;
            mSpeed   = 0;
            break;
        case 4:
            mUnk_19c = 0;
            mSpeed   = 0;
            mAlive   = false;
            break;
    }
    return true;
}

static EquipShield *GetEquipShield();

ARM bool ActorArrow::vfunc_48(Knockback *param1) {
    switch (param1->mUnk_10) {
        case 2:
        case 3:
            GetEquipShield()->func_ov000_020c070c(0x18c, &mPos, 0);
        case 0:
        case 1: {
            Vec3p diff;
            Vec3p_Sub(&mPrevPos, &gPlayerPos, &diff);
            func_ov014_02120ac4((s16) FX_Atan2Idx(diff.x, diff.z), true);
        } break;
    }
    return true;
}

ARM static EquipShield *GetEquipShield() {
    return (EquipShield *) ItemManager::GetEquipItemUnchecked(ItemFlag_WoodenShield);
}

static inline void PushVertex(s16 x, s16 y, s16 z) {
    u32 data[2];
    data[0] = (u16) x | ((u16) y << 16);
    data[1] = (u16) z;
    PushGeometryCommand(0x23, data, 2);
}

static inline void PushCommand(u32 command, u32 value) {
    PushGeometryCommand(command, &value, 1);
}

ARM void ActorArrow::vfunc_20(bool param1) {
    bool visible;
    if (param1) {
        visible = mUnk_0a4.mUnk_01;
    } else {
        visible = mUnk_0a4.mUnk_00;
    }
    if (!visible || mUnk_130 == 4) {
        return;
    }

    Mat3p rotation;
    Vec3p pos = mPos;
    q4 sin    = SIN(mAngle);
    q4 cos    = COS(mAngle);
    Mat3p_InitYRotation(&rotation, sin, cos);

    if (mUnk_1ac != 0 || mUnk_1b2 != 0) {
        Mat3p pitch;
        s16 angle   = mUnk_1ac + mUnk_1b2;
        q4 pitchSin = SIN((u16) angle);
        Mat3p_InitXRotation(&pitch, pitchSin, COS((u16) angle));
        Mat3p_Multiply(&pitch, &rotation, &rotation);
        if (mUnk_130 == 3) {
            pos.y -= MUL_Q20(pitchSin, 0x333);
        } else {
            pos.y += MUL_Q20(pitchSin, 0x333);
        }
    }

    s32 alpha = 31;
    if (mUnk_1a4 < 16) {
        alpha = (mUnk_1a4 << 5) / 16;
        func_02019570(mUnk_184->GetLcdcAddress(), 0, alpha);
    }
    mUnk_184->SetRotationTranslation(&rotation, &pos);

    if (mUnk_1a4 < 16) {
        func_02019570(mUnk_184->GetLcdcAddress(), 0, 31);
    } else {
        q20 length = MUL_Q20(mUnk_19c, 0x1000);
        G3d_SetMtxMode_inline(2);
        PushGeometryCommand(0x11, NULL, 0);

        Vec3p trans = mPos;
        trans.x -= (sin * 0x800 + 0x800) >> 12;
        trans.z -= (cos * 0x800 + 0x800) >> 12;
        PushGeometryCommand(0x1c, &trans, 3);
        G3d_MtxMult33_inline(&rotation);
        G3d_Scale_inline(0x1000, 0x1000, length);

        PushCommand(0x2a, 0);
        PushCommand(0x2b, 0);
        PushCommand(0x29, 0x010700c0);
        PushCommand(0x30, 0x4210ffff);
        PushCommand(0x31, 0);
        PushCommand(0x40, 0);
        PushVertex(sTrailVertices[0].x, sTrailVertices[0].y, sTrailVertices[0].z);
        PushVertex(sTrailVertices[1].x, sTrailVertices[1].y, sTrailVertices[1].z);
        PushVertex(sTrailVertices[2].x, sTrailVertices[2].y, sTrailVertices[2].z);
        PushGeometryCommand(0x41, NULL, 0);
        G3d_SetMtxMode_inline(2);
        PushCommand(0x12, 1);
    }

    Vec3p shadowPos;
    Vec3p_Add(&mPos, &mUnk_08c.pos, &shadowPos);
    func_ov005_02102c2c(data_ov000_020e9370, 0, &shadowPos, 0x7b, 0x666, (s16) mAngle, alpha >> 1, 0, 1, 1);
}

static const s32 sUnused[2] = {0, 0x333};
