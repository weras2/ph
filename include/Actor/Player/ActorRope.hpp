#pragma once

#include "global.h"
#include "nds/math.h"
#include "types.h"

#include "Actor/Actor.hpp"
#include "Actor/ActorType.hpp"
#include "Unknown/UnkStruct_ov000_020beba8.hpp"

// List of points the rope is drawn through
struct ActorRope_PointList {
    /* 00 */ Vec3p *mPoints[8];
    /* 20 */ s32 mCount;
    /* 24 */
};

void func_ov014_0213e544(ActorRope_PointList *list, Vec3p *point);
void func_ov014_0213e55c(ActorRope_PointList *list);

class ActorRope_Unk_0219a3b0 : public UnkStruct_ov000_020beba8 {
public:
    /* 0 (base) */
    /* c */

    /* 00 */ virtual ~ActorRope_Unk_0219a3b0() override;
    /* 08 */ virtual bool vfunc_08(UnkStruct_ov000_020beba8_08 *param1) override;
    /* 10 */ virtual bool vfunc_10(s32 *param1) override;
    /* 1c */

    inline ActorRope_Unk_0219a3b0() :
        UnkStruct_ov000_020beba8(6) {}
};

class ActorRope : public Actor {
public:
    static ActorType gType;

    /* 000 (base) */
    /* 158 */ unk32 mUnk_158[3]; // render object, vtable compatible with ModelRender
    /* 164 */ s16 mUnk_164;
    /* 166 */ s16 mUnk_166;
    /* 168 */ s16 mUnk_168;
    /* 16a */ bool mUnk_16a;
    /* 16b */ u8 mUnk_16b;
    /* 16c */ bool mUnk_16c;
    /* 16d */ bool mUnk_16d;
    /* 16e */ unk16 mUnk_16e;
    /* 170 */ u16 mUnk_170;
    /* 172 */ unk8 mUnk_172[0x2];
    /* 174 */ Vec3p mUnk_174;
    /* 180 */ Vec3p mUnk_180;
    /* 18c */ Actor_UnkStruct_0a4 mUnk_18c;
    /* 1a0 */

    /* 00 */ virtual ~ActorRope() override;
    /* 08 */ virtual bool Init() override;
    /* 10 */ virtual void vfunc_10(u32 param1) override;
    /* 14 */ virtual void vfunc_14(u32 param1) override;
    /* 18 */ virtual void vfunc_18(u32 param1) override;
    /* 20 */ virtual void vfunc_20(bool param1) override;
    /* b4 */

    static ActorRope *Create();
    static void func_ov014_0212382c(Vec4p *vec);
    static q20 func_ov014_0212384c();
    s32 func_ov014_021238f0();
    void func_ov014_02123904();
    bool func_ov014_02123960();
    void func_ov014_02123c54(s32 param1);
    bool func_ov014_02123cd0(Vec3p *param1, s32 param2);
    bool func_ov014_02123e1c(s32 param1);
    bool func_ov014_02123e48(s32 state);

    ActorRope();
    q20 func_ov057_0219a5ac();
    void func_ov057_0219a6b8();
    void func_ov057_0219a850();
};
