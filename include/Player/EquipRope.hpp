#pragma once

#include "global.h"
#include "nds/math.h"
#include "types.h"

#include "Actor/ActorRef.hpp"
#include "Actor/Player/ActorRope.hpp"
#include "Map/TilePos.hpp"
#include "Physics/Cylinder.hpp"
#include "Player/EquipItem.hpp"
#include "Render/ModelRender.hpp"
#include "Unknown/UnkStruct_ov000_020b7d74.hpp"

struct EquipRope_Vec3p : public Vec3p {
    inline EquipRope_Vec3p() {}
    inline EquipRope_Vec3p &operator=(const EquipRope_Vec3p &other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
    inline EquipRope_Vec3p &operator=(Vec3p other) {
        x = other.x;
        y = other.y;
        z = other.z;
        return *this;
    }
};

struct EquipRope_Unk_18 {
    /* 00 */ EquipRope_Vec3p vec;
    /* 0c */ ActorRef mRef;
    /* 14 */ TilePos mTile;
    /* 16 */ s16 mState;
    /* 18 */ u8 mUnk_18;
    /* 19 */ s8 mUnk_19;
    /* 1c */

    EquipRope_Unk_18();
    ~EquipRope_Unk_18();

    bool func_ov057_02198e80();
    void func_ov057_02198fc0(u32 param1);
    void func_ov057_02199028(s32 param1);
    bool func_ov057_02199104(EquipRope_Unk_18 *other);
};

#pragma push
#pragma thumb off
inline EquipRope_Unk_18::EquipRope_Unk_18() {
    mState  = 0;
    mUnk_18 = 0;
    mUnk_19 = 0;
}
#pragma thumb on
inline EquipRope_Unk_18::~EquipRope_Unk_18() {}
#pragma pop

class ItemModel;

// Constructor of a small render object (vtable compatible with ModelRender); returns the object
extern "C" void *func_ov000_020bd618(void *param1, ItemModel *model, u16 param3, u16 param4);

class EquipRope_Unk_02198dd0 {
public:
    /* 0 (vtable) */
    /* 4 */ unk32 mUnk_4;
    /* 8 */

    /* 00 */ virtual ~EquipRope_Unk_02198dd0();
    /* 08 */ unk32 vfunc_08();
    /* 0c */ unk32 vfunc_0c();
    /* 10 */ unk32 vfunc_10(s32 *param1);
    /* 14 */ unk32 vfunc_14();
    /* 18 */

    EquipRope_Unk_02198dd0();
};

class Actor;
class LinkStateItem;

class EquipRope : public EquipItem {
public:
    /* 00 (base) */
    /* 09 */ unk8 mUnk_09;
    /* 0a */ unk16 mUnk_0a;
    /* 0c */ u8 mUnk_0c;
    /* 0d */ unk8 mUnk_0d[3];
    /* 10 */ ActorRef mRopeRef;
    /* 18 */ EquipRope_Unk_18 mUnk_18[2];
    /* 50 */ Vec3p mUnk_50;
    /* 5c */ unk8 mUnk_5c[0xc];
    /* 68 */ bool mUnk_68;
    /* 69 */ bool mUnk_69;
    /* 6a */ bool mUnk_6a;
    /* 6b */ unk8 mUnk_6b;
    /* 6c */ unk16 mUnk_6c;
    /* 6e */ unk8 mUnk_6e[2];
    /* 70 */ unk16 mUnk_70;
    /* 72 */ unk8 mUnk_72[0x2];
    /* 74 */ q20 mUnk_74;
    /* 78 */ Vec3p mUnk_78;
    /* 84 */ ModelRender *mUnk_84;
    /* 88 */ unk8 mUnk_88[0x18];
    /* a0 */ UnkStruct_ov000_020b7d74 mUnk_a0;
    /* a4 */

    /* 04 */ virtual ~EquipRope() override;
    /* 0c */ virtual ItemFlag GetId() const override;
    /* 10 */ virtual void vfunc_10() override;
    /* 14 */ virtual bool IsUsable(unk32 param1) const override;
    /* 18 */ virtual void vfunc_18() override;
    /* 1c */ virtual void vfunc_1c() override;
    /* 30 */ virtual void vfunc_30() override;
    /* 38 */ virtual void vfunc_38(unk32 param1) override;
    /* 50 */

    u16 GetAmmo();

    EquipRope();
    bool func_ov014_0213d3d4(Vec3p *vec);
    void func_ov014_0213d404(unk32 *param1);
    ActorRope *GetRopeActor();
    inline bool HasRopeActor() {
        return GetRopeActor() != NULL;
    }
    s32 func_ov14_0213d440(s32 actorId);
    s32 func_ov14_0213d480(s32 actorId);
    bool func_ov014_0213d4c8();
    bool func_ov014_0213d4ec(unk32 *param1, s32 param2);
    s32 func_ov014_0213d594(s32 param1);
    bool func_ov014_0213d5d0(unk32 *param1, s32 param2);
    s16 func_ov014_0213d63c(s32 param1);
    bool func_ov014_0213d684();
    bool func_ov014_0213d6e0();
    bool func_ov014_0213d71c(s32 param1, ActorRef *param2);
    bool func_ov014_0213d788(s32 param1);
    bool func_ov14_0213d81c(s32 index, Vec3p *vec);
    void func_ov14_0213d91c(s32 index);
    bool func_ov014_0213d9ac();
    bool func_ov14_0213dadc(s32 index, Cylinder *cylinder);
    void func_ov014_0213db34();
    void func_ov014_0213db60();
    void func_ov014_0213dba4(Vec3p *param1);
    s32 func_ov014_0213dda0();
    s32 func_ov14_0213ddd4(Actor *actor);
    bool func_ov14_0213defc(Actor *actor);
    bool func_ov014_0213dfbc(Cylinder *cylinder, s32 param2, Vec3p *vec);
    void func_ov014_0213e144(Vec3p *param1, Vec3p *param2, s32 param3);
    bool func_ov014_0213e20c(s32 param1, Vec3p *param2);
    bool func_ov014_0213e328();

    void func_ov057_021990ec();
    void func_ov057_021990f8();
    bool func_ov057_0219922c(u32 param1);
    void func_ov057_021992b4(s32 param1);
    bool func_ov057_0219939c(s32 *param1, s32 param2);
    bool func_ov057_02199454(s32 param1);
    bool func_ov057_021994c0(unk32 *param1);
    s32 func_ov057_021996b0(Vec3p *param1);
    void func_ov057_02199ad8();
    void func_ov057_02199c78();
    void func_ov057_02199d54();
    void func_ov057_02199e24();
};
