#include "Actor/ActorManager.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "DTCM/UnkStruct_027e0fd4.hpp"
#include "Item/ItemManager.hpp"
#include "Map/MapManager.hpp"
#include "Player/EquipRope.hpp"
#include "Player/PlayerLinkBase.hpp"
#include "System/SysNew.hpp"
#include "nds/g3d/sbc.h"

static char *gShipParts[8] = {"anc", "bow", "hul", "can", "dco", "pdl", "fnl", "brg"};

class EquipRope_MapSubObject {
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
    /* 40 */ virtual s32 vfunc_40();
};

// Map object hooked by the grappling hook (e.g. a peg)
class EquipRope_MapObject {
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
    /* 24 */ virtual void vfunc_24();
    /* 28 */ virtual void vfunc_28();
    /* 2c */ virtual void vfunc_2c();
    /* 30 */ virtual void vfunc_30();
    /* 34 */ virtual s32 vfunc_34(s32 index, Vec3p *pos);
    /* 38 */ virtual void vfunc_38();
    /* 3c */ virtual void vfunc_3c();
    /* 40 */ virtual void vfunc_40();
    /* 44 */ virtual void vfunc_44();
    /* 48 */ virtual void vfunc_48();
    /* 4c */ virtual void vfunc_4c();
    /* 50 */ virtual void vfunc_50();
    /* 54 */ virtual EquipRope_MapSubObject *vfunc_54();
    /* 58 */ virtual void vfunc_58();
    /* 5c */ virtual void vfunc_5c();
    /* 60 */ virtual void vfunc_60();
    /* 64 */ virtual void vfunc_64();
    /* 68 */ virtual void vfunc_68();
    /* 6c */ virtual void vfunc_6c();
    /* 70 */ virtual void vfunc_70();
    /* 74 */ virtual void vfunc_74();
    /* 78 */ virtual void vfunc_78();
    /* 7c */ virtual void vfunc_7c();
    /* 80 */ virtual void vfunc_80();
    /* 84 */ virtual void vfunc_84();
    /* 88 */ virtual void vfunc_88();
    /* 8c */ virtual void vfunc_8c(Vec3p *pos);

    /* 04 */ unk8 mUnk_04[0x8];
    /* 0c */ s16 mUnk_0c;
};

extern unk32 *data_027e0d44;

extern "C" {
bool func_01ffe468(UnkStruct_027e0f64_04 *param1, Vec3p *param2, s32 *param3, s32 *param4, bool param5);
void func_020104b8(s32 param1, Vec3p *param2, Vec3p *param3);
void func_0202d95c(Vec3p *param1, q20 param2);
bool func_ov014_0214be64(EquipRope_MapObject *param1);
void func_ov014_0214bd08(EquipRope_MapObject *param1);
bool func_ov014_0214bd7c(EquipRope_MapObject *param1);
void func_ov014_0214bc98(EquipRope_MapObject *param1);
Vec3p *func_02018450();
}

ARM void func_ov014_0213d230(s32 param1, s32 param2) {
    EquipRope *rope = (EquipRope *) param2;
    func_020104b8(param1, &rope->mUnk_18[0].vec, &rope->mUnk_18[1].vec);
}

ARM bool func_ov013_0213d248(s32 param1) {
    return param1 == 0x47 || param1 == 0x83;
}

THUMB EquipRope::EquipRope() :
    mUnk_0a(-1),
    mUnk_0c(0),
    mUnk_68(false),
    mUnk_69(false),
    mUnk_6a(false),
    mUnk_6c(0),
    mUnk_70(-1) {
    void *model = SysObject::operator new(0xc, data_027e0ce0[1], 4);
    if (model != NULL) {
        model = func_ov000_020bd618(model, NULL, 0, 0);
    }
    mUnk_84 = (ModelRender *) model;
}

THUMB EquipRope::~EquipRope() {
    if (mUnk_84 != NULL) {
        delete mUnk_84;
    }
}

THUMB void EquipRope::vfunc_10() {
    if (gPlayerLink != NULL) {
        mUnk_84->Init_RenderObject(gItemManager->GetItemModel(14));
    }
}

ARM ItemFlag EquipRope::GetId() const {
    return ItemFlag_GrapplingHook;
}

ARM bool EquipRope::func_ov014_0213d3d4(Vec3p *vec) {
    if (mUnk_18[0].mState == 0) {
        return false;
    }
    vec->x = mUnk_18[0].vec.x;
    vec->y = mUnk_18[0].vec.y;
    vec->z = mUnk_18[0].vec.z;
    return true;
}

ARM void EquipRope::func_ov014_0213d404(unk32 *param1) {
    Vec3p *vec = (Vec3p *) param1;
    vec->x     = mUnk_78.x;
    vec->y     = mUnk_78.y;
    vec->z     = mUnk_78.z;
}

ARM ActorRope *EquipRope::GetRopeActor() {
    return (ActorRope *) gActorManager->GetActor(&mRopeRef);
}

ARM s32 EquipRope::func_ov14_0213d440(s32 actorId) {
    if (mUnk_0a >= 0) {
        for (s32 i = 0; i < 2; i++) {
            if (mUnk_18[i].mState == 3 && actorId == mUnk_18[i].mRef.id) {
                return i;
            }
        }
    }
    return -1;
}

ARM s32 EquipRope::func_ov14_0213d480(s32 actorId) {
    if (mUnk_68) {
        for (s32 i = 0; i < 2; i++) {
            if (actorId == mUnk_18[i].mRef.id && (mUnk_18[i].mState == 5 || mUnk_18[i].mState == 3)) {
                return i;
            }
        }
    }
    return -1;
}

ARM bool EquipRope::func_ov014_0213d4c8() {
    return gPlayerLink->GetStateId() == 1;
}

ARM bool EquipRope::func_ov014_0213d4ec(unk32 *param1, s32 param2) {
    EquipRope_Unk_18 *point = (EquipRope_Unk_18 *) param1;
    switch (mUnk_0a) {
        case 0:
            func_ov014_0213d404((unk32 *) point);
            point->mState  = 1;
            point->mUnk_19 = 0;
            return true;
        case 1:
            *point = mUnk_18[1 - param2];
            return true;
        default:
            point->mState = 0;
            return false;
    }
}

ARM s32 EquipRope::func_ov014_0213d594(s32 param1) {
    switch (mUnk_0a) {
        case 0:
            return 1;
        case 1:
            return mUnk_18[1 - param1].mState;
        default:
            return 0;
    }
}

ARM bool EquipRope::func_ov014_0213d5d0(unk32 *param1, s32 param2) {
    EquipRope_Unk_18 point;
    if (!func_ov014_0213d4ec((unk32 *) &point, param2)) {
        return false;
    }
    Vec3p *vec = (Vec3p *) param1;
    vec->x     = point.vec.x;
    vec->y     = point.vec.y;
    vec->z     = point.vec.z;
    return true;
}

ARM s16 EquipRope::func_ov014_0213d63c(s32 param1) {
    Vec3p *from = &mUnk_18[param1].vec;
    Vec3p *to   = &mUnk_18[1 - param1].vec;
    return (s16) FX_Atan2Idx(to->x - from->x, to->z - from->z);
}

ARM bool EquipRope::func_ov014_0213d684() {
    if (mUnk_0a == 0 && mUnk_18[0].mState == 2) {
        EquipRope_MapObject *obj = (EquipRope_MapObject *) gMapManager->MapData_vfunc_78(&mUnk_18[0].mTile);
        if (obj == NULL || func_ov013_0213d248(obj->vfunc_1c())) {
            return true;
        }
    }
    return false;
}

ARM bool EquipRope::func_ov014_0213d6e0() {
    if (mUnk_0a != 0) {
        return false;
    }
    if (func_ov014_0213d684()) {
        return false;
    }
    return mUnk_18[0].mUnk_19 >= 1;
}

ARM bool EquipRope::func_ov014_0213d71c(s32 param1, ActorRef *param2) {
    Actor *actor               = gActorManager->GetActor(param2);
    mUnk_18[param1].mState     = 3;
    mUnk_18[param1].mRef.id    = param2->id;
    mUnk_18[param1].mRef.index = param2->index;
    mUnk_18[param1].func_ov057_02198e80();
    mUnk_18[param1].func_ov057_02198fc0(actor->mType);
    return true;
}

ARM bool EquipRope::func_ov014_0213d788(s32 param1) {
    EquipRope_Unk_18 other;
    if (func_ov014_0213d4ec((unk32 *) &other, param1)) {
        s8 a = mUnk_18[param1].mUnk_19;
        s8 b = other.mUnk_19;
        if (a == 0 || (a == 1 && b != 0)) {
            return true;
        }
        return false;
    }
    return false;
}

ARM bool EquipRope::func_ov14_0213d81c(s32 index, Vec3p *vec) {
    EquipRope_Unk_18 other;
    if (func_ov014_0213d4ec((unk32 *) &other, index)) {
        EquipRope_Unk_18 *point = &mUnk_18[index];
        if (mUnk_74 > 0) {
            s8 a = point->mUnk_19;
            s8 b = other.mUnk_19;
            if (a == 0 || (a == 1 && b != 0)) {
                Vec3p_Sub(&other.vec, &point->vec, vec);
                func_0202d95c(vec, MUL_Q20(point->mUnk_19 == 0 ? 0xe66 : 0x800, mUnk_74));
                return true;
            }
        }
        vec->x = gVec3p_ZERO.x;
        vec->y = gVec3p_ZERO.y;
        vec->z = gVec3p_ZERO.z;
    }
    return false;
}

ARM void EquipRope::func_ov14_0213d91c(s32 index) {
    switch (mUnk_18[index].mState) {
        case 2: {
            EquipRope_MapObject *obj = (EquipRope_MapObject *) gMapManager->MapData_vfunc_78(&mUnk_18[index].mTile);
            if (obj != NULL && func_ov013_0213d248(obj->vfunc_1c()) && !func_ov014_0214be64(obj)) {
                func_ov014_0214bd08(obj);
            }
        } break;
        case 3:
            break;
    }
    mUnk_18[index].mState  = 0;
    mUnk_18[index].mUnk_18 = 0;
    mUnk_18[index].mUnk_19 = 0;
}

ARM bool EquipRope::func_ov014_0213d9ac() {
    mUnk_0a = func_ov014_0213dda0();
    for (s32 i = 0; i <= mUnk_0a; i++) {
        switch (mUnk_18[i].mState) {
            case 4: {
                EquipRope_MapObject *obj = (EquipRope_MapObject *) gMapManager->MapData_vfunc_78(&mUnk_18[i].mTile);
                if (obj != NULL) {
                    Vec3p pos;
                    func_ov014_0213d5d0((unk32 *) &pos, i);
                    mUnk_18[i].mState = 2;
                    Vec3p target;
                    target.x      = pos.x;
                    target.y      = pos.y;
                    target.z      = pos.z;
                    bool attached = obj->vfunc_34(i, &target) >= 0;
                    if (!attached) {
                        mUnk_18[i].mState = 0;
                        return false;
                    }
                }
            } break;
            case 5:
                if (gActorManager->GetActor(&mUnk_18[i].mRef) != NULL) {
                    mUnk_18[i].mState = 3;
                } else {
                    mUnk_18[i].mState = 0;
                }
                break;
        }
    }
    mUnk_74 = 0;
    return true;
}

ARM bool EquipRope::func_ov14_0213dadc(s32 index, Cylinder *cylinder) {
    ActorRope *rope = GetRopeActor();
    if (rope == NULL) {
        return false;
    }
    Vec3p pos;
    pos                  = cylinder->pos;
    mUnk_18[index].vec.x = pos.x;
    mUnk_18[index].vec.y = pos.y;
    mUnk_18[index].vec.z = pos.z;
    rope->func_ov014_02123c54(index);
    return true;
}

THUMB void EquipRope::func_ov014_0213db34() {
    mRopeRef.Reset();
    mUnk_70 = -1;
    mUnk_68 = false;
    mUnk_0a = -1;
    for (s32 i = 0; i < 2; i++) {
        func_ov14_0213d91c(i);
    }
}

ARM void EquipRope::func_ov014_0213db60() {
    ActorRope *rope = GetRopeActor();
    if (rope != NULL) {
        rope->Kill();
    } else {
        for (s32 i = 0; i < 2; i++) {
            func_ov14_0213d91c(i);
        }
    }
    mUnk_0a = -1;
}

ARM void EquipRope::func_ov014_0213dba4(Vec3p *param1) {
    if (mUnk_0a >= 1) {
        Vec3p start = mUnk_18[0].vec;
        Vec3p end   = mUnk_18[1].vec;
        Vec3p dir;
        Vec3p_Sub(&end, &start, &dir);
        q20 invLength = (s64) 0x1000000 / Vec3p_Length(&dir);
        dir.x         = MUL_Q20(dir.x, invLength);
        dir.y         = MUL_Q20(dir.y, invLength);
        dir.z         = MUL_Q20(dir.z, invLength);

        Vec3p offset;
        Vec3p_Sub(param1, &start, &offset);
        Vec3p pos;
        Vec3p_Axpy(Vec3p_Dot(&offset, &dir), &dir, &start, &pos);
        data_027e0e58->func_ov000_0207c1b0(0x26, &pos, 1, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x27, &pos, 1, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x28, &pos, 1, 0, 0);
        data_027e0e58->func_ov000_0207c1b0(0x29, &pos, 1, 0, 0);

        Vec3p middle;
        middle.x = (start.x + end.x) / 2;
        middle.y = (start.y + end.y) / 2;
        middle.z = (start.z + end.z) / 2;
        data_027e0e58->func_ov000_0207c1b0(0x2a, &middle, 1, (unk32) this, (unk32) func_ov014_0213d230);
    }
    func_ov014_0213db60();
}

ARM s32 EquipRope::func_ov014_0213dda0() {
    s32 result = -1;
    for (s16 i = 0; i < 2; i++) {
        if (mUnk_18[i].mState != 0) {
            result = i;
        }
    }
    return result;
}

ARM s32 EquipRope::func_ov14_0213ddd4(Actor *actor) {
    if (!mUnk_68) {
        return -1;
    }
    s32 index = func_ov14_0213d480(actor->mRef.id);
    if (index >= 0) {
        return index;
    }
    if (!HasRopeActor()) {
        Cylinder hitbox;
        actor->GetHitbox(&hitbox);
        s32 dist = mUnk_50.y - hitbox.pos.y;
        if (dist < 0) {
            dist = -dist;
        }
        if (dist < hitbox.size + ActorRope::func_ov014_0212384c() && actor->IsHitboxTouched(false)) {
            EquipRope_Unk_18 point;
            point.mState     = 5;
            point.mRef.id    = actor->mRef.id;
            point.mRef.index = actor->mRef.index;
            point.func_ov057_02198e80();
            point.func_ov057_02198fc0(actor->mType);
            if (!mUnk_18[0].func_ov057_02199104(&point)) {
                return -1;
            }
            return func_ov14_0213d480(point.mRef.id);
        }
    }
    return -1;
}

ARM bool EquipRope::func_ov14_0213defc(Actor *actor) {
    bool found = false;
    for (s32 i = 0; i < 2; i++) {
        if (found) {
            mUnk_18[i - 1] = mUnk_18[i];
        }
        if (!found && mUnk_18[i].mRef.id == actor->mRef.id) {
            if (mUnk_18[i].mState == 3 || mUnk_18[i].mState == 5) {
                found = true;
            }
        }
    }
    if (found) {
        mUnk_18[1].mState  = 0;
        mUnk_18[1].mUnk_18 = 0;
        mUnk_18[1].mUnk_19 = 0;
    }
    return found;
}

ARM bool EquipRope::func_ov014_0213dfbc(Cylinder *cylinder, s32 param2, Vec3p *vec) {
    if (mUnk_0a < 1) {
        return false;
    }
    if (mUnk_18[0].mUnk_19 != 2 || mUnk_18[1].mUnk_19 != 2) {
        return false;
    }

    Vec3p start = mUnk_18[0].vec;
    Vec3p end   = mUnk_18[1].vec;
    Approach_thunk(&start.y, cylinder->pos.y, 0x333);
    Approach_thunk(&end.y, cylinder->pos.y, 0x333);
    Vec3p lineStart;
    lineStart.x = start.x;
    lineStart.y = start.y;
    lineStart.z = start.z;
    Vec3p lineEnd;
    lineEnd.x = end.x;
    lineEnd.y = end.y;
    lineEnd.z = end.z;

    bool hit = false;
    if (cylinder->func_ov000_0208f030(&lineStart, &lineEnd, 0x19a)) {
        if (HasRopeActor()) {
            hit = true;
        }
    }
    if (!hit) {
        return false;
    }
    if (vec != NULL) {
        s16 angle = func_ov014_0213d63c(0);
        s16 diff  = param2 - angle;
        if (diff >= 0) {
            angle -= 0x4000;
        } else {
            angle += 0x4000;
        }
        u16 normal = angle;
        vec->x     = SIN(normal);
        vec->y     = 0;
        vec->z     = COS(normal);
    }
    return true;
}

ARM void EquipRope::func_ov014_0213e144(Vec3p *param1, Vec3p *param2, s32 param3) {
    Cylinder *cylinder = (Cylinder *) param1;
    Vec3p diff;
    diff.x = mUnk_18[0].vec.x;
    diff.y = mUnk_18[0].vec.y;
    diff.z = mUnk_18[0].vec.z;
    Vec3p_Sub(&diff, &cylinder->pos, &diff);
    q20 dist = cylinder->size + (Vec3p_Dot(param2, &diff) + 0x19a);
    if (param3 != 0) {
        *(q20 *) param3 = dist;
    }
    Vec3p pos = cylinder->pos;
    pos.y     = mUnk_18[0].vec.y;
    Vec3p_Axpy(((dist * 0x19a + 0x800) >> 12) - cylinder->size, param2, &pos, &pos);

    ActorRope *rope  = GetRopeActor();
    rope->mUnk_174.x = pos.x;
    rope->mUnk_174.y = pos.y;
    rope->mUnk_174.z = pos.z;
    rope->mUnk_16b   = 1;
}

ARM bool EquipRope::func_ov014_0213e20c(s32 param1, Vec3p *param2) {
    bool result              = false;
    EquipRope_MapObject *obj = (EquipRope_MapObject *) gMapManager->MapData_vfunc_78(&mUnk_18[param1].mTile);
    if (obj != NULL && func_ov013_0213d248(obj->vfunc_1c())) {
        if (mUnk_18[param1].mUnk_18 == 0) {
            if (!func_ov014_0214bd7c(obj)) {
                Vec3p diff;
                Vec3p_Sub(param2, &mUnk_18[param1].vec, &diff);
                s16 angle = obj->mUnk_0c - (s16) FX_Atan2Idx(diff.x, diff.z);
                if (angle < 0) {
                    angle = -angle;
                }
                if (angle < 0x4000) {
                    func_ov014_0214bc98(obj);
                }
            } else if (!func_ov014_0214be64(obj)) {
                func_ov014_0214bd08(obj);
                result                  = true;
                mUnk_18[param1].mUnk_18 = result;
            }
        }
        Vec3p pos;
        obj->vfunc_8c(&pos);
        mUnk_18[param1].vec.x = pos.x;
        mUnk_18[param1].vec.z = pos.z;
    }
    return result;
}

ARM bool EquipRope::func_ov014_0213e328() {
    if (mUnk_0a < 0) {
        return false;
    }

    q20 length = 0;
    Vec3p *points[2];
    for (s32 i = 0; i <= mUnk_0a; i++) {
        s32 state    = mUnk_18[i].mState;
        Actor *actor = state == 3 ? gActorManager->GetActor(&mUnk_18[i].mRef) : NULL;
        EquipRope_MapObject *obj =
            state == 2 ? (EquipRope_MapObject *) gMapManager->MapData_vfunc_78(&mUnk_18[i].mTile) : NULL;
        if (actor != NULL) {
            length += actor->mHitbox.size;
        } else if (obj != NULL) {
            EquipRope_MapSubObject *sub = obj->vfunc_54();
            length += sub == NULL ? 0 : sub->vfunc_40();
        } else {
            return false;
        }
        points[i] = &mUnk_18[i].vec;
    }
    if (mUnk_0a == 0) {
        points[1] = &mUnk_78;
        length += data_027e0fd4->mUnk_020.size;
    }

    if (Vec3p_Distance(points[0], points[1]) < length) {
        if (mUnk_0a == 0) {
            mUnk_6a = true;
        }
        mUnk_69 = true;
        return false;
    }

    for (s32 j = 0; j <= mUnk_0a; j++) {
        if (mUnk_18[j].mState == 2) {
            Vec3p pos;
            func_ov014_0213d5d0((unk32 *) &pos, j);
            if (mUnk_0a == 0 || mUnk_18[1 - j].mUnk_19 == 2) {
                if (func_ov014_0213e20c(j, &pos) && mUnk_0a == 0) {
                    func_ov057_02199e24();
                } else {
                    GetRopeActor()->func_ov014_02123c54(j);
                }
            }
        }
    }
    return true;
}

ARM void func_ov014_0213e544(ActorRope_PointList *list, Vec3p *point) {
    list->mPoints[list->mCount] = point;
    list->mCount++;
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

ARM void func_ov014_0213e55c(ActorRope_PointList *list) {
    if ((u32) list->mCount < 2) {
        return;
    }

    Vec3p *point = list->mPoints[0];
    Vec3p first;
    first.x = point->x;
    first.y = point->y;
    first.z = point->z;
    s32 curX;
    s32 curY;
    func_01ffe468(data_027e0f64->func_ov000_0208b180(), &first, &curX, &curY, false);
    s32 prevX = curX;
    s32 prevY = curY;
    s32 nextX;
    s32 nextY;
    u16 angles[8];
    u32 i;
    for (i = 0; i < (u32) list->mCount; i++) {
        if (i < (u32) list->mCount - 1) {
            Vec3p *nextPoint = list->mPoints[i + 1];
            Vec3p next;
            next.x = nextPoint->x;
            next.y = nextPoint->y;
            next.z = nextPoint->z;
            func_01ffe468(data_027e0f64->func_ov000_0208b180(), &next, &nextX, &nextY, false);
        }
        angles[i] = FX_Atan2Idx(nextX - prevX, nextY - prevY);
        prevX     = curX;
        prevY     = curY;
        curX      = nextX;
        curY      = nextY;
    }

    Vec3p *camera = func_02018450();
    Vec3p right   = camera[0];
    Vec3p up      = camera[1];
    Vec3p prev    = gVec3p_ZERO;

    q20 texCoord = 0;
    PushCommand(0x2a, (((u16) data_027e0d44[0xaa]) & ~0xe0000000) | 0x30000 | 0x8000000);
    PushCommand(0x2b, ((u16) data_027e0d44[0xab]) & ~0xe0000000);
    PushCommand(0x30, 0xffff);
    PushCommand(0x31, texCoord);
    PushCommand(0x29, 0x001f20c0);
    PushGeometryCommand(0x11, NULL, texCoord);
    PushCommand(0x40, 3);

    for (i = texCoord; i < (u32) list->mCount; i++) {
        u16 angle  = angles[i];
        Vec3p side = right;
        q20 scale  = MUL_Q20(COS(angle), 0xf6);
        side.x     = MUL_Q20(side.x, scale);
        side.y     = MUL_Q20(side.y, scale);
        side.z     = MUL_Q20(side.z, scale);
        Vec3p_Axpy(MUL_Q20(SIN(angle), 0xf6), &up, &side, &side);
        PushGeometryCommand(0x11, NULL, 0);

        Vec3p *current = list->mPoints[i];
        Vec3p trans;
        trans.x = current->x - prev.x;
        trans.y = current->y - prev.y;
        trans.z = current->z - prev.z;
        PushGeometryCommand(0x1c, &trans, 3);

        u32 tex = (u16) (s16) (texCoord >> 8) << 16;
        PushCommand(0x22, tex);
        PushVertex(side.x, side.y, side.z);
        PushCommand(0x22, tex | 0x80);
        PushVertex(-side.x, -side.y, -side.z);

        current = list->mPoints[i];
        prev.x  = current->x;
        prev.y  = current->y;
        prev.z  = current->z;
        if (i < (u32) list->mCount - 1) {
            texCoord += MUL_Q20(Vec3p_Distance(current, list->mPoints[i + 1]), 0x3c000);
        }
    }
    PushGeometryCommand(0x41, NULL, 0);
    PushCommand(0x12, list->mCount + 1);
}
