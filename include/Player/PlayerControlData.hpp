#pragma once

#include "global.h"
#include "nds/math.h"
#include "types.h"

#include "Actor/Actor.hpp"
#include "System/SysNew.hpp"

// 0x20 bytes; ctor/dtor live in overlay 4 next to PlayerBase
class PlayerControlData_Unk0 {
public:
    /* 00 */ unk8 mUnk_00[0x20];
    /* 20 */

    PlayerControlData_Unk0();
    ~PlayerControlData_Unk0();
};

class PlayerControlData_Unk1 {
public:
    /* 0 */ unk32 mUnk_0;
    /* 4 */ s32 mUnk_4;
    /* 8 */ unk32 mUnk_8;
    /* c */

    PlayerControlData_Unk1() :
        mUnk_0(0),
        mUnk_4(-1),
        mUnk_8(0) {}
    ~PlayerControlData_Unk1();

    void Set(s32 param1, unk32 param2) {
        mUnk_4 = param1;
        mUnk_8 = param2;
    }
};

class PlayerControlData_Unk2 : public SysObject {
public:
    /* 00 */ virtual ~PlayerControlData_Unk2();
};

class PlayerControlData : public SysObject {
public:
    /* 000 (vtable) */
    /* 004 */ unk32 mUnk_004;
    /* 008 */ unk32 mUnk_008;
    /* 00c */ unk32 mRadius;
    /* 010 */ unk32 mUnk_010;
    /* 014 */ unk32 mUnk_014;
    /* 018 */ unk32 mStateUnk;
    /* 01c */ Vec3p mLastJumpLocation; // vector from last location of the player before jumping?
    /* 028 */ unk16 mUnk_028;
    /* 02a */ unk16 mUnk_02a;
    /* 02c */ unk16 mUnk_02c;
    /* 02e */ unk16 mUnk_02e;
    /* 030 */ unk16 mUnk_030;
    /* 032 */ unk16 mUnk_032;
    /* 034 */ Vec3p mFairyVector; // shortened vector from link to fairy?
    /* 040 */ Mat4x3p mUnk_040[3];
    /* 0d0 */ Vec3p mUnk_0d0[2];
    /* 0e8 */ Vec3p mUnk_0e8[2];
    /* 100 */ PlayerControlData_Unk0 mUnk_100;
    /* 120 */ PlayerControlData_Unk0 mUnk_120;
    /* 140 */ PlayerControlData_Unk2 *mUnk_140;
    /* 144 */ unk32 mUnk_144;
    /* 148 */ unk8 mUnk_148;
    /* 149 */ unk8 mUnk_149;
    /* 14a */ unk8 mUnk_14a;
    /* 14b */ unk8 mUnk_14b;
    /* 14c */ unk8 mUnk_14c;
    /* 14d */ unk8 mUnk_14d;
    /* 14e */ unk8 mUnk_14e;
    /* 14f */ unk8 mUnk_14f;
    /* 150 */ unk16 mUnk_150;
    /* 152 */ unk8 mUnk_152[2];
    /* 154 */ Actor_UnkStruct_0a4 mUnk_154;
    /* 168 */ PlayerControlData_Unk1 mUnk_168[3];
    /* 18c */ unk32 mUnk_18c;
    /* 190 */ unk32 mUnk_190;
    /* 194 */ unk32 mUnk_194;
    /* 198 */ unk32 mUnk_198;
    /* 19c */ unk16 mUnk_19c;
    /* 19e */ unk16 mUnk_19e;
    /* 1a0 */

    /* 00 */ virtual void vfunc_00();
    /* 04 */ virtual ~PlayerControlData();
    /* 0c */ virtual unk32 vfunc_0c();
    /* 10 */ virtual unk32 GetCharacterId()    = 0;
    /* 14 */ virtual void vfunc_14(s32 param1) = 0;
    /* 18 */ virtual void vfunc_18();
    /* 1c */ virtual void vfunc_1c();
    /* 20 */ virtual void vfunc_20();
    /* 24 */ virtual void vfunc_24();
    /* 28 */ virtual void vfunc_28();
    /* 2c */ virtual void vfunc_2c();
    /* 30 */ virtual void vfunc_30();
    /* 34 */ virtual void vfunc_34();
    /* 38 */ virtual void vfunc_38(s32 param1, s32 param2) = 0;
    /* 3c */ virtual void vfunc_3c(s32 param1, s32 param2);
    /* 40 */ virtual void vfunc_40(u16 *param1, Vec3p *param2, unk32 param3, char param4);
    /* 44 */ virtual void vfunc_44(unk32 param1, unk32 *param2, unk32 param3, unk16 param4);
    /* 48 */ virtual void vfunc_48(unk32 param1, unk32 param2, unk32 param3, s16 param4);
    /* 4c */ virtual void vfunc_4c(unk32 param1, Vec3p *param2);
    /* 50 */ virtual void vfunc_50();
    /* 54 */ virtual void vfunc_54();
    /* 58 */ virtual void vfunc_58();
    /* 5c */ virtual void vfunc_5c();
    /* 60 */ virtual void vfunc_60(unk32 param1, unk32 param2, s32 param3);
    /* 64 */ virtual void vfunc_64(u32 param1);
    /* 68 */ virtual void vfunc_68(unk32 param1, unk32 param2);
    /* 6c */ virtual void vfunc_6c(s32 param1, Vec3p *param2);
    /* 70 */ virtual void vfunc_70(s32 param1);
    /* 74 */ virtual unk32 vfunc_74(s32 param1);
    /* 78 */ virtual unk32 vfunc_78(s32 param1);
    /* 7c */ virtual unk32 vfunc_7c();
    /* 80 */

    void func_ov000_020b4440();
    void func_ov000_020b4460(s32 param1);
    void func_ov000_020b44d4(s32 param1, u32 param2);
    void func_ov000_020b4558(s32 param1, u32 param2);
    void func_ov000_020b45e0();
    void func_ov000_020b45f8(unk32 *param1, unk8 param2, unk8 param3);
    void func_ov000_020b464c(unk32 *param1, unk8 param2, unk8 param3);
    void func_ov000_020b484c(s32 param1, s32 param2, s32 param3);
    void func_ov000_020b4944(unk32 param1, u32 param2, s32 param3);
    void func_ov000_020b4a00(s32 *param1, s32 *param2, s32 *param3, s32 param4);

    PlayerControlData();
};

extern PlayerControlData *gPlayerControlData;
