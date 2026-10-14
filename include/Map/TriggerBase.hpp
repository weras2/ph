#pragma once

#include "global.h"
#include "types.h"

#include "nds/math.h"

#include "Physics/AABB.hpp"
#include "System/SysNew.hpp"

struct TriggerParams {
    /* 0 */ u8 id;
    /* 1 */ u8 zMin;
    /* 2 */ u8 xMin;
    /* 3 */ u8 zMax; // high byte of the radius for spheres
    /* 4 */ u8 xMax; // low byte of the radius for spheres
    /* 5 */ bool isAABB_Unk1;
    /* 6 */ u8 mUnk_6;
    /* 7 */ u8 mUnk_7;
    /* 8 */ u8 mUnk_8;
    /* 9 */ bool isAABB_Unk2;
    /* a */ bool isSphere;
    /* b */
};

class UnkStruct_TriggerBase : public SysObject {
public:
    virtual unk32 vfunc_00(void *);
};

class TriggerBase : public UnkStruct_TriggerBase {
public:
    /* 00 (vtable) */
    /* 04 */ bool mUnk_04;
    /* 05 */ u8 mId;
    /* 06 */ unk8 mUnk_06[2];
    /* 08 */ u32 mUnk_08;
    /* 0c */ s32 mUnk_0c;
    /* 10 */ u32 mUnk_10;
    /* 14 */

    /* 00 */ virtual ~TriggerBase();
    /* 08 */ virtual void vfunc_08();
    /* 0c */ virtual bool vfunc_0c(bool param_2);
    /* 10 */ virtual unk32 vfunc_10();
    /* 14 */ virtual bool Overlaps(Vec3p *point);
    /* 18 */ virtual bool GetBoundingBox(AABB *bbox);
    /* 1c */

    TriggerBase(TriggerParams *params);
    TriggerBase(u8 id, u32 param2, u32 param3, u32 param4);
};
