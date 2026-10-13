#include "Player/EquipBoomerang.hpp"
#include "Actor/ActorManager.hpp"
#include "Actor/ActorSpawner.hpp"
#include "DTCM/UnkStruct_027e0de4.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Map/MapManager.hpp"
#include "Player/PlayerControl.hpp"
#include "Unknown/UnkStruct_020ee6f8.hpp"
#include "nds/g3d/sbc.h"

// Tiles hit by the boomerang
struct UnkStruct_ov053_0219a5bc {
    /* 00 */ unk32 mUnk_00;
    /* 04 */ u16 mCount;
    /* 06 */ u16 mIndex;
    /* 08 */ TilePos mTiles[16];
    /* 28 */
};

// Actors hit by the boomerang
struct UnkStruct_ov053_0219a5e4 {
    /* 00 */ unk32 mUnk_00;
    /* 04 */ Sphere *mSphere;
    /* 08 */ u16 mCount;
    /* 0a */ u16 mIndex;
    /* 0c */ ActorRef mActors[16];
    /* 8c */
};

struct UnkStruct_ov053_0219a580 {
    /* 00 */ unk8 mUnk_00[0x3c];
    /* 3c */ UnkStruct_ov053_0219a5bc mTiles;
    /* 64 */ UnkStruct_ov053_0219a5e4 mActors;
    /* f0 */
};

extern Mat4x3p data_ov053_0219a180;
extern EquipBoomerang_Point data_ov053_0219a1b0[];
extern UnkStruct_ov053_0219a580 data_ov053_0219a580;
extern UnkStruct_ov053_0219a5bc data_ov053_0219a5bc;
extern UnkStruct_ov053_0219a5e4 data_ov053_0219a5e4;
extern const Vec3p data_ov053_02199fb8;

extern "C" {
void func_ov000_020b17ec(Mat4x3p *param1, Vec3p param2, s32 param3, s32 param4, s32 param5);
void func_ov000_020b41c4(ModelRender *param1);
void func_ov053_02198f38(UnkStruct_ov053_0219a5e4 *param1);
bool func_ov053_02198de4(UnkStruct_ov053_0219a5bc *param1, TilePos param2);
bool func_ov053_02198f88(UnkStruct_ov053_0219a5e4 *param1, s32 *param2);
void func_ov000_020bd958(unk32 *param1, unk32 param2, unk32 param3, unk32 param4, unk32 param5, unk32 param6, unk32 param7);
void func_ov000_020bdeb4(unk32 *param1, Vec3p *param2, s32 *param3, s32 *param4);
void func_ov000_020d61b0(UnkStruct_020ee6f8 *param1, s32 param2, s32 param3, unk32 param4);
void func_ov014_02123134(Sphere *param1);
}

ARM void EquipBoomerang::func_ov053_02199014(void *param1) {
    ((EquipBoomerang *) param1)->func_ov053_02199168();
}

ARM void EquipBoomerang::func_ov053_02199020(void *param1) {
    ((EquipBoomerang *) param1)->func_ov053_021991ec();
}

ARM EquipBoomerang_Point *EquipBoomerang::func_ov053_0219902c(s32 param1) {
    return &mUnk_28[param1];
}

ARM void EquipBoomerang::func_ov053_02199038() {
    this->func_ov014_0213d1b0();
    data_ov053_0219a580.mTiles.mIndex = 0;
    data_ov053_0219a580.mTiles.mCount = 0;
    func_ov053_02198f38(&data_ov053_0219a5e4);
}

ARM void EquipBoomerang::vfunc_18() {
    func_ov000_020b17ec(&data_ov053_0219a180, data_ov053_02199fb8, -0x39f5, -0x38e, -0x2aab);
    mUnk_28 = data_ov053_0219a1b0;
    mUnk_24 = 64;
    this->func_ov053_02199038();
}

ARM void EquipBoomerang::vfunc_1c() {
    if (this->GetActor() == NULL) {
        this->func_ov053_02199038();
    }
}

ARM void EquipBoomerang::func_ov053_021990f0(TilePos param1) {
    func_ov053_02198de4(&data_ov053_0219a5bc, param1);
}

ARM bool EquipBoomerang::func_ov053_02199128(s32 *param1) {
    return func_ov053_02198f88(&data_ov053_0219a5e4, param1);
}

ARM void EquipBoomerang::vfunc_30() {
    if (this->GetActor() == NULL) {
        this->func_ov014_0213d098();
    }
    mUnk_2c++;
}

ARM void EquipBoomerang::func_ov053_02199168() {
    if (this->IsInUse()) {
        func_ov000_020bd958(&mUnk_20, 0, mUnk_20, 0x33ff, 32, 0x3800, 0);
    } else {
        func_ov000_020bd958(&mUnk_20, 0, mUnk_20, 0x7a29, 20, 0x2800, 0);
    }
}

ARM void EquipBoomerang::func_ov053_021991ec() {
    for (s32 i = data_ov053_0219a580.mTiles.mIndex; i < data_ov053_0219a580.mTiles.mCount; i++) {
        TilePos tile                  = data_ov053_0219a5bc.mTiles[i];
        UnkStruct_ov000_020beba8 *obj = (UnkStruct_ov000_020beba8 *) gMapManager->MapData_vfunc_78(&tile);
        if (obj != NULL) {
            Vec3p pos;
            ((void (*)(UnkStruct_ov000_020beba8 *, Vec3p *, s32))(*(void ***) obj)[25])(obj, &pos, 2);
            this->func_ov000_020be9e4(pos, mUnk_2c);
        }
    }
    for (s32 i = data_ov053_0219a580.mActors.mIndex; i < data_ov053_0219a580.mActors.mCount; i++) {
        ActorRef ref = data_ov053_0219a5e4.mActors[i];
        Actor *actor = gActorManager->GetActor(&ref);
        if (actor != NULL) {
            Cylinder hitbox;
            actor->GetHitbox(&hitbox);
            this->func_ov000_020be9e4(hitbox.pos, mUnk_2c);
        }
    }
}

ARM void EquipBoomerang::vfunc_38(unk32 param1) {
    if (this->IsInUse()) {
        G3d_RestoreMtx_inline(29);
        G3d_MtxMult43_inline(&data_ov053_0219a180);
        func_ov000_020b41c4(mUnk_0c);
    }
    if (param1 != 0) {
        return;
    }
    if (!gPlayerControl->mUnk_7d) {
        return;
    }
    if (!this->IsInUse() && mRef.id == -1) {
        return;
    }
    data_027e0de4.func_ov000_0207bb1c(2, EquipBoomerang::func_ov053_02199014, this);
    data_027e0de4.func_ov000_0207bb1c(5, EquipBoomerang::func_ov053_02199020, this);
}

ARM bool EquipBoomerang::IsUsable(unk32 param1) const {
    if (param1 != 0 && mRef.id != -1) {
        return false;
    }
    return EquipItem::IsUsable(1);
}

ARM void EquipBoomerang::func_ov053_02199410(s32 param1) {
    Vec3p pos = *this->GetPlayerPos();
    pos.y += FLOAT_TO_Q20(0.5);
    ActorSpawnOptions options;
    options.mUnk_1c.id         = 1;
    options.mAngle             = mUnk_04;
    options.mUnk_00.mUnk_00[0] = (param1 >> 7) & 0xff;
    gActorSpawner->Spawn(ActorTypeId_BMRN, &pos, &options, &mRef);
    if (mRef.id == -1) {
        return;
    }
    this->UpdateInUse(0);
}

ARM bool EquipBoomerang::func_ov053_021994cc(Vec3p *param1) {
    Vec3p cur;
    Vec3p prev;
    Sphere hitSphere;
    Vec3p point;
    s32 a;
    s32 b;

    mUnk_18 = mUnk_1c;
    if (mUnk_18 >= 64) {
        return false;
    }
    if (mUnk_18 <= 0 || Vec3p_Distance(param1, &this->func_ov053_0219902c(mUnk_18 - 1)->mPos) > FLOAT_TO_Q20(0.5)) {
        point.x = param1->x;
        point.y = param1->y;
        point.z = param1->z;
        func_ov000_020bdeb4(&mUnk_20, &point, &a, &b);
        mUnk_1c = mUnk_18 + 1;
        func_ov000_020d61b0(&data_ov000_020ee6f8, a, b, 0x19f);
        if (mUnk_18 > 0) {
            UnkStruct hit;
            Sphere sphere;
            func_ov014_02123134(&sphere);
            Vec3p *p = &this->func_ov053_0219902c(mUnk_18)->mPos;
            cur.x    = p->x;
            cur.y    = p->y;
            cur.z    = p->z;
            p        = &this->func_ov053_0219902c(mUnk_18 - 1)->mPos;
            prev.x   = p->x;
            prev.y   = p->y;
            prev.z   = p->z;

            s32 prevHits = data_ov053_0219a580.mTiles.mCount + data_ov053_0219a580.mActors.mCount;
            gMapManager->func_01ffbe78(&hit, &cur, &prev, &sphere, 1, 4, (unk32) &data_ov053_0219a5bc, 0);
            hitSphere = sphere;
            Vec3p_Add(&cur, &hitSphere.pos, &hitSphere.pos);
            data_ov053_0219a5e4.mSphere = &hitSphere;
            gActorManager->FilterActors((FilterActorBase *) &data_ov053_0219a5e4, NULL);
            if (data_ov053_0219a580.mTiles.mCount + data_ov053_0219a580.mActors.mCount > prevHits) {
                data_027e0ffc.func_ov000_020ceacc(0x1a0, &cur, 0);
            }
        }
    }
    return true;
}
