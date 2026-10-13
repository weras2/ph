#include "Player/EquipBoomerang.hpp"
#include "Actor/ActorManager.hpp"
#include "Actor/ActorSpawner.hpp"
#include "Actor/FilterActorBase.hpp"
#include "DTCM/UnkStruct_027e0de4.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Map/MapManager.hpp"
#include "Physics/Cylinder.hpp"
#include "Player/LinkStateItem.hpp"
#include "Player/PlayerBase.hpp"
#include "Player/PlayerControl.hpp"
#include "Unknown/UnkStruct_020ee6f8.hpp"
#include "Unknown/UnkStruct_ov000_020beba8.hpp"
#include "nds/g3d/sbc.h"

// Tiles hit by the boomerang
class EquipBoomerang_TileList : public SysObject {
public:
    /* 00 (vtable) */
    /* 04 */ u16 mCount;
    /* 06 */ u16 mIndex;
    /* 08 */ TilePos mTiles[16];
    /* 28 */

    /* 00 */ virtual ~EquipBoomerang_TileList() {
        ((UnkStruct_ov000_020beba8 *) this)->UnkStruct_ov000_020beba8::~UnkStruct_ov000_020beba8();
    }
    /* 08 */ virtual bool vfunc_08(UnkStruct_ov000_020beba8_08 *param1);
    /* 0c */ virtual bool vfunc_0c(unk16 *param1);
    /* 10 */ virtual bool vfunc_10(s32 *param1);
    /* 14 */ virtual bool vfunc_14(u16 *param1);
    /* 18 */

    inline EquipBoomerang_TileList() {
        mIndex = 0;
        mCount = 0;
    }

    bool func_ov053_02198de4(TilePos tile);
};

// Actors hit by the boomerang
class EquipBoomerang_ActorList {
public:
    /* 00 (vtable) */
    /* 04 */ Cylinder *mHitbox;
    /* 08 */ u16 mCount;
    /* 0a */ u16 mIndex;
    /* 0c */ ActorRef mActors[16];
    /* 8c */

    /* 00 */ virtual bool Filter(Actor *actor);
    /* 04 */

    inline EquipBoomerang_ActorList() {
        this->Reset();
    }

    void Reset();
    bool func_ov053_02198f88(ActorRef *ref);
    void func_ov053_02198fd4(ActorRef *ref);
};

struct EquipBoomerang_MapObject {
    /* 00 (vtable) */
    /* 04 */ u32 mFlags;
    /* 08 */ unk8 mUnk_08[0xc];
    /* 14 */ TilePos mTile;
};

struct EquipBoomerang_Throw {
    /* 0 */ s16 mAngle;
    /* 4 */ unk32 mUnk_4;
};

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

Mat4x3p EquipBoomerang::sMtx;
EquipBoomerang_Point EquipBoomerang::sPoints[64];

static const Vec3p data_ov053_02199fb8 = {-0x199, 0x800, -0x7a};

extern "C" {
void func_ov000_020b17ec(Mat4x3p *param1, Vec3p param2, s32 param3, s32 param4, s32 param5);
void func_ov000_020b41c4(ModelRender *param1);
void func_ov000_020bd958(unk32 *param1, unk32 param2, unk32 param3, unk32 param4, unk32 param5, unk32 param6, unk32 param7);
void func_ov000_020bdeb4(unk32 *param1, Vec3p *param2, s32 *param3, s32 *param4);
void func_ov000_020d61b0(UnkStruct_020ee6f8 *param1, s32 param2, s32 param3, unk32 param4);
void func_ov014_02123134(Sphere *param1);
bool func_ov000_02087f08(UnkStruct_027e0f64_04 *param1, unk32 param2);
void func_ov000_0208967c(UnkStruct_027e0f64_04 *param1, unk32 param2, Vec3p *param3, const Vec3p *param4, unk32 param5,
                         unk32 param6);
void func_0202b4e4(Vec3p *param1, Vec3p *param2, q20 param3, s32 param4, s32 param5);
}

EquipBoomerang *GetEquipBoomerang();

ARM bool EquipBoomerang_TileList::vfunc_08(UnkStruct_ov000_020beba8_08 *param1) {
    return false;
}

ARM bool EquipBoomerang_TileList::vfunc_0c(unk16 *param1) {
    return false;
}

ARM bool EquipBoomerang_TileList::vfunc_14(u16 *param1) {
    return false;
}

ARM bool EquipBoomerang_TileList::vfunc_10(s32 *param1) {
    EquipBoomerang_MapObject *obj = (EquipBoomerang_MapObject *) param1;
    if (!(obj->mFlags & 0x400)) {
        return false;
    }
    if (mCount >= 16) {
        return false;
    }
    TilePos tile = obj->mTile;
    for (s32 i = 0; i < mCount; i++) {
        if (mTiles[i] == tile) {
            return false;
        }
    }
    mTiles[mCount] = tile;
    mCount++;
    return false;
}

ARM bool EquipBoomerang_TileList::func_ov053_02198de4(TilePos tile) {
    if (mIndex < mCount && mTiles[mIndex] == tile) {
        mIndex++;
        return true;
    }
    return false;
}

ARM bool EquipBoomerang_ActorList::Filter(Actor *actor) {
    if (mCount >= 16) {
        return false;
    }
    for (s32 i = 0; i < mCount; i++) {
        if (actor->mRef.id == mActors[i].id) {
            return false;
        }
    }
    Cylinder hitbox;
    actor->GetHitbox(&hitbox);
    if (hitbox.Overlaps(mHitbox)) {
        if (!actor->vfunc_60()) {
            return false;
        }
        mActors[mCount] = actor->mRef;
        mCount++;
        return true;
    }
    return false;
}

ARM void EquipBoomerang_ActorList::Reset() {
    for (s32 i = 0; i < mCount; i++) {
        this->func_ov053_02198fd4(&mActors[i]);
    }
    mCount  = 0;
    mIndex  = 0;
    mHitbox = NULL;
}

ARM bool EquipBoomerang_ActorList::func_ov053_02198f88(ActorRef *ref) {
    if (mIndex < mCount && mActors[mIndex].id == ref->id) {
        this->func_ov053_02198fd4(ref);
        mIndex++;
        return true;
    }
    return false;
}

ARM void EquipBoomerang_ActorList::func_ov053_02198fd4(ActorRef *ref) {
    Actor *actor = gActorManager->GetActor(ref);
    if (actor == NULL) {
        return;
    }
    if (actor->mType != 'FBS1') {
        return;
    }
    actor->vfunc_64();
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

static EquipBoomerang_TileList sTiles;
static EquipBoomerang_ActorList sActors;

ARM void EquipBoomerang::func_ov053_02199038() {
    this->func_ov014_0213d1b0();
    sTiles.mIndex = 0;
    sTiles.mCount = 0;
    sActors.Reset();
}

ARM void EquipBoomerang::vfunc_18() {
    func_ov000_020b17ec(&sMtx, data_ov053_02199fb8, -0x39f5, -0x38e, -0x2aab);
    mUnk_28 = sPoints;
    mUnk_24 = 64;
    this->func_ov053_02199038();
}

ARM void EquipBoomerang::vfunc_1c() {
    if (this->GetActor() == NULL) {
        this->func_ov053_02199038();
    }
}

ARM void EquipBoomerang::func_ov053_021990f0(TilePos param1) {
    sTiles.func_ov053_02198de4(param1);
}

ARM bool EquipBoomerang::func_ov053_02199128(s32 *param1) {
    return sActors.func_ov053_02198f88((ActorRef *) param1);
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
    for (s32 i = sTiles.mIndex; i < sTiles.mCount; i++) {
        TilePos tile                  = sTiles.mTiles[i];
        UnkStruct_ov000_020beba8 *obj = (UnkStruct_ov000_020beba8 *) gMapManager->MapData_vfunc_78(&tile);
        if (obj != NULL) {
            Vec3p pos;
            ((void (*)(UnkStruct_ov000_020beba8 *, Vec3p *, s32))(*(void ***) obj)[25])(obj, &pos, 2);
            this->func_ov000_020be9e4(pos, mUnk_2c);
        }
    }
    for (s32 i = sActors.mIndex; i < sActors.mCount; i++) {
        ActorRef ref = sActors.mActors[i];
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
        G3d_MtxMult43_inline(&sMtx);
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

            s32 prevHits = sTiles.mCount + sActors.mCount;
            gMapManager->func_01ffbe78(&hit, &cur, &prev, &sphere, 1, 4, (unk32) &sTiles, 0);
            hitSphere = sphere;
            Vec3p_Add(&cur, &hitSphere.pos, &hitSphere.pos);
            sActors.mHitbox = (Cylinder *) &hitSphere;
            gActorManager->FilterActors((FilterActorBase *) &sActors, NULL);
            if (sTiles.mCount + sActors.mCount > prevHits) {
                data_027e0ffc.func_ov000_020ceacc(0x1a0, &cur, 0);
            }
        }
    }
    return true;
}

static EquipBoomerang_Throw data_ov053_0219a0ec     = {0x2000, 0x7000};
static LinkStateBase_UnkStruct1 data_ov053_0219a0f4 = {0x30, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(30.0)}};
static LinkStateBase_UnkStruct1 data_ov053_0219a104 = {0x31, {FLOAT_TO_Q20(1.5), 0, FLOAT_TO_Q20(12.0)}};

ARM void LinkStateItem::func_ov053_02199730() {
    this->func_ov00_020a89bc(&data_ov053_0219a0f4, 1);
    mUnk_44 = gVec3p_ZERO;
    gPlayerControl->ResetAim();
}

ARM void LinkStateItem::func_ov053_0219977c() {
    EquipBoomerang *boomerang = GetEquipBoomerang();
    if (data_ov053_0219a0f4.mUnk_00 == this->Get_PlayerControlData_Unk100()) {
        Vec3p aim;
        if (gPlayerControl->func_ov00_020b0f88(&aim, 0x800, &mUnk_44)) {
            if (boomerang->mUnk_1c == 0) {
                mUnk_38 = aim;
            }
            boomerang->func_ov053_021994cc(&aim);
            this->func_ov00_020a81fc(&aim, 0x800);
        } else if (gPlayerControl->IsUntouchedNow() && boomerang->mUnk_1c > 0) {
            this->func_ov00_020a89bc(&data_ov053_0219a104, 1);
            this->LookAt(&mUnk_38);
            return;
        }
        if (!func_ov000_02087f08(data_027e0f64->mUnk_4, 2)) {
            return;
        }
        Vec3p pos;
        Vec3p_Add(&mUnk_44, &gPlayerPos, &pos);
        func_ov000_0208967c(data_027e0f64->mUnk_4, 2, &pos, &gVec3p_ZERO, 0, 0);
        return;
    }

    if (data_ov053_0219a104.mUnk_00 != this->Get_PlayerControlData_Unk100()) {
        return;
    }
    if (this->func_ov00_020a8b04(data_ov053_0219a0ec.mUnk_4, false)) {
        boomerang->mUnk_04 = *(s16 *) this->GetPlayerAngle();
        boomerang->func_ov053_02199410(data_ov053_0219a0ec.mAngle);
        return;
    }
    if (this->func_ov00_020a8b3c(0)) {
        gPlayerControl->UpdateUsingEquipItem();
        this->func_ov005_02105d94();
        return;
    }
    if (!func_ov000_02087f08(data_027e0f64->mUnk_4, 2)) {
        return;
    }
    Vec3p dir;
    boomerang->func_ov014_0213d0bc(&dir);
    func_0202b4e4(&dir, &boomerang->func_ov053_0219902c(0)->mPos, 0x800, 0, 0x7fffffff);
    Vec3p_Sub(&dir, &gPlayerPos, &dir);
    func_0202b4e4(&mUnk_44, &dir, 0x800, 0, 0x7fffffff);
    Vec3p pos;
    Vec3p_Add(&mUnk_44, &gPlayerPos, &pos);
    func_ov000_0208967c(data_027e0f64->mUnk_4, 2, &pos, &gVec3p_ZERO, 0, 0);
}

ARM EquipBoomerang *GetEquipBoomerang() {
    return (EquipBoomerang *) ItemManager::GetEquipItemUnchecked(ItemFlag_Boomerang);
}
