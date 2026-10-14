#pragma once

#include "global.h"
#include "types.h"

#include "DTCM/UnkStruct_027e0f6c.hpp"
#include "Map/TriggerAABB.hpp"
#include "Unknown/UnkStruct_ov000_020e2f04.hpp"

class TriggerAABB_Unk2_Unk1 : public UnkStruct_ov000_020e2f04 {
public:
    /* 00 (base) */
    /* 14 */ AABB mUnk_14;
    /* 2c */

    /* 00 */ virtual ~TriggerAABB_Unk2_Unk1() override {}
    /* 08 */ virtual unk32 vfunc_08() override;
    /* 14 */ virtual void vfunc_14(AABB *param1, unk32 param2, unk32 param3, unk32 param4) override;
    /* 20 */ virtual void SetBoundingBox(AABB *param1) override;
    /* 2c */ virtual void GetBoundingBox(AABB *bbox) override;
    /* 30 */ virtual void SetPosition(Vec3p *pos) override;
    /* 34 */ virtual void vfunc_34() override;
    /* 38 */ virtual void vfunc_38() override;
    /* 3c */ virtual void GetPosition(Vec3p *pos) override;
    /* 40 */ virtual q20 GetSizeXZ() override;
    /* 44 */ virtual q20 GetHeight() override;
    /* 48 */ virtual bool ContainsInXZ(Vec3p *pos) override;
    /* 4c */ virtual bool Contains(Vec3p *pos) override;
    /* 50 */ virtual bool IntersectsCube(Cube *cube) override;
    /* 54 */ virtual void vfunc_54(Cube *param1, Vec3p *param2, u32 *param3) override;
    /* 5c */

    TriggerAABB_Unk2_Unk1() {}
};

// Bit layout of the third vfunc_14 argument
struct TriggerShapeFlagBits {
    /* 0 */ u32 mType : 5;
    /* 5 */ u32 mUnk_05 : 8;
    /* d */ u32 mUnk_0d : 2;
    /* f */ u32 mUnk_0f : 1;
    /* 10 */ u32 mUnk_10 : 6;
    /* 16 */ u32 mUnk_16 : 1;
    /* 17 */ u32 mUnk_17 : 1;
    /* 18 */ u32 mUnk_18 : 1;
    /* 19 */ u32 mUnk_19 : 1;
    /* 1a */ u32 mUnk_1a : 2;
    /* 1c */ u32 mUnk_1c : 1;
    /* 1d */ u32 mUnk_1d : 1;
    /* 1e */ u32 mUnk_1e : 2;
};

union TriggerShapeFlags {
    u32 raw;
    TriggerShapeFlagBits bits;
};

extern "C" void func_ov000_02093a5c(UnkStruct_027e0f6c *param1, UnkStruct_ov000_020e2f04 *param2);
extern "C" void func_ov000_02093af0(UnkStruct_027e0f6c *param1, UnkStruct_ov000_020e2f04 *param2);

class TriggerAABB_Unk2 : public TriggerAABB {
public:
    /* 00 (base) */
    /* 2c */ bool mUnk_2c;
    /* 2d */ unk8 mUnk_2d[3];
    /* 30 */ TriggerAABB_Unk2_Unk1 mUnk_30[4];
    /* e0 */

    /* 00 */ virtual ~TriggerAABB_Unk2() override;
    /* 08 */ virtual void vfunc_08() override;
    /* 0c */ virtual bool vfunc_0c(bool param1) override;
    /* 10 */ virtual unk32 vfunc_10() override;
    /* 1c */

    TriggerAABB_Unk2(TriggerParams *params);
};
