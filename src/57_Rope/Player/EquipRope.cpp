#include "Player/EquipRope.hpp"
#include "Actor/ActorManager.hpp"
#include "Actor/ActorSpawner.hpp"
#include "DTCM/UnkStruct_027e0de4.hpp"
#include "DTCM/UnkStruct_027e0e58.hpp"
#include "DTCM/UnkStruct_027e0f64.hpp"
#include "DTCM/UnkStruct_027e0fd4.hpp"
#include "DTCM/UnkStruct_027e0ffc.hpp"
#include "Item/ItemManager.hpp"
#include "Map/MapManager.hpp"
#include "Player/LinkStateItem.hpp"
#include "Player/PlayerBase.hpp"
#include "Player/PlayerControl.hpp"
#include "Player/PlayerLinkBase.hpp"
#include "Save/AdventureFlags.hpp"
#include "Unknown/UnkStruct_020eec9c.hpp"
#include "nds/g3d/sbc.h"

struct UnkStruct_ov057_0219ab14 {
    /* 0 */ bool mUnk_0;
    /* 4 */ s32 mUnk_4;
};

struct UnkStruct_ov014_0213e544 {
    /* 00 */ unk8 mUnk_00[0x20];
    /* 20 */ unk32 mUnk_20;
};

extern "C" {
void func_ov000_020b41c4(ModelRender *param1);
void func_ov000_020b1d3c(Vec3p *param1);
void func_ov000_0207c444(UnkStruct_027e0e58 *param1, EquipRope_a0 **param2);
void func_ov000_0207c1f8(UnkStruct_027e0e58 *param1, EquipRope_a0 **param2, unk32 param3, Vec3p *param4, unk32 param5);
void func_0202b2f8(Vec3p *param1, Vec3p *param2, q20 param3);
void func_0202d95c(Vec3p *param1, q20 param2);
void func_ov000_020bd944(unk32 *param1);
void func_ov000_020bde54(unk32 *param1, Vec3p *param2);
void func_ov000_020bdfc0(unk32 *param1);
void func_ov000_020bd958(unk32 *param1, unk32 param2, unk32 param3, unk32 param4, unk32 param5, unk32 param6, unk32 param7);
bool func_ov000_02087f08(UnkStruct_027e0f64_04 *param1, unk32 param2);
void func_ov000_0208967c(UnkStruct_027e0f64_04 *param1, unk32 param2, Vec3p *param3, const Vec3p *param4, unk32 param5,
                         unk32 param6);
void func_ov000_020d7cd4(UnkStruct_020eec9c *param1, unk32 param2);
void Vec3p_RotateY(s32 angle, Vec3p *vec);
}
bool func_ov013_0213d248(s32 param1);
void func_ov014_0213e544(UnkStruct_ov014_0213e544 *param1, Vec3p *param2);
void func_ov014_0213e55c(UnkStruct_ov014_0213e544 *param1);
extern unk8 data_027e037c[];

EquipRope_Unk_02198dd0 sUnk_02198dd0;
static UnkStruct_ov057_0219ab14 data_ov057_0219ab14;

ARM bool func_ov057_02198d00(Vec3p *vec, Vec3p *dest, q20 step) {
    Vec3p diff;
    Vec3p_Sub(vec, dest, &diff);
    q20 length = Vec3p_Length(&diff);
    if (length <= step) {
        return false;
    }
    q20 scale = CoDivide64By32(step, length);
    vec->x    = dest->x + MUL_Q20(scale, diff.x);
    vec->y    = dest->y + MUL_Q20(scale, diff.y);
    vec->z    = dest->z + MUL_Q20(scale, diff.z);
    return true;
}

ARM bool EquipRope_Unk_02198dd0::vfunc_08(UnkStruct_ov000_020beba8_08 *param1) {
    return false;
}

ARM void EquipRope_Unk_02198dd0::vfunc_0c(unk16 *param1) {}

ARM bool EquipRope_Unk_02198dd0::vfunc_14(u16 *param1) {
    return false;
}

ARM EquipRope_Unk_02198dd0::EquipRope_Unk_02198dd0() {
    mUnk_4 = 0;
}

struct EquipRope_MapObject {
    /* 00 (vtable) */
    /* 04 */ u32 mFlags;
    /* 08 */ unk8 mUnk_08[0xc];
    /* 14 */ TilePos mTile;
    /* 16 */

    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual void vfunc_04();
    /* 08 */ virtual void vfunc_08();
    /* 0c */ virtual void vfunc_0c();
    /* 10 */ virtual void vfunc_10();
    /* 14 */ virtual void vfunc_14();
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual s32 vfunc_1c();
};

ARM bool EquipRope_Unk_02198dd0::vfunc_10(s32 *param1) {
    EquipRope_MapObject *obj = (EquipRope_MapObject *) param1;
    if (!(obj->mFlags & 0x20)) {
        return false;
    }
    EquipRope_Unk_18 hit;
    hit.mType = 4;
    hit.mTile = obj->mTile;
    hit.func_ov057_02198e80();
    hit.func_ov057_02199028(obj->vfunc_1c());
    ((EquipRope_Unk_18 *) mUnk_4)->func_ov057_02199104(&hit);
    return false;
}

ARM bool EquipRope_Unk_18::func_ov057_02198e80() {
    switch (mType) {
        case 4: {
            EquipRope_MapObject *obj = (EquipRope_MapObject *) gMapManager->MapData_vfunc_78(&mTile);
            if (obj == NULL) {
                return false;
            }
            s32 kind = obj->vfunc_1c();
            if (func_ov013_0213d248(kind)) {
                Vec3p pos;
                ((void (*)(EquipRope_MapObject *, Vec3p *))(*(void ***) obj)[35])(obj, &pos);
                vec.x = pos.x;
                vec.y = pos.y;
                vec.z = pos.z;
                vec.y += 0x99a;
            } else {
                Vec3p *pos = (Vec3p *) ((u8 *) obj + 0x18);
                vec.x      = pos->x;
                vec.y      = pos->y;
                vec.z      = pos->z;
                if (kind == 144) {
                    vec.y += 0xc00;
                } else {
                    vec.y += 0x99a;
                }
            }
            return true;
        }
        case 5: {
            Actor *actor = gActorManager->GetActor(&mRef);
            if (actor == NULL) {
                return false;
            }
            Cylinder hitbox;
            actor->GetHitbox(&hitbox);
            vec.x = hitbox.pos.x;
            vec.y = hitbox.pos.y;
            vec.z = hitbox.pos.z;
            return true;
        }
    }
    return false;
}

ARM void EquipRope_Unk_18::func_ov057_02198fc0(u32 param1) {
    switch (param1) {
        case 'KORG':
        case 'MURD':
        case 'ENTS':
        case 'URAT':
            mUnk_19 = 1;
            return;
    }
    mUnk_19 = 0;
}

ARM void EquipRope_Unk_18::func_ov057_02199028(s32 param1) {
    switch (param1) {
        case 3:
        case 14:
        case 28:
            mUnk_19 = 0;
            return;
        case 2:
        case 53:
        case 103:
            mUnk_19 = 1;
            return;
        case 144:
            mUnk_19 = 2;
            return;
    }
    mUnk_19 = 2;
}

ARM bool EquipRope::IsUsable(unk32 param1) const {
    if (this->EquipItem::GetAmmo() > 0) {
        return true;
    }
    if (param1 == 0) {
        return false;
    }
    return gPlayerLink->func_ov000_020bba28();
}

ARM void EquipRope::func_ov057_021990ec(void *param1) {
    ((EquipRope *) param1)->func_ov057_02199ad8();
}

ARM void EquipRope::func_ov057_021990f8(void *param1) {
    ((EquipRope *) param1)->func_ov057_02199c78();
}

ARM bool EquipRope_Unk_18::func_ov057_02199104(EquipRope_Unk_18 *other) {
    for (s32 i = 0; i < 2; i++) {
        if (this[i].mType == 0) {
            for (s32 j = 0; j < i; j++) {
                if (other->mType == 4 && this[j].mTile == other->mTile) {
                    return false;
                }
                if (other->mType == 5 && other->mRef.id == this[j].mRef.id) {
                    return false;
                }
            }
            this[i] = *other;
            data_027e0ffc.func_ov000_020ceacc(0xef, &this[i].vec, 0);
            return true;
        }
    }
    return false;
}

ARM bool EquipRope::func_ov057_0219922c(TilePos param1) {
    for (s32 i = 0; i < 2; i++) {
        if (mUnk_18[i].mType == 4 && mUnk_18[i].mTile == param1) {
            return true;
        }
    }
    return false;
}

ARM void EquipRope::func_ov057_021992b4(bool param1) {
    if (param1) {
        if (!mUnk_0c) {
            mUnk_6e = mUnk_04;
        }
    } else {
        func_ov000_0207c444(data_027e0e58, &mUnk_a0);
    }
    mUnk_0c = param1;
}

ARM void EquipRope::vfunc_18() {
    this->func_ov014_0213db60();
    mRopeRef.Reset();
    for (s32 i = 0; i < 2; i++) {
        Vec3p pos      = mUnk_78;
        mUnk_18[i].vec = pos;
    }
    mUnk_68 = false;
    mUnk_0c = false;
    mUnk_6a = false;
    mUnk_74 = 0;
}

ARM void EquipRope::vfunc_1c() {
    if (!mUnk_69 && !this->func_ov014_0213d6e0()) {
        this->func_ov014_0213db60();
    }
    this->func_ov057_021992b4(0);
    mUnk_68 = false;
}

ARM bool EquipRope::func_ov057_0219939c(Vec3p *param1, s32 param2) {
    if (!mUnk_68) {
        return false;
    }
    if (param2 > 1) {
        return false;
    }
    if (param2 < 0) {
        this->func_ov014_0213d404(param1);
        return true;
    }
    for (s32 i = 0; i < 2 && mUnk_18[i].mType != 0; i++) {
        if (param2 == i) {
            *param1 = mUnk_18[i].vec;
            return true;
        }
    }
    if (param2 != 0) {
        return false;
    }
    *param1 = mUnk_50;
    return true;
}

ARM bool EquipRope::func_ov057_02199454(EquipRope_Unk_18 *param1) {
    switch (param1->mType) {
        case 4:
            return gMapManager->MapData_vfunc_78(&param1->mTile) != NULL;
        case 5:
            return gActorManager->GetActor(&param1->mRef) != NULL;
    }
    return false;
}

static const Vec3p data_ov057_0219a994 = {0, 0, 0x4cd};

ARM void EquipRope::func_ov057_021994c0(Vec3p *param1) {
    mUnk_50 = *param1;
    if (!mUnk_68) {
        mUnk_5c = *param1;
    }
    mUnk_68    = true;
    mUnk_69    = false;
    Vec3p prev = mUnk_5c;
    func_0202b2f8(&mUnk_5c, &mUnk_50, 0x199a);

    if (mUnk_18[0].mType != 0) {
        if (!this->func_ov057_02199454(&mUnk_18[0]) || Vec3p_Distance(&mUnk_78, &mUnk_18[0].vec) > 0xb000) {
            for (s32 i = 0; i < 2; i++) {
                mUnk_18[i].mType   = 0;
                mUnk_18[i].mUnk_18 = 0;
                mUnk_18[i].mUnk_19 = 0;
            }
        } else if (mUnk_18[1].mType != 0) {
            if (!this->func_ov057_02199454(&mUnk_18[1]) || Vec3p_Distance(&mUnk_18[0].vec, &mUnk_18[1].vec) > 0xb000) {
                mUnk_18[1].mType   = 0;
                mUnk_18[1].mUnk_18 = 0;
                mUnk_18[1].mUnk_19 = 0;
            }
        } else {
            func_ov057_02198d00(&mUnk_5c, &mUnk_18[0].vec, 0xa000);
        }
    } else {
        func_ov057_02198d00(&mUnk_5c, &mUnk_78, 0xa000);
    }

    UnkStruct hit;
    Vec4p sphere;
    ActorRope::func_ov014_0212382c(&sphere);
    sUnk_02198dd0.mUnk_4 = (unk32) mUnk_18;
    gMapManager->func_01ffbe78(&hit, &mUnk_5c, &prev, (Sphere *) &sphere, 1, 4, (unk32) &sUnk_02198dd0, 0);
}

ARM s32 EquipRope::func_ov057_021996b0(Vec3p *param1) {
    if (this->func_ov14_0213d420() != NULL) {
        this->func_ov014_0213d404(param1);
        Vec3p_Sub(&mUnk_18[0].vec, param1, param1);
        s32 length = Vec3p_Length(param1);
        func_0202d95c(param1, MUL_Q20(mUnk_74, 0x6e1));
        return length;
    }
    param1->x = 0;
    param1->y = 0;
    param1->z = 0;
    return 0;
}

ARM void EquipRope::vfunc_30() {
    mUnk_6c++;
    if (mUnk_0c) {
        s16 prevAngle = mUnk_6e;
        mUnk_6e += -0x1555;
        if (prevAngle <= 0 && mUnk_6e > 0) {
            data_ov000_020eec9c.func_ov000_020d7a84(0xe9, this->GetPlayerPos());
        }
        if (mUnk_a0 == NULL) {
            func_ov000_0207c1f8(data_027e0e58, &mUnk_a0, 0x172, &mUnk_78, 1);
            if (mUnk_a0 != NULL) {
                EquipRope_a0 *effect = mUnk_a0;
                s16 angle            = mUnk_04 - 0x2aab;
                if (effect != NULL) {
                    effect->mUnk_56 = angle;
                }
            }
        } else if (mUnk_a0 != NULL) {
            mUnk_a0->mUnk_28.x = mUnk_78.x + (*mUnk_a0->mUnk_20)->mUnk_4.x;
            mUnk_a0->mUnk_28.y = mUnk_78.y + (*mUnk_a0->mUnk_20)->mUnk_4.y;
            mUnk_a0->mUnk_28.z = mUnk_78.z + (*mUnk_a0->mUnk_20)->mUnk_4.z;
        }
    } else {
        ActorRope *rope = this->func_ov14_0213d420();
        if (rope != NULL) {
            s16 prev = mUnk_70;
            mUnk_70  = rope->mUnk_164 - 1;
            if (prev != mUnk_70 && mUnk_18[mUnk_70].mType != 0) {
                data_027e0ffc.func_ov000_020ceacc(0xeb, &rope->mPos, 0);
            }
        }
    }
    for (s32 i = 0; i < 2; i++) {
        mUnk_18[i].func_ov057_02198e80();
    }
    Approach_thunk((unk32 *) &mUnk_74, FLOAT_TO_Q20(1.0), 0x266);
}

ARM void EquipRope::vfunc_38(unk32 param1) {
    if (this->IsInUse() || mUnk_0a >= 0) {
        PushGeometryCommand(0x11, NULL, 0);
        G3d_RestoreMtx_inline(29);
        func_ov000_020b1d3c(&mUnk_78);
        if (mRopeRef.id == -1) {
            Vec3p offset = data_ov057_0219a994;
            if (mUnk_0c) {
                Vec3p_RotateY(mUnk_6e, &offset);
                Mat4x3p rot;
                Mat4x3p_InitYRotation(&rot, SIN((u16) mUnk_6e), COS((u16) mUnk_6e));
                Vec3p_Add(&mUnk_78, &offset, &rot.wColumn);
                PushGeometryCommand(0x17, data_027e037c + 0x4c, 12);
                PushGeometryCommand(0x19, &rot, 12);
            }
            func_ov000_020b41c4(mUnk_84);
            if (mUnk_0c) {
                Vec3p end;
                Vec3p_Add(&mUnk_78, &offset, &end);
                UnkStruct_ov014_0213e544 line;
                line.mUnk_20 = 0;
                func_ov014_0213e544(&line, &mUnk_78);
                func_ov014_0213e544(&line, &end);
                func_ov014_0213e55c(&line);
            }
        }
        u32 cmd = 1;
        PushGeometryCommand(0x12, &cmd, 1);
    }
    if (param1 != 0) {
        return;
    }
    if (gAdventureFlags->func_ov00_02097738()) {
        return;
    }
    if (!this->IsInUse() || !mUnk_68) {
        return;
    }
    data_027e0de4.func_ov000_0207bb1c(3, EquipRope::func_ov057_021990ec, this);
    data_027e0de4.func_ov000_0207bb1c(5, EquipRope::func_ov057_021990f8, this);
}

ARM void EquipRope::func_ov057_02199ad8() {
    if (mRopeRef.id != -1) {
        return;
    }
    unk32 points1[8];
    unk32 points2[8];
    unk32 line1[3];
    unk32 line2[3];
    func_ov000_020bd944(line1);
    func_ov000_020bd944(line2);
    line1[2] = (unk32) points1;
    line1[1] = 2;
    line2[1] = 2;
    line2[2] = (unk32) points2;
    if (mUnk_18[0].mType == 0) {
        Vec3p pos;
        pos.x = mUnk_78.x;
        pos.y = mUnk_78.y;
        pos.z = mUnk_78.z;
        func_ov000_020bde54(line1, &pos);
        func_ov000_020bde54(line1, &mUnk_5c);
    } else if (mUnk_18[1].mType == 0) {
        Vec3p pos;
        pos.x = mUnk_78.x;
        pos.y = mUnk_78.y;
        pos.z = mUnk_78.z;
        func_ov000_020bde54(line1, &pos);
        func_ov000_020bde54(line1, &mUnk_18[0].vec);
        func_ov000_020bde54(line2, &mUnk_18[0].vec);
        func_ov000_020bde54(line2, &mUnk_5c);
    } else {
        func_ov000_020bde54(line1, &mUnk_18[0].vec);
        func_ov000_020bde54(line1, &mUnk_18[1].vec);
        Vec3p pos;
        pos.x = mUnk_78.x;
        pos.y = mUnk_78.y;
        pos.z = mUnk_78.z;
        func_ov000_020bde54(line2, &pos);
        func_ov000_020bde54(line2, &mUnk_18[0].vec);
    }
    func_ov000_020bdfc0(line2);
    func_ov000_020bd958(line2, 0, 2, 0x7a29, 18, 0x2800, 1);
    func_ov000_020bdfc0(line1);
    func_ov000_020bd958(line1, 0, 2, 0x3400 - 1, 24, 0x2ccd, 1);
}

ARM void EquipRope::func_ov057_02199c78() {
    for (s32 i = 0; i < 2; i++) {
        switch (mUnk_18[i].mType) {
            case 4: {
                UnkStruct_ov000_020beba8 *obj = (UnkStruct_ov000_020beba8 *) gMapManager->MapData_vfunc_78(&mUnk_18[i].mTile);
                if (obj != NULL) {
                    Vec3p pos;
                    ((void (*)(UnkStruct_ov000_020beba8 *, Vec3p *, s32))(*(void ***) obj)[25])(obj, &pos, 6);
                    this->func_ov000_020be9e4(pos, mUnk_6c);
                }
            } break;
            case 5: {
                Actor *actor = gActorManager->GetActor(&mUnk_18[i].mRef);
                if (actor != NULL) {
                    Cylinder hitbox;
                    actor->GetHitbox(&hitbox);
                    this->func_ov000_020be9e4(hitbox.pos, mUnk_6c);
                }
            } break;
        }
    }
}

ARM void EquipRope::func_ov057_02199d54() {
    if (this->EquipItem::GetAmmo() <= 0) {
        return;
    }
    Vec3p pos = *this->GetPlayerPos();
    pos.y += FLOAT_TO_Q20(0.5);
    ActorSpawnOptions options;
    options.mUnk_1c.id = 0;
    options.mAngle     = mUnk_04;
    gActorSpawner->Spawn(ActorTypeId_GrapplingHook, &pos, &options, &mRopeRef);
    if (mRopeRef.id == -1) {
        return;
    }
    data_ov000_020eec9c.func_ov000_020d7a84(0xec, this->GetPlayerPos());
    mUnk_70 = -1;
}

ARM void EquipRope::func_ov057_02199e24() {
    mUnk_69 = true;
    mUnk_6a = true;
}

ARM EquipRope_Unk_02198dd0::~EquipRope_Unk_02198dd0() {}

EquipRope *GetEquipRope();

static LinkStateBase_UnkStruct1 data_ov057_0219aa40 = {0x42, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(1.0)}};
static LinkStateBase_UnkStruct1 data_ov057_0219aa50 = {0x40, {FLOAT_TO_Q20(2.5), 0, FLOAT_TO_Q20(18.0)}};
static LinkStateBase_UnkStruct1 data_ov057_0219aa60 = {0x3f, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(12.0)}};
static LinkStateBase_UnkStruct1 data_ov057_0219aa70 = {0x41, {FLOAT_TO_Q20(1.0), 0, FLOAT_TO_Q20(22.0)}};

ARM void LinkStateItem::func_ov057_02199e64() {
    this->func_ov00_020a89bc(&data_ov057_0219aa60, 1);
    mUnk_44 = gVec3p_ZERO;
    GetEquipRope()->func_ov057_021992b4(1);
    data_ov057_0219ab14.mUnk_0 = false;
    gPlayerControl->ResetAim();
}

ARM EquipRope *GetEquipRope() {
    return (EquipRope *) ItemManager::GetEquipItemUnchecked(ItemFlag_GrapplingHook);
}

ARM void LinkStateItem::func_ov057_02199edc() {
    EquipRope *rope = GetEquipRope();
    if (rope->func_ov014_0213d6e0()) {
        data_ov057_0219ab14.mUnk_0 = true;
        data_ov057_0219ab14.mUnk_4 = 0;
        this->EquipItem_vfunc_28();
        this->func_ov00_020a8a4c(&data_ov057_0219aa40, 1);
        gPlayerControl->mUnk_7a = false;
    }
    if (data_ov057_0219ab14.mUnk_0) {
        this->func_ov057_0219a208();
        return;
    }

    Vec3p prevAim = mUnk_44;
    if (data_ov057_0219aa70.mUnk_00 == this->Get_PlayerControlData_Unk100()) {
        if (rope->mUnk_69) {
            gPlayerControl->UpdateUsingEquipItem();
            if (rope->mUnk_6a) {
                this->ChangeLinkState(LinkStateId_Move);
                return;
            }
        }
        ActorRope *ropeActor = rope->func_ov14_0213d420();
        if (ropeActor == NULL) {
            this->func_ov00_020a8a90((unk32) &data_ov057_0219aa60);
            rope->func_ov057_021992b4(1);
        } else if (!this->func_ov00_020a8b80()) {
            gPlayerControl->UpdateUsingEquipItem();
            ropeActor->func_ov014_02123960();
            this->ChangeLinkState(LinkStateId_Move);
            return;
        }
    } else if (data_ov057_0219aa50.mUnk_00 == this->Get_PlayerControlData_Unk100()) {
        if (this->func_ov00_020a8b04(0xb000, true)) {
            rope->func_ov057_02199d54();
        }
        if (this->func_ov00_020a8b3c(1)) {
            this->func_ov00_020a89bc(&data_ov057_0219aa70, 1);
        }
    } else if (gPlayerControl->CheckUntouchedNow(1) && rope->mUnk_68) {
        rope->func_ov057_021992b4(0);
        if (data_ov057_0219aa60.mUnk_00 == this->Get_PlayerControlData_Unk100()) {
            this->func_ov00_020a89bc(&data_ov057_0219aa50, 1);
        }
    } else {
        Vec3p target;
        if (gPlayerControl->func_ov00_020b1058(&target, 0x800, &prevAim,
                                               rope->mUnk_18[0].mType != 0 ? &rope->mUnk_18[0].vec : NULL)) {
            rope->func_ov057_021994c0(&target);
            Vec3p lookAt;
            if (rope->func_ov014_0213d3d4(&lookAt)) {
                this->LookAt(&lookAt);
            } else {
                this->LookAt(&target);
            }
            if (rope->mUnk_18[1].mType == 0) {
                mUnk_44 = prevAim;
            }
        } else {
            mUnk_44 = prevAim;
        }
    }

    if (!func_ov000_02087f08(data_027e0f64->mUnk_4, 6)) {
        return;
    }
    Vec3p aimPos;
    Vec3p_Add(&mUnk_44, &gPlayerPos, &aimPos);
    func_ov000_0208967c(data_027e0f64->mUnk_4, 6, &aimPos, &gVec3p_ZERO, 0, 0);
}

ARM void LinkStateItem::func_ov057_0219a208() {
    EquipRope *rope = GetEquipRope();
    if (!(rope->func_ov14_0213d420() != NULL)) {
        this->GetPlayerVel()->x = 0;
        this->GetPlayerVel()->z = 0;
        gPlayerControl->UpdateUsingEquipItem();
        this->ChangeLinkState(LinkStateId_Move);
        return;
    }
    this->func_ov00_020a8d40()->mUnk_0bb[0] = 0;
    this->func_ov00_020a8d40()->mUnk_0bb[1] = 0;
    Vec3p vel;
    s32 length = rope->func_ov057_021996b0(&vel);
    if (length < data_ov057_0219ab14.mUnk_4 || data_ov057_0219ab14.mUnk_4 <= 0) {
        data_ov057_0219ab14.mUnk_4           = length;
        *this->GetPlayerVel()                = vel;
        this->func_ov00_020a8d40()->mUnk_0a4 = 2;
        func_ov000_020d7cd4(&data_ov000_020eec9c, 0xee);
        return;
    }
    gPlayerControl->UpdateUsingEquipItem();
    this->ChangeLinkState(LinkStateId_Move);
}

ARM void LinkStateItem::StopUsingRope() {
    EquipRope *rope = GetEquipRope();
    if (rope->func_ov014_0213d6e0()) {
        rope->func_ov014_0213db60();
    }
    gPlayerControl->mUnk_7a = true;
}

ARM bool LinkStateItem::func_ov057_0219a364() {
    EquipRope *rope = GetEquipRope();
    if (rope->func_ov014_0213d6e0()) {
        return false;
    }
    if (data_ov057_0219aa70.mUnk_00 == this->Get_PlayerControlData_Unk100() && !rope->mUnk_69) {
        return false;
    }
    return true;
}
