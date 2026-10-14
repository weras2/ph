#include "Actor/Player/ActorBomb.hpp"
#include "Actor/ActorSpawner.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "DTCM/UnkStruct_027e0f68.hpp"
#include "DTCM/UnkStruct_027e0f6c.hpp"
#include "DTCM/UnkStruct_027e0f78.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Item/ItemManager.hpp"
#include "Map/MapManager.hpp"
#include "Player/PlayerBase.hpp"
#include "Player/PlayerLinkBase.hpp"
#include "Render/ModelRender.hpp"
#include "System/Random.hpp"
#include "System/SysNew.hpp"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

// ActorRef without the resetting constructor
struct ActorBomb_Ref {
    /* 0 */ s32 id;
    /* 4 */ s32 index;
};

struct ActorBomb_AnimName {
    /* 00 */ char mName[0x10];
    /* 10 */ unk32 mUnk_10;
    /* 14 */
};

struct ActorBomb_AnimName2 {
    /* 00 */ unk32 mUnk_00;
    /* 04 */ char mName[0x10];
    /* 14 */
};

// Local tile query state (constructed but unused)
struct ActorBomb_TileQuery {
    /* 00 */ u16 mUnk_00[4];
    /* 08 */ u16 mUnk_08;
    /* 0a */ unk8 mUnk_0a[0x20];
    /* 2a */ u8 mUnk_2a[4];
    /* 2e */ unk8 mUnk_2e[6];
    /* 34 */ u8 mUnk_34[6];
    /* 3a */

    inline ActorBomb_TileQuery() {
        mUnk_00[0] = 0xffff;
        mUnk_00[1] = 0xffff;
        mUnk_00[2] = 0xffff;
        mUnk_00[3] = 0xffff;
        mUnk_08    = 0;
        mUnk_2a[0] = 0;
        mUnk_2a[1] = 0;
        mUnk_2a[2] = 0;
        mUnk_2a[3] = 0;
        mUnk_34[0] = 0;
        mUnk_34[1] = 0;
        mUnk_34[2] = 0;
        mUnk_34[3] = 0;
        mUnk_34[4] = 0;
        mUnk_34[5] = 0;
    }
};

class ActorBomb_MapObject {
public:
    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08();
    /* 0c */ virtual void vfunc_0c();
    /* 10 */ virtual void vfunc_10();
    /* 14 */ virtual void vfunc_14();
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual s32 vfunc_1c();
    /* 20 */ virtual void vfunc_20();
};

static const ActorBomb_AnimName sAnimName   = {"bomb_clanim", 0};
static const ActorBomb_AnimName2 sAnimName2 = {0, "Fbomb_clanim"};
static const Vec3p sSparkOffsets[2]         = {
    {0xcd, 0xd9a, 0},
    {0xcd, 0xc00, 0},
};
static const Vec3p sSparkOffsets2[2] = {
    {0, 0xc00, 0},
    {0, 0xb33, 0},
};
static const ActorTypeId sExplodeActorTypes[] = {ActorTypeId_Blast, ActorTypeId_Arrow, ActorTypeId_Null};
static const ActorTypeId sBounceActorTypes[]  = {(ActorTypeId) 'WBST', (ActorTypeId) 'WBSA', ActorTypeId_Null};

struct ActorBomb_FloatParams {
    /* 0 */ q20 mHeight;
    /* 4 */ q20 mSpeed;
    /* 8 */

    inline ActorBomb_FloatParams(q20 height, q20 speed) :
        mHeight(height),
        mSpeed(speed) {}
};

inline void *operator new(size_t size, void *ptr) {
    return ptr;
}

extern u32 **data_027e0fe0[];
extern u32 data_ov000_020e9370[];
void func_ov000_020b7e6c(s32 *param1);

extern "C" {
extern Mat3p gDefaultMatrix;
void func_ov000_020c7764(s32 param1, Vec3p *param2, s32 param3, s32 param4);
ItemModel *func_ov000_0208ccdc(UnkStruct_027e0f68 *param1, s32 param2);
void *func_ov000_0208cd0c(UnkStruct_027e0f68 *param1, s32 param2, s32 param3, const void *param4);
ModelRender *func_ov014_0212e1f4(void *param1, ItemModel *model, s32 param3, s32 param4);
void func_ov000_020c0c70(UnkStruct_ov000_020c0c08 *param1, void *param2);
void func_ov000_020b7df0(void *param1);
void func_ov000_0207c474(UnkStruct_027e0e58 *param1, ActorBomb_Unk2 *param2, Vec3p *param3);
void func_ov000_0207c444(UnkStruct_027e0e58 *param1, ActorBomb_Unk2 *param2);
bool func_ov000_0209cbd4(UnkStruct_027e0f78 *param1, Vec3p *param2, Vec3p *param3);
void func_ov000_020a61ac(Vec3p *vec, s16 angle);
void func_ov005_02102c2c(u32 *param1, s32 param2, Vec3p *param3, s32 param4, s32 param5, s32 param6, u8 param7, u8 param8,
                         u8 param9, u8 param10);
}

ActorType ActorBomb::gType = ActorType(ActorTypeId_Bomb, (ActorCreateFunc) ActorBomb::Create, NULL);

extern ActorBomb_FloatParams sFloatParams;

ARM ActorBomb *ActorBomb::Create() {
    return new(*data_027e0fe0[0], 4) ActorBomb();
}

ARM bool ActorBomb_Unk1::vfunc_0c(unk16 *param1) {
    u32 info;
    UnkStruct_027e0f6c::func_ov000_02093a1c(&info, data_027e0f6c, *param1);
    if (((info >> 5) & 3) == 2) {
        if ((info & 0x1f) == 8) {
            func_ov000_020c7764(1, (Vec3p *) (param1 + 2), 0, 1);
            data_027e0ffc.func_ov000_020ceacc(0x1ac, (Vec3p *) (param1 + 2), 0);
            mUnk_0c = 2;
            return false;
        }
        return false;
    }
    return UnkStruct_ov000_020beba8::vfunc_0c(param1);
}

ARM bool ActorBomb_Unk1::vfunc_10(s32 *param1) {
    ActorBomb_MapObject *obj = (ActorBomb_MapObject *) param1;
    switch (obj->vfunc_1c()) {
        case 0x10:
        case 0x17:
            obj->vfunc_20();
            if (mUnk_0c == 0) {
                mUnk_0c = 1;
            }
            return true;
        case 0x11:
            return true;
    }
    return UnkStruct_ov000_020beba8::vfunc_10(param1);
}

ARM ActorBomb::ActorBomb() :
    mUnk_1c4(NULL),
    mUnk_1c8(&mUnk_1ec, NULL) {
    mUnk_244               = NULL;
    mUnk_254               = gVec3p_ZERO;
    mUnk_260               = 0x1000;
    mUnk_26a               = false;
    mHitbox.pos.x          = 0;
    mHitbox.pos.y          = 0x59a;
    mHitbox.pos.z          = 0;
    mHitbox.size           = 0x59a;
    mUnk_08c.pos.x         = mHitbox.pos.x;
    mUnk_08c.pos.y         = mHitbox.pos.y;
    mUnk_08c.pos.z         = mHitbox.pos.z;
    mUnk_08c.size          = mHitbox.size;
    mUnk_0a4.mUnk_04.pos.x = 0;
    mUnk_0a4.mUnk_04.pos.y = 0x59a;
    mUnk_0a4.mUnk_04.pos.z = 0;
    mUnk_0a4.mUnk_04.size  = 0x59a + 0x1000;
    mUnk_22c[0].mUnk_4     = 0x22c;
    mUnk_22c[0].mUnk_8     = 2;
    mUnk_22c[1].mUnk_4     = 0x22d;
    mUnk_22c[1].mUnk_8     = 2;
}

ARM ActorBomb_Unk2::~ActorBomb_Unk2() {
    func_ov000_020b7e6c((s32 *) this);
    func_ov000_020b7df0(this);
}

ARM ActorBomb::~ActorBomb() {}

ARM ActorBomb_Unk2::ActorBomb_Unk2() {
    mUnk_0 = 0;
    mUnk_4 = -1;
    mUnk_8 = 0;
}

ARM bool ActorBomb::Init() {
    ItemModel *model;
    void *anim;

    mUnk_130 = 0;
    switch (mUnk_020.mUnk_00[0]) {
        case 0:
            model    = gItemManager->GetItemModel(8);
            anim     = gItemManager->func_ov00_020ad560((const ItemManager_Unk1 *) &sAnimName);
            mUnk_1c4 = ::new(mUnk_15c) ModelRender(model);
            mUnk_244 = sSparkOffsets;
            break;
        case 1:
            model    = func_ov000_0208ccdc(data_027e0f68, 0x38);
            anim     = func_ov000_0208cd0c(data_027e0f68, 0x38, 1, &sAnimName2);
            mUnk_1c4 = mUnk_15c != NULL ? func_ov014_0212e1f4(mUnk_15c, model, 1, 0) : NULL;
            mUnk_244 = sSparkOffsets2;
            break;
        default:
            return false;
    }
    mUnk_1c8.mUnk_08 = model;
    func_ov000_020c0c70(&mUnk_1c8, anim);
    mUnk_125 = 12;
    mUnk_158 = 120;
    mUnk_12c = 4;
    mUnk_1c4->vfunc_24(&mUnk_1c8);
    mUnk_09c.mUnk_2 = 0;
    return true;
}

ARM void ActorBomb::vfunc_14(u32 param1) {
    if (func_ov00_020c313c(param1)) {
        bool active = false;
        if (mUnk_130 != 4 && mUnk_130 != 5) {
            active = true;
        }
        if (active) {
            data_027e0ffc.func_ov000_020cec60(0x1ae, &mPos, (Actor *) mRef.id, 0);
        }

        static ActorBomb_Unk1 sHitHandler;
        mUnk_09c.mUnk_4 = &sHitHandler;

        if (active) {
            if (!mUnk_26a) {
                mUnk_158--;
            }
            if (mUnk_158 <= 0 && mUnk_130 != 2 && mUnk_130 != 6) {
                func_ov014_02122bb8(4);
            } else if (mUnk_158 < 60) {
                mUnk_1c8.mUnk_0c.mUnk_04 = 0x1800 - mUnk_158 * 0x51;
                mUnk_1c8.func_ov000_020c0e04();
            }
            if (mUnk_130 != 6) {
                if (mUnk_158 <= 0) {
                    mUnk_260 = 0x14cd;
                } else {
                    mUnk_260 = CoDivide64By32((mUnk_158 << 12) + 0xa668, (mUnk_158 + 8) << 12);
                }
            }
        }

        switch (mUnk_130) {
            case 0:
            case 2:
            case 3: {
                if (mGrabbed) {
                    func_ov014_02122bb8(1);
                    break;
                }
                Approach_thunk(&mUnk_08c.pos.y, 0x59a, 0x333);
                if (mUnk_130 == 2) {
                    mVel.x    = 0;
                    mVel.z    = 0;
                    u16 angle = mUnk_268;
                    q4 sin    = SIN(angle);
                    q4 cos    = COS(angle);
                    mVel.x += MUL_Q20(sin, 0x4cd);
                    mVel.z += MUL_Q20(cos, 0x4cd);
                    mUnk_268 += 0x2aab;
                    if (mPos.y > 0x7000) {
                        func_ov014_02122bb8(4);
                        break;
                    }
                } else if (mUnk_130 == 3) {
                    Vec3p target;
                    target.x = mUnk_248.x;
                    target.y = mUnk_248.y;
                    target.z = mUnk_248.z;
                    Vec3p floor;
                    bool onFloor;
                    if (gMapManager->func_ov00_02083978(&target, &floor) && floor.y > 0) {
                        onFloor = true;
                    } else {
                        onFloor = false;
                    }
                    if (onFloor) {
                        mVel.x = (mVel.x * 0xe66 + 0x800) >> 12;
                        mVel.y = (mVel.y * 0xd9a + 0x800) >> 12;
                        mVel.z = (mVel.z * 0xe66 + 0x800) >> 12;
                        if (mActiveFrames > 30) {
                            Vec3p pos;
                            pos.x                  = mPos.x;
                            pos.y                  = mPos.y;
                            pos.z                  = mPos.z - 0x1000;
                            MapManager *mapManager = gMapManager;
                            ActorBomb_TileQuery query;
                            TilePos tile             = mapManager->func_ov00_02083a1c(&pos);
                            ActorBomb_MapObject *obj = (ActorBomb_MapObject *) mapManager->MapData_vfunc_78(&tile);
                            if (obj != NULL && (obj->vfunc_1c() == 0x3d || obj->vfunc_1c() == 0x40 ||
                                                obj->vfunc_1c() == 0x44 || obj->vfunc_1c() == 0x5d)) {
                                mVel.y        = 0xcd;
                                mVel.x        = gRandom.Next(0, 0xa5) - 0x52;
                                mVel.z        = gRandom.Next(0, 0xa5) - 0x52;
                                mActiveFrames = 0;
                            } else {
                                mVel.x   = 0;
                                mVel.y   = 0x19a;
                                mVel.z   = -0x19a;
                                mGravity = 0xcc;
                                func_ov014_02122bb8(0);
                            }
                        } else {
                            mActiveFrames++;
                            mGravity =
                                (MUL_Q20(sFloatParams.mHeight - (mPos.y - mUnk_248.y), sFloatParams.mSpeed) * -0xcd + 0x800) >>
                                12;
                            mVel.x += (mUnk_248.x - mPos.x) >> 4;
                            mVel.z += (mUnk_248.z - mPos.z) >> 4;
                        }
                    } else {
                        mGravity = 0xcc;
                        func_ov014_02122bb8(0);
                    }
                } else {
                    Vec3p pos;
                    pos.x = mPos.x;
                    pos.y = mPos.y;
                    pos.z = mPos.z;
                    Vec3p push;
                    if (func_ov000_0209cbd4(data_027e0f78, &pos, &push)) {
                        if (mTouchingFloor) {
                            Vec3p_Scale(&push, 0x19a);
                            push.y = 0;
                            Vec3p_Add(&mVel, &push, &mVel);
                        } else if ((push.x != 0 || push.z != 0) && (mVel.x != 0 || mVel.z != 0)) {
                            s16 pushAngle = FX_Atan2Idx(push.x, push.z);
                            s16 velAngle  = FX_Atan2Idx(mVel.x, mVel.z);
                            Vec3p vel;
                            vel.x = mVel.x;
                            vel.y = mVel.y;
                            vel.z = mVel.z;
                            func_ov000_020a61ac(&vel, (s16) ((pushAngle - velAngle) >> 2));
                            mVel.x = vel.x;
                            mVel.z = vel.z;
                        }
                    }
                }

                ApplyGravity();
                Vec3p_Add(&mPos, &mVel, &mPos);
                Vec3p_Add(&mPos, &mUnk_254, &mPos);
                mUnk_254.x = gVec3p_ZERO.x;
                mUnk_254.y = gVec3p_ZERO.y;
                mUnk_254.z = gVec3p_ZERO.z;

                if (CollidesWithPlayer(0x1a)) {
                    func_ov014_02122bb8(4);
                    break;
                }
                ActorBomb_Ref ref;
                Actor::func_ov00_020c23c4((ActorRef *) &ref, this);
                if (ref.id != -1) {
                    func_ov014_02122bb8(4);
                    break;
                }
                if (func_ov00_020c243c((ActorTypeId *) sExplodeActorTypes, NULL)) {
                    func_ov014_02122bb8(5);
                    break;
                }
                Actor *other;
                if (func_ov00_020c243c((ActorTypeId *) sBounceActorTypes, &other)) {
                    mUnk_264 = other->mRef.id;
                    mGravity = -0xcd;
                    Vec3p diff;
                    Vec3p_Sub(&other->mPos, &mPos, &diff);
                    mUnk_268 = FX_Atan2Idx(diff.x, diff.z);
                    mUnk_268 += -0x2aab;
                    if (mVel.y < 0) {
                        mVel.y = 0;
                    }
                    func_ov014_02122bb8(2);
                    break;
                }

                sHitHandler.mUnk_0c = 0;
                if (func_ov014_02122ed4()) {
                    mPos.x = mUnk_0b8.x;
                    mPos.y = mUnk_0b8.y;
                    mPos.z = mUnk_0b8.z;
                }
                if (sHitHandler.mUnk_0c == 1) {
                    func_ov014_02122bb8(4);
                } else if (mTouchingWall || mUnk_112 || mUnk_113) {
                    Vec3p *normal = (Vec3p *) mUnk_0c4;
                    q20 dot       = Vec3p_Dot(&mVel, normal);
                    if (dot < 0) {
                        Vec3p_Axpy(MUL_Q20(dot, -0x1200), normal, &mVel, &mVel);
                        mVel.x = MUL_Q20(mVel.x, 0xc00);
                        mVel.z = MUL_Q20(mVel.z, 0xc00);
                    }
                } else if (mTouchingFloor) {
                    mVel.x = MUL_Q20(mVel.x, 0x4cd);
                    mVel.y = MUL_Q20(-mVel.y, 0x800);
                    mVel.z = MUL_Q20(mVel.z, 0x4cd);
                } else if (sHitHandler.mUnk_0c == 2 || mPos.y < -0x2666) {
                    mAlive = false;
                }

                bool landed = false;
                Vec3p floor;
                if (mTouchingFloor) {
                    Vec3p pos;
                    pos.x = mPos.x;
                    pos.y = mPos.y;
                    pos.z = mPos.z;
                    if (gMapManager->func_ov00_02083978(&pos, &floor)) {
                        landed = true;
                    }
                }
                if (landed && floor.y > 0) {
                    mGravity      = -0xcd;
                    mActiveFrames = 0;
                    mUnk_248.y    = mPos.y;
                    mUnk_248.x    = (mPos.x & ~0xfff) + 0x800;
                    mUnk_248.z    = (mPos.z & ~0xfff) + 0x800;
                    mVel.z        = 0;
                    mVel.y        = 0;
                    mVel.x        = 0;
                    func_ov014_02122bb8(3);
                }
            } break;
            case 1:
                if (!mGrabbed) {
                    func_ov014_02122bb8(0);
                    break;
                }
                mUnk_08c.pos.y = gPlayerPos.y + 0x5da - mPos.y;
                func_ov00_020c195c();
                break;
            case 4:
            case 5:
                if (--mUnk_158 < -2) {
                    mAlive = false;
                }
                break;
            case 6: {
                Vec3p diff;
                Vec3p_Sub(&mUnk_248, &mPos, &diff);
                q20 length = Vec3p_Length(&diff);
                if (length < 0x666) {
                    q20 scale = (length * 0x666 + 0x800) >> 12;
                    if (mUnk_260 > scale) {
                        mUnk_260 = scale;
                    }
                }
                mGravity = 0;
                Vec3p_Axpy(0x400, &diff, &mVel, &mVel);
                mVel.x = (mVel.x * 0x99a + 0x800) >> 12;
                mVel.y = (mVel.y * 0x99a + 0x800) >> 12;
                mVel.z = (mVel.z * 0x99a + 0x800) >> 12;
                Vec3p_Add(&mPos, &mVel, &mPos);
            } break;
        }

        if (active) {
            if ((mUnk_0a4.mUnk_00 || mUnk_0a4.mUnk_01) && mVisible) {
                Vec3p spark1;
                Vec3p spark2;
                Vec3p_Axpy(mUnk_260, (Vec3p *) &mUnk_244[0], &mPos, &spark1);
                Vec3p_Axpy(mUnk_260, (Vec3p *) &mUnk_244[1], &mPos, &spark2);
                func_ov000_0207c474(data_027e0e58, &mUnk_22c[0], &spark1);
                func_ov000_0207c474(data_027e0e58, &mUnk_22c[1], &spark2);
            } else {
                for (ActorBomb_Unk2 *it = mUnk_22c; it != mUnk_22c + 2; it++) {
                    func_ov000_020b7e6c((s32 *) it);
                }
            }
        }
    }
    mUnk_0a4.func_ov000_0207a1c8(param1, &mPos);
}

ActorBomb_FloatParams sFloatParams(0x2199, 0x79e);

ARM void ActorBomb::vfunc_18(u32 param1) {
    mUnk_26a = true;
    if (mGrabbed) {
        if (!gPlayerLink->func_ov000_020bbe94()) {
            mAlive = false;
            return;
        }
        vfunc_14(param1);
    } else {
        for (ActorBomb_Unk2 *it = mUnk_22c; it != mUnk_22c + 2; it++) {
            func_ov000_020b7e6c((s32 *) it);
        }
    }
    mUnk_0a4.func_ov000_0207a1c8(param1, &mPos);
    mUnk_26a = false;
}

ARM bool ActorBomb::func_ov014_02122bb8(s32 state) {
    mUnk_130 = state;
    if (state != 4 && state != 5) {
        if (state == 6) {
            mActiveFrames = 0;
            mUnk_12c      = 0;
        }
    } else {
        ActorSpawnOptions options;
        options.mUnk_1c.id    = mRef.id;
        options.mUnk_1c.index = mRef.index;
        if (mUnk_130 == 4) {
            options.mUnk_00.mUnk_00[0] = 0;
        } else {
            options.mUnk_00.mUnk_00[0] = 1;
        }
        gActorSpawner->Spawn(ActorTypeId_Blast, &mPos, &options, NULL);
        mUnk_158                    = 0;
        UnkStruct_027e0e58 *effects = data_027e0e58;
        for (u32 i = 0; i < 2; i++) {
            func_ov000_0207c444(effects, &mUnk_22c[i]);
        }
        mVisible = false;
    }
    return true;
}

ARM void ActorBomb::vfunc_54() {
    Vec3p_Add(&mUnk_254, &mUnk_254, &mUnk_254);
}

ARM void ActorBomb::vfunc_20(bool param1) {
    bool visible;
    if (param1) {
        visible = mUnk_0a4.mUnk_01;
    } else {
        visible = mUnk_0a4.mUnk_00;
    }
    if (!visible) {
        return;
    }
    q20 size = mUnk_260;
    if (size == 0x1000) {
        mUnk_1c4->SetTranslation(&mPos);
    } else {
        Vec3p scale;
        scale.x = size;
        scale.y = size;
        scale.z = size;
        mUnk_1c4->SetTransform(&scale, &gDefaultMatrix, &mPos);
    }
    func_ov005_02102c2c(data_ov000_020e9370, 0, &mPos, 0x59a, 0x59a, 0, 31, 0, 1, 1);
}

ARM bool ActorBomb::Drop(Vec3p *vel) {
    if (Vec3p_Length(vel) > 0x29) {
        mPos.x     = gPlayerPos.x;
        mPos.z     = gPlayerPos.z;
        mPrevPos.x = mPos.x;
        mPrevPos.y = mPos.y;
        mPrevPos.z = mPos.z;
    } else {
        mPrevPos.x = gPlayerPos.x;
        mPrevPos.y = mPos.y;
        mPrevPos.z = gPlayerPos.z;
    }
    bool result = Actor::Drop(vel);
    mVel.x      = MUL_Q20(mVel.x, 0xccd);
    mVel.y      = 0xc00 - 0xccd;
    mVel.z      = MUL_Q20(mVel.z, 0xccd);
    return result;
}

ARM void ActorBomb::func_ov014_02122e48(unk32 *param1) {
    Vec3p *pos = (Vec3p *) param1;
    mUnk_248.x = pos->x;
    mUnk_248.y = pos->y;
    mUnk_248.z = pos->z;
    if (mUnk_130 == 6) {
        return;
    }
    func_ov014_02122bb8(6);
}

ARM bool ActorBomb::func_ov014_02122e7c() {
    return !mGrabbed && mUnk_130 == 0;
}

ARM void ActorBomb::func_ov014_02122e98() {
    if (!(mUnk_130 != 4 && mUnk_130 != 5)) {
        return;
    }
    func_ov014_02122bb8(4);
}

ARM bool ActorBomb::func_ov014_02122eb8() {
    return !mGrabbed && mUnk_130 == 0;
}

ARM bool ActorBomb::func_ov014_02122ed4() {
    q20 step = mUnk_08c.size - 0x40;
    bool hit = false;
    Vec3p pos;
    pos.x = mPos.x;
    pos.y = mPos.y;
    pos.z = mPos.z;
    Vec3p prev;
    prev.x = mPrevPos.x;
    prev.y = mPrevPos.y;
    prev.z = mPrevPos.z;
    Vec3p diff;
    Vec3p_Sub(&pos, &prev, &diff);
    q20 length  = Vec3p_Length(&diff);
    Vec3p start = prev;
    Vec3p from  = start;
    Vec3p to    = start;
    Vec3p dir   = diff;
    if (Vec3p_TryNormalize(&dir) && length != 0) {
        do {
            if (length > step) {
                Vec3p_Axpy(step, &dir, &to, &to);
                length -= step;
            } else {
                Vec3p_Axpy(length, &dir, &to, &to);
                length = 0;
            }
            mPos.x     = to.x;
            mPos.y     = to.y;
            mPos.z     = to.z;
            mPrevPos.x = from.x;
            mPrevPos.y = from.y;
            mPrevPos.z = from.z;
            hit        = func_01fffd04(0);
            if (hit || mTouchingFloor) {
                break;
            }
            from.x = to.x;
            from.y = to.y;
            from.z = to.z;
        } while (length != 0);
    }
    mPrevPos.x = mPos.x;
    mPrevPos.y = mPos.y;
    mPrevPos.z = mPos.z;
    return hit;
}

ARM ActorBomb_Unk1::~ActorBomb_Unk1() {}
