#pragma once

#include "global.h"
#include "types.h"

#include "Unknown/UnkStruct_02035064.hpp"

class UnkStruct_ov058_0219afb0_08 {
public:
    /* 00 (vtable) */
    /* 04 */ unk8 mUnk_04[6];
    /* 0a */ u16 mUnk_0a;
    /* 0c */ unk8 mUnk_0c[0xc];
    /* 18 */

    /* 00 */ virtual u32 vfunc_00(unk32 param1, unk32 param2, unk32 param3);
};

class UnkStruct_ov058_0219afb0 {
public:
    /* 00 (vtable) */
    /* 04 */ unk32 mUnk_04;
    /* 08 */ UnkStruct_ov058_0219afb0_08 mUnk_08[3];
    /* 50 */ UnkStruct_02035064 mUnk_50;
    /* d8 */ s16 mUnk_d8;
    /* da */ s16 mUnk_da;
    /* dc */ s16 mUnk_dc;
    /* de */ bool mUnk_de;
    /* df */ bool mUnk_df;
    /* e0 */ bool mUnk_e0;
    /* e4 */

    /* 00 */ virtual bool vfunc_00();
    /* 04 */ virtual void vfunc_04(bool param1);
    /* 08 */

    void func_ov058_0219a5c8();
    bool func_ov058_0219a76c(u16 param1);
    void func_ov058_0219a998();
    s32 func_ov058_0219aad0();
};
