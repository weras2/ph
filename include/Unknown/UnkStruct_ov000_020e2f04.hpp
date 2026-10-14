#pragma once

#include <nds/math.h>

#include "Physics/AABB.hpp"
#include "System/SysNew.hpp"
#include "global.h"
#include "types.h"

class UnkStruct_ov000_020e2f04 : public SysObject {
public:
    /* 00 (vtable) */
    /* 04 */ unk8 mUnk_04;
    /* 05 */ unk8 mUnk_05;
    /* 06 */ unk8 mUnk_06[0x2];
    /* 08 */ unk32 mUnk_08;
    /* 0c */ unk32 mUnk_0c;
    /* 10 */

    /* 00 */ virtual ~UnkStruct_ov000_020e2f04();
    /* 08 */ virtual unk32 vfunc_08() = 0;
    /* 0c */ virtual void vfunc_0c();
    /* 10 */ virtual void vfunc_10();
    /* 14 */ virtual void vfunc_14(AABB *param1, unk32 param2, unk32 param3, unk32 param4);
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual void vfunc_1c();
    /* 20 */ virtual void SetBoundingBox(AABB *param1);
    /* 24 */ virtual void vfunc_24();
    /* 28 */ virtual void vfunc_28();
    /* 2c */ virtual void GetBoundingBox(AABB *bbox);
    /* 30 */ virtual void SetPosition(Vec3p *pos)                            = 0;
    /* 34 */ virtual void vfunc_34()                                         = 0;
    /* 38 */ virtual void vfunc_38()                                         = 0;
    /* 3c */ virtual void GetPosition(Vec3p *pos)                            = 0;
    /* 40 */ virtual q20 GetSizeXZ()                                         = 0;
    /* 44 */ virtual q20 GetHeight()                                         = 0;
    /* 48 */ virtual bool ContainsInXZ(Vec3p *pos)                           = 0;
    /* 4c */ virtual bool Contains(Vec3p *pos)                               = 0;
    /* 50 */ virtual bool IntersectsCube(Cube *cube)                         = 0;
    /* 54 */ virtual void vfunc_54(Cube *param1, Vec3p *param2, u32 *param3) = 0;
    /* 58 */ virtual bool vfunc_58(unk32 param1, unk32 param2, s32 param3);
    /* 5c */

    inline UnkStruct_ov000_020e2f04() :
        mUnk_04(1),
        mUnk_05(0),
        mUnk_08(0),
        mUnk_0c(0) {}
};
