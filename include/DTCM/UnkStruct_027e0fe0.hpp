#pragma once

#include "global.h"
#include "types.h"

struct UnkStruct_027e0fe0;

struct UnkStruct_027e0fe0_Unk0 {
    /* 00 */ u32 mMagic;
    /* 04 */ unk8 mUnk_04[0x20];
    /* 24 */ UnkStruct_027e0fe0 *mOwner;
    /* 28 */ unk32 mUnk_28;
    /* 2c */
};

struct UnkStruct_027e0fe0_Unk10 {
    /* 0 */ unk32 mUnk_0;
    /* 4 */ unk32 mUnk_4;
    /* 8 */
};

struct UnkStruct_027e0fe0 {
    /* 00 */ UnkStruct_027e0fe0_Unk0 *mUnk_00;
    /* 04 */ unk32 mUnk_04;
    /* 08 */ unk32 mUnk_08;
    /* 0c */ unk32 mUnk_0c;
    /* 10 */ UnkStruct_027e0fe0_Unk10 mUnk_10;
    /* 18 */

    void Init();
    UnkStruct_027e0fe0 *Dispose();
    void func_0202ea50(unk32 param1, unk32 param2, unk32 param3);
    void func_0202ea98();
};
